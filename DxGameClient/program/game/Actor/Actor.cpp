#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"
#include"../EnemyManager.h"
#include"Enemy.h"
#include"Player.h"
#include"../BattleLogic.h"
#include"../EffectManager.h"
#include<math.h>

#include"../scene/Map.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
	myData = std::make_shared<ActorData>();
	SetDefaultAttackOffset();
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

void Actor::SetActorData(float attack, float defence, float moveSpeed)
{
	myData->SetAllStatus(attack, defence, moveSpeed);
}

void Actor::SetActorAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	myData->SetAttribute(STR, VIT, INT, MID, SPD, DEX);
}

void Actor::SetCircleSize(tnl::Vector3& size)
{
	if (size.x >= size.y)circleSize = size.x / 2;
	else circleSize = size.y / 2;
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

bool Actor::HitMaptoCharacter(tnl::Vector3& pos)
{
	/*auto& player = GameManager::GetInstance()->GetPlayer();
	tnl::Vector3& characterPos = player->GetPos();*/

	auto map = GameManager::GetInstance()->GetPlayerOnMap();

	auto& hitMap = map->GetHitMap();

	auto x = std::floor(pos.x / 32);
	auto y = std::floor(pos.y / 32);

	tnl::Vector3 localPos = (tnl::Vector3(x+1, y+1, 0));

	if (hitMap[localPos.y+17][localPos.x+17] == 65)return false;
	return true;
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
tnl::Vector3 Actor::GetNearestPoint(tnl::Vector3& Pos, std::vector<tnl::Vector3>& boxPos)
{
	std::vector<tnl::Vector3> nearPoses;

	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[0], boxPos[1]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[1], boxPos[2]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[2], boxPos[3]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[3], boxPos[0]));

	std::vector<float>distances;

	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[0]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[1]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[2]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[3]));

	int mostNearNum = 0;

	for (int i = 1; i < 4; ++i) {
		if (distances[mostNearNum] > distances[i]) {
			mostNearNum = i;
		}
	}
	return nearPoses[mostNearNum];
}
void Actor::SetDefaultAttackOffset()
{
	auto range = myData->GetAttackRange();

	EFFECTOFFSET[static_cast<int>(EXDIR::LEFTTOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(225)), (range / 2) * std::sin(tnl::ToRadian(225)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::LEFT)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(180)), (range / 2) * std::sin(tnl::ToRadian(180)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::LEFTBOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(135)), (range / 2) * std::sin(tnl::ToRadian(135)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::BOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(90)), (range / 2) * std::sin(tnl::ToRadian(90)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHTBOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(45)), (range / 2) * std::sin(tnl::ToRadian(45)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHT)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(0)), (range / 2) * std::sin(tnl::ToRadian(0)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHTTOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(315)), (range / 2) * std::sin(tnl::ToRadian(315)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::TOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(270)), (range / 2) * std::sin(tnl::ToRadian(270)), 0);

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
void Actor::SetExDir(int dir)
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
//通常攻撃関数
void Actor::DefaultAttack()
{
	//攻撃した直後なら行動を行わない
	if (attackInterval > 0.0f)return;

	//攻撃者
	std::shared_ptr<Actor> attackActor = shared_from_this();
	//防衛者
	std::vector<std::shared_ptr<Actor>> defendActor;
	defendActor.clear();

	//攻撃タイプを取得するによって発生する攻撃を変化させる
	if (myType == ATTACKTYPE::MELEE) {
		//攻撃範囲をプレイヤーの正面方向に向けて薙ぎ払う
		//左上, 右上, 左下, 右下の順で格納(回転済みの当たり判定座標)
		auto boxPos = GetMeleeAttackBox();


		//auto animPos = tnl::Vector3(50, 50, 0);

		//攻撃アニメーションの生成

		auto animPos = drawPos + EFFECTOFFSET[static_cast<int>(myExDir)];
		EffectManager::GetInstance()->CreateEffect(static_cast<int>(EffectManager::EFFECTTYPE::NORMAL), animPos);

		//インターバルセット
		attackInterval = canAttackTime;

		bool isHit = false;

		//攻撃者がプレイヤーの場合
		if (actorType == 0) {

			//敵のリストのソート　プレイヤーに近い順
			auto eManager = EnemyManager::GetInstance();
			eManager->SortEnemyList(drawPos);

			auto& list = eManager->GetEnemyList();

			for (auto& enemy : list) {
				//敵の座標
				auto& pos = enemy->GetPos();
				//判定用の一番近い点を求める
				tnl::Vector3 mostNear = GetNearestPoint(pos, boxPos);

				//一番近い点と敵の当たり判定の円の中心との距離を求める
				float pointToCircleCenter = gManager->GetLengthFromTwoPoint(mostNear, pos);
				//この距離が敵の当たり判定の半径より小さいなら当たっている
				if (enemy->GetCircleSize() > pointToCircleCenter)isHit = true;
				else {
					//内包している場合の判定
					if (gManager->isHitRotateBox(boxPos, pos))isHit = true;
				}

				//当たっている場合ダメージ判定対象に入れる
				if (isHit) {
					defendActor.emplace_back(enemy);
					isHit = false;
					continue;
					//bool successAttack = BattleLogic::GetInstance()->IsSuccessAttack();
				}
				//当たっていないキャラが来たらそれ以降も当たっていないのでやめる
				break;
			}
		}
		//enemyが攻撃者の場合
		else {
			auto& player = GameManager::GetInstance()->GetPlayer();
			auto& pos = player->GetPos();

			//判定用の一番近い点を求める
			tnl::Vector3 mostNear = GetNearestPoint(pos, boxPos);

			//一番近い点と敵の当たり判定の円の中心との距離を求める
			float pointToCircleCenter = gManager->GetLengthFromTwoPoint(mostNear, pos);
			//この距離が敵の当たり判定の半径より小さいなら当たっている
			if (player->GetCircleSize() > pointToCircleCenter)isHit = true;

			//内包している場合の判定
			if (gManager->isHitRotateBox(boxPos, pos))isHit = true;
			//当たっている場合ダメージ判定対象に入れる
			if (isHit)defendActor.emplace_back(player);

			//bool successAttack = BattleLogic::GetInstance()->IsSuccessAttack();
		}
	}
	else if (myType == ATTACKTYPE::RANGE) {

	}

	auto attackData = attackActor->GetActorData();

	for (auto& defender : defendActor) {
		auto defendData = defender->GetActorData();

		auto battleLogic = BattleLogic::GetInstance();

		//ダメージ判定
		bool successAttack = battleLogic->IsSuccessAttack(attackData, defendData, static_cast<int>(myType));

		double damage = battleLogic->CalcDefaultDamage(attackData->GetAttack(), defendData->GetDefence(), attackData->GetLevel(), successAttack);
		if (defendData->UpdateHp((damage * (-1)))) {
			//trueで帰ってきたら死んでるので、isliveを変える
			defender->SetIsLive(false);
		}
	}
}
void Actor::UpdateAttackInterval(const float deltatime)
{
	//インターバルが0以下なら減らさない
	if (attackInterval <= 0.0f) return;

	//インターバル更新
	attackInterval -= deltatime;
	//マイナスになっていたら0にする
	if (attackInterval < 0.0f) attackInterval = 0.0f;
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
