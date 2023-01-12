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


/*エネミー索敵範囲（四角）*/
void Enemy::SearchBox(tnl::Vector3 SpawnPos, double atackRange)
{
	//索敵範囲
	int range = (static_cast<int>(atackRange) * gManager->CHIPWIDTH);
	float halfChipSize = gManager->CHIPHEIGHT >> 1;
	tnl::Vector3 rangeMax = SpawnPos + tnl::Vector3(range,range,0) + tnl::Vector3(halfChipSize, halfChipSize,0);
	tnl::Vector3 rangeMin = SpawnPos - tnl::Vector3(range, range, 0) - tnl::Vector3(halfChipSize, halfChipSize, 0);
	
	//--------------------------------------------------------------------------------------------------------------
	//Debug用
	//探索範囲にプレイヤがはいったら範囲BOXが赤くなる
	int x1 = static_cast<int>(SpawnPos.x) - range;
	int y1 = static_cast<int>(SpawnPos.y) - range;
	int x2 = static_cast<int>(SpawnPos.x) + range;
	int y2 = static_cast<int>(SpawnPos.y) + range;
	DrawBox(x1, y1, x2, y2,ChangedColor(), false);
	//--------------------------------------------------------------------------------------------------------------

	//敵とプレイヤの距離+カメラの位置修正
	tnl::Vector3 serchRangePos = gManager->GetVectorToPlayer(SpawnPos) + 
									tnl::Vector3((gManager->SCREEN_WIDTH >> 1), (gManager->SCREEN_HEIGHT >> 1),0);

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

void Enemy::EnemyMove(tnl::Vector3 SpawnPos, double speed) {
	
	float A = gManager->GetVectorToPlayer(SpawnPos).x;
	float B = gManager->GetVectorToPlayer(SpawnPos).y;
	float C = sqrt(A * A + B * B);

	float dx = A / C;
	float dy = B / C;

	SpawnPos += tnl::Vector3(dx, dy, 0) * static_cast<float>(speed);

}

void Enemy::Update()
{
	EnemyMove(drawPos, myData->GetMoveSpeed());
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))drawPos.x++;
	
}

void Enemy::Draw(Camera* camera)
{
	auto x = static_cast<int>(drawPos.x) - camera->pos.x + (gManager->SCREEN_WIDTH >> 1);
	auto y = static_cast<int>(drawPos.y) - camera->pos.y + (gManager->SCREEN_HEIGHT >> 1);

	//if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))x++;
	if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_SPACE))drawPos.x++;
	
	/*索敵関数*/
	SearchBox(tnl::Vector3(x, y, 0), myData->GetAttackRange());
	
	DrawRotaGraphF(x, y, 1.0f, 0, img_Ghost, true);
}

