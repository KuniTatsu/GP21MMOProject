#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"
#include"../EnemyManager.h"
#include"Enemy.h"


Actor::Actor()
{
	gManager = GameManager::GetInstance();
	myData = std::make_shared<ActorData>();
}

std::vector<tnl::Vector3> Actor::GetCharaEdgePos()
{
	std::vector<tnl::Vector3>ret;
	tnl::Vector3 leftTop = drawPos - tnl::Vector3{ width, height, 0 };
	tnl::Vector3 rightTop = drawPos - tnl::Vector3{ -width, height, 0 };

	tnl::Vector3 leftBottom = drawPos - tnl::Vector3{ width, -height, 0 };
	tnl::Vector3 rightBottom = drawPos - tnl::Vector3{ -width, -height, 0 };

	ret.emplace_back(leftTop);
	ret.emplace_back(rightTop);
	ret.emplace_back(leftBottom);
	ret.emplace_back(rightBottom);

	return ret;
}

void Actor::SetActorData(double attackRange, float attack, float defence, float moveSpeed)
{
	myData->SetAllStatus(attackRange, attack, defence, moveSpeed);
}

	void Actor::SetActorAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	myData->SetAttribute(STR, VIT, INT, MID, SPD, DEX);
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
		if (y > 0)return static_cast<uint32_t>(EXDIR::RIGHTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::RIGHTTOP);
	}
	//左方向
	else {
		if (y > 0)return static_cast<uint32_t>(EXDIR::LEFTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::LEFTTOP);
	}
	return 0;
}
void Actor::SetExDirFromInt(int dir)
{
	switch (dir)
	{
	case 0:
		myExDir = EXDIR::LEFTTOP;
		break;
	case 1:
		myExDir = EXDIR::LEFT;
		break;
	case 2:
		myExDir = EXDIR::LEFTBOTTOM;
		break;
	case 3:
		myExDir = EXDIR::BOTTOM;
		break;
	case 4:
		myExDir = EXDIR::RIGHTBOTTOM;
		break;
	case 5:
		myExDir = EXDIR::RIGHT;
		break;
	case 6:
		myExDir = EXDIR::RIGHTTOP;
		break;
	case 7:
		myExDir = EXDIR::TOP;
		break;
	default:
		break;
	}
}
void Actor::SetExDir(float x, float y)
{
	//上下左右の場合
	//上下
	if (x == 0.0f) {
		if (y > 0)myExDir = EXDIR::BOTTOM;
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
	//攻撃タイプを取得するによって発生する攻撃を変化させる
	if (myType == ATTACKTYPE::MELEE) {
		//攻撃範囲をプレイヤーの正面方向に向けて薙ぎ払う
		//左上, 右上, 左下, 右下の順で格納(回転済みの当たり判定座標)
		auto boxPos = GetMeleeAttackBox();

		//攻撃アニメーションの生成


		//敵のリストのソート　プレイヤーに近い順
		auto eManager = EnemyManager::GetInstance();
		eManager->SortEnemyList(drawPos);

		auto& list = eManager->GetEnemyList();

		bool isHit = false;

		for (auto& enemy : list) {
			//敵の座標
			auto& pos = enemy->GetPos();

			std::vector<tnl::Vector3> nearPoses;

			nearPoses.emplace_back(gManager->GetNearestPointLine(pos, boxPos[0], boxPos[1]));
			nearPoses.emplace_back(gManager->GetNearestPointLine(pos, boxPos[1], boxPos[2]));
			nearPoses.emplace_back(gManager->GetNearestPointLine(pos, boxPos[2], boxPos[3]));
			nearPoses.emplace_back(gManager->GetNearestPointLine(pos, boxPos[3], boxPos[0]));

			std::vector<float>distances;

			distances.emplace_back(gManager->GetLengthFromTwoPoint(pos, nearPoses[0]));
			distances.emplace_back(gManager->GetLengthFromTwoPoint(pos, nearPoses[1]));
			distances.emplace_back(gManager->GetLengthFromTwoPoint(pos, nearPoses[2]));
			distances.emplace_back(gManager->GetLengthFromTwoPoint(pos, nearPoses[3]));

			int mostNearNum = 0;

			for (int i = 1; i < 4; ++i) {
				if (distances[mostNearNum] > distances[i]) {
					mostNearNum = i;
				}
			}
			tnl::Vector3 mostNear = nearPoses[mostNearNum];

			//一番近い点と敵の当たり判定の円の中心との距離を求める
			float pointToCircleCenter = gManager->GetLengthFromTwoPoint(mostNear, pos);
			//この距離が敵の当たり判定の半径より小さいなら当たっている
			if (enemy->GetCircleSize() > pointToCircleCenter)isHit = true;

			//内包している場合の判定
			if (gManager->isHitRotateBox(boxPos, pos))isHit = true;
			//当たっている場合のダメージ判定
			if (isHit) {

			}

			//当たっていないキャラが来たらそれ以降も当たっていないのでやめる
			break;
		}


		//その点と範囲の4つの点のベクトルとの外積を取り、一つでも負があれば当たってない

		//上で求めた向いている方向への四角形の範囲で当たり判定を取る
		//同時に攻撃アニメーションを生成し、描画する
		//範囲内にenemyがいるかどうか判定する
		//当たってないなら処理を終える

	}
	else if (myType == ATTACKTYPE::RANGE) {

	}



}
//向いている方向の当たり判定の四角形の四点を取得する関数 左上,右上,左下,右下の順で格納する
std::vector<tnl::Vector3> Actor::GetMeleeAttackBox()
{
	//使った本人の攻撃範囲を取得する
	float myRange = myData->GetAttackRange();

	//使った本人の攻撃の幅を取得する
	float myAttackWidth = myData->GetAttackWidth();

	float left = drawPos.x - (myAttackWidth / 2);
	float right = drawPos.x + (myAttackWidth / 2);

	//上向きの四角形の攻撃範囲をデフォルトとして最初に作る
	//上向きの攻撃としての左下の点座標
	tnl::Vector3 leftBottom = { left,drawPos.y - (height / 2),0 };
	tnl::Vector3 rightBottom = { right,drawPos.y - (height / 2),0 };

	tnl::Vector3 leftTop = { left ,drawPos.y - (height / 2) - myRange,0 };
	tnl::Vector3 rightTop = { right ,drawPos.y - (height / 2) - myRange,0 };

	//キャラが向いている方向に応じて4点の座標を回転させる　中心はdrawPos
	auto fixLeftBottom = gManager->RotatePoint(leftBottom, static_cast<int>(myExDir), drawPos);
	auto fixRightBottom = gManager->RotatePoint(rightBottom, static_cast<int>(myExDir), drawPos);//当たり判定につかう

	auto fixLeftTop = gManager->RotatePoint(leftTop, static_cast<int>(myExDir), drawPos);//当たり判定につかう
	auto fixRightTop = gManager->RotatePoint(rightTop, static_cast<int>(myExDir), drawPos);

	std::vector<tnl::Vector3> vectors;
	vectors.emplace_back(fixLeftTop);
	vectors.emplace_back(fixRightTop);
	vectors.emplace_back(fixLeftBottom);
	vectors.emplace_back(fixRightBottom);

	//test 当たり判定の範囲を画像で描画
	if (!bufPos.empty()) {
		bufPos.clear();
	}
	bufPos.emplace_back(fixLeftTop);
	bufPos.emplace_back(fixRightTop);
	bufPos.emplace_back(fixLeftBottom);
	bufPos.emplace_back(fixRightBottom);

	return vectors;
}
