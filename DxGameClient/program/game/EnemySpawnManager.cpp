#include "EnemySpawnManager.h"
#include"GameManager.h"
#include"EnemyManager.h"
#include"Actor/Enemy.h"
#include<time.h>
#include<random>

EnemySpawnManager::EnemySpawnManager()
{
	gManager = GameManager::GetInstance();
	eManager = EnemyManager::GetInstance();
}

EnemySpawnManager::~EnemySpawnManager()
{
}

void EnemySpawnManager::SpawnEnemy(tnl::Vector3& PlayerPos)
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

int EnemySpawnManager::randomRange(int minRange, int maxRange)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(minRange, maxRange);

	int rand = dist(gen);

	return rand;
}

void EnemySpawnManager::SelectEnemy(tnl::Vector3 posEnemy)
{
	//敵を生成できるかチェック
	if (CheckCanCreateEnemy(posEnemy))return;

	srand(static_cast<unsigned int>(time(NULL)));
	//random = static_cast<uint32_t>(rand()) % 2;
	random = 0;

	switch (random)
	{
	case static_cast<uint32_t>(EnemyManager::EnemyType::GHOST):
		eManager->CreateEnemy(static_cast<uint32_t>(EnemyManager::EnemyType::GHOST), posEnemy);
		break;
	case static_cast<uint32_t>(EnemyManager::EnemyType::SLIME):
		//スライムの生成
		break;
	case static_cast<uint32_t>(EnemyManager::EnemyType::GOBLIN):
		//ゴブリンの生成
		break;
	}
}

bool EnemySpawnManager::CheckCanCreateEnemy(tnl::Vector3& Pos)
{
	bool canSpawn = true;
	//既存の敵のポジションとかぶっていないかチェック
	for (auto& enemy : eManager->EnemyList) {
		auto listEnemyPos = enemy->GetPos();
		if (gManager->GetLength(Pos, listEnemyPos) < 32) {
			canSpawn = false;
			break;
		}
	}
	return canSpawn;
	////かぶっていたら生成しない
	//if (!canSpawn)return;

	//auto enemy = std::make_shared<Enemy>(Pos);
	//Enemys.emplace_back(enemy);
}
