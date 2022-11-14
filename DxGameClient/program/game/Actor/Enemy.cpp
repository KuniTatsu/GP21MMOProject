#include "Enemy.h"
#include"Camera.h"
#include"../GameManager.h"
#include<time.h>
#include<random>

Enemy::Enemy(tnl::Vector3 SpawnPos)
{

	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{

}

void Enemy::Update()
{

}

void Enemy::Draw(Camera* camera)
{
	DrawRotaGraph(static_cast<int>(drawPos.x), static_cast<int>(drawPos.y), 0, 1.0f, img_Ghost, true);
}

