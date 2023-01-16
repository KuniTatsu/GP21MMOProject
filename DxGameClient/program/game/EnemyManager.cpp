#include "EnemyManager.h"
#include"EnemySpawnManager.h"
#include"Actor/Camera.h"
#include"Actor/Enemy.h"
#include"Actor/ActorData.h"
#include"GameManager.h"
#include<time.h>
#include<random>

EnemyManager* EnemyManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// �R���X�g���N�^
EnemyManager::EnemyManager()
{
	gManager = GameManager::GetInstance();
	eSpawnManager = std::make_shared<EnemySpawnManager>();
	createCount = 0;
	LoadEnemyMaster();

	for (int i = 0; i < SPAWNLIMIT; ++i) {
		isUseEnemyIdentNum.emplace_back(false);
	}
}

//-----------------------------------------------------------------------------------------
// �f�X�g���N�^
EnemyManager::~EnemyManager()
{

}

void EnemyManager::LoadEnemyMaster()
{
	//enemyCsv��ǂݍ��ޏ��������� //�K�v�ȃJ���� attackRange,attack,defence,moveSpeed


	//debug�p -�{����csv����ǂݎ���ē����l
	auto newEnemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, 3.0, 5.0f, 3.0f, 2.0f);
	enemyMaster.emplace_back(newEnemy);

}

//-----------------------------------------------------------------------------------------
/*�V���O���g��*/
EnemyManager* EnemyManager::GetInstance()
{
	if (!instance) {
		instance = new EnemyManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// �j��
void EnemyManager::Destory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}
//�G�̎��ʔԍ��ŊJ���Ă���ԍ��𒲂ׁA�Ԃ��֐�
int EnemyManager::SearchBlankEnemyNum() {
	for (int i = 0; i < isUseEnemyIdentNum.size(); ++i) {
		//false:�J���Ă���Ȃ炻�̔ԍ���Ԃ�
		if (isUseEnemyIdentNum[i] != true) {
			isUseEnemyIdentNum[i] = true;
			return i;
		}
	}
	//�J���Ă���ꏊ���Ȃ��Ȃ�G���[�i���o�[��Ԃ�
	return -1;
}
//Enemy�̈ʒu���W�̓���
void EnemyManager::ShareEnemyPosFromServer(int identId, float x, float y, int dir, int type)
{
	bool canSpawn = true;

	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {

		int clientEnemyId = (*itr)->GetIdentId();
		//�T�[�o�[����ʒm���ꂽID�Ƃ��̃N���C�A���g��̓G��ID����v�����瓮����
		if (clientEnemyId == identId)
		{
			(*itr)->MoveEnemyFromServerInfo(x, y, dir);
			canSpawn = false;
			break;
		}
	}
	//���ɑ��݂��Ă���G�𓮂������Ȃ�V�K�X�|�[�������Ȃ�
	if (!canSpawn)return;

	//��v���Ȃ������炱�̃N���C�A���g��ɂ܂����݂��Ă��Ȃ��G�Ȃ̂ŁA��������
	tnl::Vector3 spawnPos(x, y, 0);
	CreateEnemyFromServer(type, identId, spawnPos);
}

void EnemyManager::ShareEnemyStatusFromServer(int identId, float moveHP)
{
	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {

		int clientEnemyId = (*itr)->GetIdentId();
		//�T�[�o�[����ʒm���ꂽID�Ƃ��̃N���C�A���g��̓G��ID����v�����瓮����
		if (clientEnemyId == identId)
		{
			(*itr)->ChangeStatusFromServerInfo(moveHP);
			break;
		}
	}
}

void EnemyManager::ShareEnemyDead(int identId, int isDead)
{
	//�����Ă����̂����S�ʒm��������
	if (isDead == 1) {
		for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {
			int clientEnemyId = (*itr)->GetIdentId();
			//�T�[�o�[����ʒm���ꂽID�Ƃ��̃N���C�A���g��̓G��ID����v������E��
			if (clientEnemyId == identId)
			{
				(*itr)->SetIsLive(false);
				break;
			}
		}
	}
}

/*�G�l�~�[�X�|�[��*/
void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	if (!spawntiming) {
		intervalCount++;
	}
	if (intervalCount % (60 * intervalLimit) == 0) {
		spawntiming = true;
	}
	if (createCount < SPAWNLIMIT && spawntiming) {
		eSpawnManager->SpawnEnemy(PlayerPos);
	}
}


std::shared_ptr<ActorData> EnemyManager::GetEnemyData(int type)
{
	auto data = enemyMaster[type]->GetActorData();

	return data;
}

/*�G�l�~�[����*/
void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);
	//auto newEnemy = std::make_shared<Enemy>(posEnemy, data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	//�̎��ʔԍ����擾
	int identId = SearchBlankEnemyNum();
	//�̎��ʔԍ����G���[�ԍ��Ȃ�G�̐������s��Ȃ�
	if (identId == -1)return;

	//auto newEnemy = std::make_shared<Enemy>(posEnemy, 3, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());
	auto newEnemy = std::make_shared<Enemy>(posEnemy, 3, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed(), identId);

	//�T�[�o�[�ɐ��������G�̏��𑗂�
	gManager->SendEnemyInfoToServer(posEnemy.x, posEnemy.y, 1, identId, type);

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;
	tnl::DebugTrace("�G�l�~�[�������ꂽ�F%d\n", createCount);
}

void EnemyManager::CreateEnemyFromServer(int type, int identId, tnl::Vector3& spawnPos)
{
	auto data = GetEnemyData(type);
	auto newEnemy = std::make_shared<Enemy>(spawnPos, 3.0, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed(), identId);
	SetEnemyList(newEnemy);
	createCount++;
	tnl::DebugTrace("�G�l�~�[�������ꂽ�F%d\n", createCount);
}

void EnemyManager::Update(float deltatime)
{
	auto& list = GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Update();
	}


	//���񂾓G�̏���
	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ) {
		bool& isLive = (*itr)->GetIsLive();
		if (!isLive) {
			//�ŋߎ��񂾓G���X�g�ɓo�^
			recentDeadEnemyList.emplace_back((*itr));
			//�����Ă���G���X�g����폜
			itr = EnemyList.erase(itr);
			createCount--;
		}
		else {
			++itr;
		}
	}

	//�ŋߎ��񂾓G���X�g�̏������Ə���
	if (recentDeadEnemyList.size() > MAXRECENTDEAD) {
		recentDeadEnemyList.pop_front();
	}

}

void EnemyManager::Draw(Camera* camera)
{

	auto& list = GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Draw(camera);
	}
}