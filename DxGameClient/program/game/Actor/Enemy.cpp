#include "Enemy.h"
#include"Camera.h"
#include"../GameManager.h"
#include"ActorData.h"
#include<time.h>
#include<random>

Enemy::Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(attackRange, attack, defence, speed);

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
	int x = static_cast<int>(drawPos.x) - camera->pos.x + (gManager->SCREEN_WIDTH >> 1);
	int y = static_cast<int>(drawPos.y) - camera->pos.y + (gManager->SCREEN_HEIGHT >> 1);
	DrawRotaGraph(x, y, 1.0f, 0, img_Ghost, true);
}

