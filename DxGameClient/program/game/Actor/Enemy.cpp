#include "Enemy.h"
#include"Camera.h"
#include"../GameManager.h"
#include"ActorData.h"
#include<time.h>
#include<random>
#include"../ResourceManager.h"

Enemy::Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed, int type)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(attackRange, attack, defence, speed);

	auto rManager = ResourceManager::GetInstance();
	auto& hoge = rManager->GetGraphicSize(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	SetCircleSize(hoge[type]);

}

Enemy::Enemy(tnl::Vector3 SpawnPos, std::shared_ptr<ActorData>& data, int type)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	auto& attribute = data->GetAttribute();

	myData->SetAttribute(attribute[0], attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);


	auto rManager = ResourceManager::GetInstance();
	auto& hoge = rManager->GetGraphicSize(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	SetCircleSize(hoge[type]);
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{

}

void Enemy::SetCircleSize(tnl::Vector3& size)
{
	if (size.x >= size.y)circleSize = size.x;
	else circleSize = size.y;
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

