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
// コンストラクタ
EnemyManager::EnemyManager()
{
	gManager = GameManager::GetInstance();
	eSpawn = std::make_shared<EnemySpawnManager>();
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
	auto newEnemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, 3.0, 5.0f, 3.0f, 2.0f);
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

//int EnemyManager::randomRange(int minRange, int maxRange)
//{
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	std::uniform_int_distribution<> dist(minRange, maxRange);
//
//	int rand = dist(gen);
//
//	return rand;
//}

/*エネミースポーン*/
void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	if (!spawntiming) {
		intervalCount++;
	}
	if (intervalCount % (60 * intervalLimit) == 0) {
		spawntiming = true;
	}
	if (eSpawn && createCount < spawnLimit && spawntiming) {
		eSpawn->SpawnEnemy(PlayerPos);
	}
}


std::shared_ptr<ActorData> EnemyManager::GetEnemyData(int type)
{
	auto data = enemyMaster[type]->GetActorData();

	return data;
}

void EnemyManager::SortEnemyList(tnl::Vector3& playerPos)
{
	EnemyList.sort([&](std::shared_ptr<Enemy>left, std::shared_ptr<Enemy>right) {
		auto distance1 = gManager->GetLengthFromTwoPoint(playerPos, left->GetPos());
		auto distance2 = gManager->GetLengthFromTwoPoint(playerPos, right->GetPos());

		if (distance1 > distance2)return true;
		return false;
		});
}

/*エネミー生成*/
void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);
	auto newEnemy = std::make_shared<Enemy>(posEnemy, data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;
	//tnl::DebugTrace("エネミー生成された：%d\n", createCount);
}

void EnemyManager::Update(float deltatime)
{
}

void EnemyManager::Draw(Camera* camera)
{

	auto& list = GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Draw(camera);
	}
}