#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
}

void Actor::SetActorData(double attackRange, float attack, float defence, float moveSpeed)
{
	myData->SetAllStatus(attackRange, attack, defence, moveSpeed);
}

void Actor::Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed)
{
	if (--actWait <= 0) {
		actIndex++;
		actWait = Speed;
		actIndex %= MaxIndex;
	}
	drawGh = DrawGhs[actIndex + MaxIndex * static_cast<uint32_t>(myExDir)];

	if (drawGh == -1) {
		int hoge = 0;
	}
}

void Actor::MoveUp()
{
	//ローカルポジションの移動
	localPos += {0, -1, 0};
}

void Actor::MoveRight()
{
	//ローカルポジションの移動
	localPos += {1, 0, 0};
}

void Actor::MoveDown()
{
	//ローカルポジションの移動
	localPos += {0, 1, 0};
}

void Actor::MoveLeft()
{
	//ローカルポジションの移動
	localPos += {-1, 0, 0};
}
//指定座標から指定距離離れた場所の座標を取得する関数 当たり判定の短形の各点座標を求めるのに使う
tnl::Vector3 Actor::GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance)
{
	//向いている方向による距離の修正
	tnl::Vector3 thisOffset = VECOFFSET[static_cast<uint32_t>(myDir)];
	//上ならyをマイナス,左ならxをマイナスに補正
	tnl::Vector3 fixDistance = distance * thisOffset;

	return myPos + fixDistance;
}
uint32_t Actor::GetExDir(float x, float y)
{
	//上下左右の場合
	//上下
	if (x == 0.0f) {
		if (y > 0)return static_cast<uint32_t>(EXDIR::BOTTOM);
		else if (y < 0)return static_cast<uint32_t>(EXDIR::TOP);
	}
	//左右
	if (y == 0.0f) {
		if (x > 0)return static_cast<uint32_t>(EXDIR::RIGHT);
		else if (x < 0)return static_cast<uint32_t>(EXDIR::LEFT);
	}

	//斜め方向の移動
	//右方向
	if (x > 0) {
		if(y>0)return static_cast<uint32_t>(EXDIR::RIGHTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::RIGHTTOP);
	}
	//左方向
	else {
		if (y > 0)return static_cast<uint32_t>(EXDIR::LEFTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::LEFTTOP);
	}
	return 0;
}
void Actor::SetExDir(float x, float y)
{
	//上下左右の場合
	//上下
	if (x == 0.0f) {
		if (y > 0)myExDir=EXDIR::BOTTOM;
		else if (y < 0)myExDir = EXDIR::TOP;
		return;
	}
	//左右
	if (y == 0.0f) {
		if (x > 0)myExDir = EXDIR::RIGHT;
		else if (x < 0)myExDir = EXDIR::LEFT;
		return;
	}

	//斜め方向の移動
	//右方向
	if (x > 0) {
		if (y > 0)myExDir = EXDIR::RIGHTBOTTOM;
		else myExDir = EXDIR::RIGHTTOP;
		return;
	}
	//左方向
	else {
		if (y > 0)myExDir = EXDIR::LEFTBOTTOM;
		else myExDir = EXDIR::LEFTTOP;
		return;
	}
}
//通常攻撃関数
void Actor::DefaultAttack()
{
	//使った本人の攻撃範囲を取得する
	double myRange = myData->GetAttackRange();
	//攻撃タイプを取得するによって発生する攻撃を変化させる
	if (myType == ATTACKTYPE::MELEE) {
		//攻撃範囲をプレイヤーの正面方向に向けて薙ぎ払う
		//左上は向かって左側のプレイヤー付近

		tnl::Vector3 distance;

		if (myDir == DIR::UP) {
			distance = tnl::Vector3(-(width / 2), height / 2, 0);
		}
		else if (myDir == DIR::RIGHT) {
			distance = tnl::Vector3(width / 2, -(height / 2), 0);
		}
		else if (myDir == DIR::DOWN) {
			distance = tnl::Vector3(width / 2, height / 2, 0);
		}
		else if (myDir == DIR::LEFT) {

		}


		//tnl::Vector3 leftTop = GetPositionToVector(drawPos, )

	}
	else if (myType == ATTACKTYPE::RANGE) {

	}



}
