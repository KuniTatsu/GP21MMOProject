#include "EnemyManager.h"
#include"EnemySpawnManager.h"
#include"Actor/Camera.h"
#include"Actor/Enemy.h"
#include"Actor/ActorData.h"
#include"GameManager.h"
#include"ResourceManager.h"
#include"Actor/ActorDrawManager.h"
#include"EffectManager.h"
#include"Connect.h"
#include<time.h>
#include<random>
#include"DebugDef.h"

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
	auto enemyCsv = tnl::LoadCsv("csv/Enemy/EnemyMaster.csv");

	for (int i = 1; i < enemyCsv.size(); ++i) {
		/*
		id	name	rare	attackRange	STR	VIT	INT	MIN	SPD	DEX	weight

		*/
		int id = std::stoi(enemyCsv[i][0]);
		std::string name = enemyCsv[i][1];
		float attackRange = std::stof(enemyCsv[i][2]);
		int STR = std::stoi(enemyCsv[i][3]);
		int VIT = std::stoi(enemyCsv[i][4]);
		int INT = std::stoi(enemyCsv[i][5]);
		int MID = std::stoi(enemyCsv[i][6]);
		int SPD = std::stoi(enemyCsv[i][7]);
		int DEX = std::stoi(enemyCsv[i][8]);

		EnemySpawnWeight.emplace_back(std::stoi(enemyCsv[i][9]));

		auto data = std::make_shared<ActorData>();
		data->SetAttackRange(attackRange);

		data->SetAttribute(STR, VIT, INT, MID, SPD, DEX);
		//�U���͂Ȃǂ̃��C���X�e�[�^�X�̎Z�o�Ƒ��
		data->CalcMainStatus();

		auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

		auto enemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, data, animList[i - 1], i - 1);

		enemy->SetEnemyId(id);

		enemyMaster.emplace_back(enemy);

	}

	//���[Id�̓o�^�@������Csv�ɍ�����
	matchDeadBodyId.insert(std::make_pair(100, 2000));
	matchDeadBodyId.insert(std::make_pair(101, 2001));
	matchDeadBodyId.insert(std::make_pair(102, 2002));
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
void EnemyManager::ResetEnemyNum(int enemyNum)
{
	if (enemyNum > SPAWNLIMIT)return;
	isUseEnemyIdentNum[enemyNum] = false;
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
//�T�[�o�[���瑗���Ă����������ɓG�̎��S�󋵂��X�V����֐�
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
				//���񂾃A�j���[�V����
				auto animPos = (*itr)->GetPos();
				EffectManager::GetInstance()->CreateEffect(static_cast<int>(EffectManager::EFFECTTYPE::DEATH), animPos);

				//���񂾓G�̌ʔԍ����J������
				ResetEnemyNum((*itr)->GetIdentId());

				//�ŋߎ��񂾓G���X�g�ɓo�^
				recentDeadEnemyList.emplace_back((*itr));
				//�`��Ώۂ���폜
				ActorDrawManager::GetInstance()->RemoveDrawActorList((*itr));
				//�����Ă���G���X�g����폜
				itr = EnemyList.erase(itr);


				createCount--;
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

int EnemyManager::GetEnemyIdFromType(int type)
{
	return enemyMaster[type]->GetEnemyId();
}

int EnemyManager::GetDeadBodyId(int enemyId)
{
	return matchDeadBodyId.at(enemyId);
}

void EnemyManager::SortEnemyList(tnl::Vector3& playerPos)
{
	EnemyList.sort([&](std::shared_ptr<Enemy>left, std::shared_ptr<Enemy>right) {
		auto distance1 = gManager->GetLengthFromTwoPoint(playerPos, left->GetPos());
		auto distance2 = gManager->GetLengthFromTwoPoint(playerPos, right->GetPos());

		if (distance1 < distance2)return true;
		return false;
		});
}

/*�G�l�~�[����*/
void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);

	int id = GetEnemyIdFromType(type);

	//�̎��ʔԍ����擾
	int identId = SearchBlankEnemyNum();
	//�̎��ʔԍ����G���[�ԍ��Ȃ�G�̐������s��Ȃ�
	if (identId == -1)return;

	auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	auto newEnemy = std::make_shared<Enemy>(posEnemy, data, animList[type], type);

	newEnemy->SetIdentId(identId);

	newEnemy->SetEnemyId(id);

	int isBig = 0;

	int rand = gManager->GetRandBetweenNum(0, 2000);
	//1/200�̊m���ŋ��剻
	if (rand < 20) {
		newEnemy->SetIsBig();
		isBig = 1;
	}

#ifndef DEBUG_ON
	//�T�[�o�[�ɐ��������G�̏��𑗂�
	gManager->SendInitEnemyInfoToServer(posEnemy.x, posEnemy.y, 1, identId, type, isBig);
	gManager->SendEnemyInfoToServer(posEnemy.x, posEnemy.y, 1, identId, type);

#endif

	ActorDrawManager::GetInstance()->AddDrawActorList(newEnemy);

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;

	tnl::DebugTrace("�G�l�~�[�������ꂽ�F%d\n", createCount);
}

void EnemyManager::CreateEnemyFromServer(int type, int identId, tnl::Vector3& spawnPos, int IsBig)
{
	auto data = GetEnemyData(type);

	int id = GetEnemyIdFromType(type);

	auto& ghs = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	auto newEnemy = std::make_shared<Enemy>(spawnPos, data, ghs[type], type, identId);

	newEnemy->SetEnemyId(id);

	ActorDrawManager::GetInstance()->AddDrawActorList(newEnemy);

	if (IsBig == 1)newEnemy->SetIsBig();

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

			//���񂾃A�j���[�V����
			auto animPos = (*itr)->GetPos();
			EffectManager::GetInstance()->CreateEffect(static_cast<int>(EffectManager::EFFECTTYPE::DEATH), animPos);

			auto id = (*itr)->GetIdentId();
#ifdef DEBUG_ON
			auto connect = GameManager::GetInstance()->GetConnection();
			if (connect != nullptr) {
				connect->SendClientEnemyIsDead(id);
			}
#endif // DEBUG_ON


			//���񂾓G�̌ʔԍ����J������
			ResetEnemyNum(id);

			//�ŋߎ��񂾓G���X�g�ɓo�^
			recentDeadEnemyList.emplace_back((*itr));
			//�`��Ώۂ���폜
			ActorDrawManager::GetInstance()->RemoveDrawActorList((*itr));
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
	SetFontSize(50);
	//DrawStringEx(50, 50, -1, "%d", createCount);
	SetFontSize(16);
}