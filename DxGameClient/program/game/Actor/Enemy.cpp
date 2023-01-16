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

Enemy::Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed, int IdentId)
{
	drawPos = SpawnPos;
	gManager = GameManager::GetInstance();
	img_Ghost = gManager->LoadGraphEx("graphics/GhostEnemy.png");

	myData = std::make_shared<ActorData>();
	myData->SetAllStatus(attackRange, attack, defence, speed);

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
	myData->SetHP(moveHP);
}


/*エネミー索敵範囲（円）*/
void Enemy::SearchCircle(int SpawnPosX, int SpawnPosY, double atackRange)
{
	int range = (static_cast<int>(atackRange) * gManager->CHIPWIDTH) + (gManager->CHIPWIDTH >> 1);
	///*DrawCircle(SpawnPosX, SpawnPosY, range, GetColor(244,167,167), false);
	/*if (tnl::IsIntersectSphere(drawPos,range,)) {

	}*/
}

unsigned int Enemy::ChangedColor(bool atack)
{
	return 0;
}

void Enemy::Update()
{
	//debug
	bool isMove = false;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		drawPos.y--;
		myExDir = EXDIR::TOP;
		isMove = true;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		drawPos.x--;
		myExDir = EXDIR::LEFT;
		isMove = true;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
		drawPos.y++;
		myExDir = EXDIR::BOTTOM;
		isMove = true;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		drawPos.x++;
		myExDir = EXDIR::RIGHT;
		isMove = true;
	}

	if (!isMove)return;

	gManager->SendEnemyInfoToServer(drawPos.x, drawPos.y, static_cast<int>(myExDir), identId);

}

void Enemy::Draw(Camera* camera)
{
	auto x = static_cast<int>(drawPos.x) - camera->pos.x + (gManager->SCREEN_WIDTH >> 1);
	auto y = static_cast<int>(drawPos.y) - camera->pos.y + (gManager->SCREEN_HEIGHT >> 1);

	DrawRotaGraphF(x, y, 1.0f, 0, img_Ghost, true);
	SearchCircle(x, y, myData->GetAttackRange());
}

