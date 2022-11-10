#include "Enemy.h"
#include<time.h>
#include<random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}

void Enemy::Draw(Camera* camera)
{
	tnl::DebugTrace("%d", randomRange(0, 100));
}

void Enemy::Init()
{

}

int Enemy::randomRange(int minRange, int maxRange)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(minRange, maxRange);
	return dist(gen);
}

void Enemy::SpawnEnemy(tnl::Vector3& PlayerPos)
{

	srand(static_cast<unsigned int>(time(NULL)));
	random = static_cast<uint32_t>(rand()) % 4;

	tnl::Vector3 fix = { 0,0,0 };
	tnl::Vector3 minPos = { 0, 0, 0};
	tnl::Vector3 maxPos = { 0, 0, 0 };

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

	//DrawRotaGraph()

}
