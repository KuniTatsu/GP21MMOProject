#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
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
