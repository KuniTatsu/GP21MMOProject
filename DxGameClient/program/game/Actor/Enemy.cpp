#include "Enemy.h"
#include"Camera.h"
#include"../GameManager.h"
#include"ActorData.h"
#include<time.h>
#include<random>
#include"../ResourceManager.h"
#include"../DebugDef.h"


Enemy::Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());
	myData->SetAttackRange(data->GetAttackRange());

	auto& attribute = data->GetAttribute();

	myData->SetAttribute(attribute[0], attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);
	myData->CalcMainStatus();

	auto rManager = ResourceManager::GetInstance();
	auto& hoge = rManager->GetGraphicSize(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	SetCircleSize(hoge[type]);

	myAnimationGh = ghs;
}

Enemy::Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type, int IdentId)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());
	myData->SetAttackRange(data->GetAttackRange());

	auto& attribute = data->GetAttribute();

	myData->SetAttribute(attribute[0], attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);
	myData->CalcMainStatus();

	auto rManager = ResourceManager::GetInstance();
	auto& hoge = rManager->GetGraphicSize(static_cast<int>(ResourceManager::RESOUCETYPE::ENEMY));

	SetCircleSize(hoge[type]);

	myAnimationGh = ghs;

	identId = IdentId;

}

Enemy::~Enemy()
{

}

void Enemy::Init()
{

}

void Enemy::MoveEnemyFromServerInfo(float x, float y, int dir)
{
	if (drawPos.x != x) {
		drawPos.x = x;
	}
	if (drawPos.y != y) {
		drawPos.y = y;
	}

	//敵は上向きと下向きの画像がないので、それ以外なら向いている方向を変える
	if (dir != static_cast<int>(EXDIR::BOTTOM) && dir != static_cast<int>(EXDIR::TOP)) {
		//向いている向きが同じなら処理しない
		if (dir == static_cast<int>(myExDir))return;
		SetExDir(dir);
	}
}

void Enemy::ChangeStatusFromServerInfo(float moveHP)
{
	myData->UpdateHp(moveHP);
}

/*エネミー索敵範囲（四角）*/
void Enemy::SearchBox(tnl::Vector3 SpawnPos, double atackRange)
{
	//索敵範囲
	int range = (static_cast<int>(atackRange) * gManager->CHIPWIDTH);
	float halfChipSize = gManager->CHIPHEIGHT >> 1;
	tnl::Vector3 rangeMax = SpawnPos + tnl::Vector3(range, range, 0) + tnl::Vector3(halfChipSize, halfChipSize, 0);
	tnl::Vector3 rangeMin = SpawnPos - tnl::Vector3(range, range, 0) - tnl::Vector3(halfChipSize, halfChipSize, 0);

	//--------------------------------------------------------------------------------------------------------------
	//Debug用
	//探索範囲にプレイヤがはいったら範囲BOXが赤くなる
	int x1 = static_cast<int>(SpawnPos.x) - range;
	int y1 = static_cast<int>(SpawnPos.y) - range;
	int x2 = static_cast<int>(SpawnPos.x) + range;
	int y2 = static_cast<int>(SpawnPos.y) + range;
	DrawBox(x1, y1, x2, y2, ChangedColor(), false);
	//--------------------------------------------------------------------------------------------------------------

	//敵とプレイヤの距離+カメラの位置修正
	tnl::Vector3 serchRangePos = gManager->GetVectorToPlayer(SpawnPos) +
		tnl::Vector3((gManager->SCREEN_WIDTH >> 1), (gManager->SCREEN_HEIGHT >> 1), 0);

	//位置座標による索敵
	if (rangeMax.x > serchRangePos.x && rangeMin.x < serchRangePos.x
		&& rangeMax.y > serchRangePos.y && rangeMin.y < serchRangePos.y) {
		onFollowToPlayer = true;
	}
	else {
		onFollowToPlayer = false;
	}

}

//索敵範囲の色を変えるだけ
unsigned int Enemy::ChangedColor()
{
	if (!onFollowToPlayer) {
		return GetColor(255, 255, 255);
	}
	else {
		GetColor(244, 167, 167);
	}
}

void Enemy::EnemyMove() {
	drawPos += gManager->GetVectorToPlayer(drawPos) * myData->GetMoveSpeed();
}

void Enemy::Update()
{
	float deltatime = GameManager::GetInstance()->deltaTime;
	//インターバル更新
	UpdateAttackInterval(deltatime);

#ifndef DEBUG_ON
	gManager->SendEnemyInfoToServer(drawPos.x, drawPos.y, static_cast<int>(myExDir), identId);
#endif

	/*if (onFollowToPlayer) {
		EnemyMove();
	}*/
	if (onFollowToPlayer && HitMaptoCharacter(drawPos)) {
		EnemyMove();
	}
}

void Enemy::Draw(Camera* camera)
{
	auto x = static_cast<int>(drawPos.x) - camera->pos.x + (gManager->SCREEN_WIDTH >> 1);
	auto y = static_cast<int>(drawPos.y) - camera->pos.y + (gManager->SCREEN_HEIGHT >> 1);


	/*索敵関数*/
	SearchBox(tnl::Vector3(x, y, 0), 50);

	DrawRotaGraphF(x, y, 1.0f, 0, img_Ghost, true);
}

