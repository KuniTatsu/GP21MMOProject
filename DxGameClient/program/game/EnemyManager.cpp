#include "EnemyManager.h"
#include"Actor/Camera.h"
#include"GameManager.h"
#include<time.h>
#include<random>

EnemyManager* EnemyManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
EnemyManager::EnemyManager()
{
	gManager = GameManager::GetInstance();
	
}

//-----------------------------------------------------------------------------------------
// デストラクタ
EnemyManager::~EnemyManager()
{

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
	return dist(gen);
}

void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	srand(static_cast<unsigned int>(time(NULL)));
	random = static_cast<uint32_t>(rand()) % 4;

	tnl::Vector3 fix = { 0,0,0 };
	tnl::Vector3 minPos = { 0, 0, 0 };
	tnl::Vector3 maxPos = { 0, 0, 0 };
	int x = 0;
	int y = 0;

	switch (random)
	{
	case static_cast<uint32_t>(DIR::UP):
		fix = { 0,static_cast<float>(FIXDIS[random]),0 };
		minPos = PlayerPos + fix;
		maxPos = PlayerPos + fix * 2;
		break;
	case static_cast<uint32_t>(DIR::RIGHT):
		fix = { static_cast<float>(FIXDIS[random]),0,0 };
		minPos = PlayerPos + fix;
		maxPos = PlayerPos + fix * 2;
		break;
	case static_cast<uint32_t>(DIR::DOWN):
		fix = { 0,static_cast<float>(FIXDIS[random]),0 };
		minPos = PlayerPos + fix;
		maxPos = PlayerPos + fix * 2;
		break;
	case static_cast<uint32_t>(DIR::LEFT):
		fix = { static_cast<float>(FIXDIS[random]),0,0 };
		minPos = PlayerPos + fix;
		maxPos = PlayerPos + fix * 2;
		break;
	}

	x = randomRange(static_cast<int>(minPos.x), static_cast<int>(maxPos.x));
	y = randomRange(static_cast<int>(minPos.y), static_cast<int>(maxPos.y));

	/*エネミー生成*/
	CreateEnemy(tnl::Vector3(static_cast<float>(x), static_cast<float>(y), 0));
	
}

void EnemyManager::CreateEnemy(tnl::Vector3 posEnemy)
{
	srand(static_cast<unsigned int>(time(NULL)));
	random = static_cast<uint32_t>(rand()) % 2;


	switch (random)
	{
	case static_cast<uint32_t>(EnemyType::SLIME):
		//スライムの生成
		break;
	case static_cast<uint32_t>(EnemyType::GOBLIN):
		//ゴブリンの生成
		break;
	}
}

void EnemyManager::Update()
{

}

void EnemyManager::Draw(Camera* camera)
{
	
}