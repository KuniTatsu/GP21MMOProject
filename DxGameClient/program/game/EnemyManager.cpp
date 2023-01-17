#include "EnemyManager.h"
#include"EnemySpawnManager.h"
#include"Actor/Camera.h"
#include"Actor/Enemy.h"
#include"Actor/ActorData.h"
#include"GameManager.h"
#include"ResourceManager.h"
#include<time.h>
#include<random>

EnemyManager* EnemyManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
EnemyManager::EnemyManager()
{
	gManager = GameManager::GetInstance();
	eSpawnManager = std::make_shared<EnemySpawnManager>();
	createCount = 0;
	LoadEnemyMaster();
}

//-----------------------------------------------------------------------------------------
// デストラクタ
EnemyManager::~EnemyManager()
{

}

void EnemyManager::LoadEnemyMaster()
{
	//enemyCsvを読み込む処理を書く //必要なカラム attackRange,attack,defence,moveSpeed


	//debug用 -本来はcsvから読み取って入れる値

	auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));
	auto newEnemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, 3.0, animList[0],0);
	enemyMaster.emplace_back(newEnemy);

}

//-----------------------------------------------------------------------------------------
/*シングルトン*/
EnemyManager* EnemyManager::GetInstance()
{
	if (!instance) {
		instance = new EnemyManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// 破棄
void EnemyManager::Destory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

/*エネミースポーン*/
void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	if (!spawntiming) {
		intervalCount++;
	}
	if (intervalCount % (60 * intervalLimit) == 0) {
		spawntiming = true;
	}
	if (createCount < spawnLimit && spawntiming) {
		eSpawnManager->SpawnEnemy(PlayerPos);
	}
}


std::shared_ptr<ActorData> EnemyManager::GetEnemyData(int type)
{
	auto data = enemyMaster[type]->GetActorData();

	return data;
}

/*エネミー生成*/
void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);
	//auto newEnemy = std::make_shared<Enemy>(posEnemy, data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	auto newEnemy = std::make_shared<Enemy>(posEnemy, 3.0, animList[type], type);

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;
	//tnl::DebugTrace("エネミー生成された：%d\n", createCount);
}

void EnemyManager::Update(float deltatime)
{
	auto& list = GetEnemyList();
	for (auto& enemy : list) {
		enemy->Update();
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