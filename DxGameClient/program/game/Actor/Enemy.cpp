#include "Enemy.h"
#include<time.h>

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

}

void Enemy::Init()
{

}

void Enemy::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	
	random = rand() % 4;

	switch (random)
	{
	case static_cast<uint32_t>(DIR::UP):
		/*tnl::Vector3 fix = { 0,FIXDIS[random],0 };
		tnl::Vector3 minPos = PlayerPos + fix;
		tnl::Vector3 maxPos = PlayerPos + Fix*2;*/
		break;
	}
}
