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
		//攻撃力などのメインステータスの算出と代入
		data->CalcMainStatus();

		auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

		auto enemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, data, animList[i - 1], i - 1);

		enemyMaster.emplace_back(enemy);

	}
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

	//auto newEnemy = std::make_shared<Enemy>(posEnemy, data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	auto& animList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));
	//auto newEnemy = std::make_shared<Enemy>(posEnemy, data, animList[1], 0);

	//Enemy(tnl::Vector3 SpawnPos, std::shared_ptr<ActorData>& data, std::vector<int>& ghs, int type);
	auto newEnemy = std::make_shared<Enemy>(posEnemy, data, animList[type], 0);

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;

	tnl::DebugTrace("エネミー生成された：%d\n", createCount);
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