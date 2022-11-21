#include "EnemyManager.h"
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
	auto newEnemy = std::make_shared<Enemy>(tnl::Vector3{0,0,0}, 3.0, 5.0f, 3.0f,2.0f);
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

int EnemyManager::randomRange(int minRange, int maxRange)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(minRange, maxRange);

	int rand = dist(gen);

	return rand;
}

void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	srand(static_cast<unsigned int>(time(0)));
	random = static_cast<uint32_t>(rand()) % 4;

	tnl::Vector3 fix = { 0,0,0 };
	tnl::Vector3 minPos = { 0, 0, 0 };
	tnl::Vector3 maxPos = { 0, 0, 0 };
	int x = 0;
	int y = 0;

	//xが-200から200の間,yが-200から200の間のどこかをとる
	//プレイヤーからの最低距離の絶対値
	minPos = PlayerPos + tnl::Vector3{ 20, 20, 0 };
	//プレイヤーからの最大距離の絶対値
	maxPos = PlayerPos + tnl::Vector3{ 200,200,0 };

	//20~200の間でランダムな数値を取得する
	x = randomRange(static_cast<int>(minPos.x), static_cast<int>(maxPos.x));
	y = randomRange(static_cast<int>(minPos.y), static_cast<int>(maxPos.y));

	int coefficient[2] = { 1,1 };
	for (int i = 0; i < 2; ++i) {
		//-1~0
		int hoge = randomRange(0, 1) - 1;
		if (hoge == 0)hoge = 1;
		coefficient[i] *= hoge;
	}
	x *= coefficient[0];
	y *= coefficient[1];

	/*エネミー生成*/
	SelectEnemy(tnl::Vector3(static_cast<float>(x), static_cast<float>(y), 0));

}

/*エネミー種類ごとの生成*/
void EnemyManager::SelectEnemy(tnl::Vector3 posEnemy)
{
	//敵を生成できるかチェック
	if (!gManager->CheckCanCreateEnemy(posEnemy))return;

	srand(static_cast<unsigned int>(time(NULL)));
	//random = static_cast<uint32_t>(rand()) % 2;
	random = 0;

	switch (random)
	{
	case static_cast<uint32_t>(EnemyType::GHOST):
		CreateEnemy(static_cast<uint32_t>(EnemyType::GHOST),posEnemy);
		break;
	case static_cast<uint32_t>(EnemyType::SLIME):
		//スライムの生成
		break;
	case static_cast<uint32_t>(EnemyType::GOBLIN):
		//ゴブリンの生成
		break;
	}
}

std::shared_ptr<ActorData> EnemyManager::GetEnemyData(int type)
{
	auto data = enemyMaster[type]->GetActorData();

	return data;
}

void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);
	auto newEnemy = std::make_shared<Enemy>(posEnemy,data->GetAttackRange(),data->GetAttack(),data->GetDefence(),data->GetMoveSpeed());
	createCount++;

	FUNCCOUNT p;
	

	gManager->SetEnemyList(newEnemy);

}

void EnemyManager::Update(float deltatime)
{

}

void EnemyManager::Draw(Camera* camera)
{
	auto& list = gManager->GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Draw(camera);
	}


}