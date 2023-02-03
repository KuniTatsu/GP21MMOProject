#include "Player.h"
#include"../GameManager.h"
#include"Camera.h"
#include"../Talent.h"
#include"../TalentManager.h"
#include"../ResourceManager.h"
#include"ActorData.h"

Player::Player(int startX, int startY, int type)
{
	drawPos.x = static_cast<float>(startX);
	drawPos.y = static_cast<float>(startY);
	gh = gManager->LoadGraphEx("graphics/Player.png");

	testGh = gManager->LoadGraphEx("graphics/test.png");

	auto rManager = ResourceManager::GetInstance();
	ghs = rManager->GetCharaVectorAtGhNum(type);

	SetTalent();

	myData = std::make_shared<ActorData>();

	myData->SetAttribute(2000, 2000, 2000, 50, 50, 2000);
	myData->CalcMainStatus();

	auto& hoge = ResourceManager::GetInstance()->GetGraphicSize(static_cast<int>(ResourceManager::RESOUCETYPE::PLAYER));

	SetCircleSize(hoge[type]);

}

Player::~Player()
{

}

void Player::Update()
{
	Move();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		DefaultAttack();
	}

}

void Player::Draw(Camera* camera)
{


	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	DrawRotaGraphF(x, y, 1, 0, gh, false);

	if (bufPos.empty())return;

	//test 当たり判定の範囲を画像で描画
	float boxX1 = bufPos[0].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY1 = bufPos[0].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX2 = bufPos[1].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY2 = bufPos[1].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX3 = bufPos[2].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY3 = bufPos[2].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX4 = bufPos[3].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY4 = bufPos[3].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	//DrawBox(boxX1, boxY1, boxX2, boxY2, -1, true);

	/*DrawExtendGraph(boxX1, boxY1, boxX2, boxY2, testGh, true);*/
	//左上、右上、右下、左下の頂点の座標 
	DrawModiGraphF(boxX1, boxY1, boxX2, boxY2, boxX4, boxY4, boxX3, boxY3, testGh, true);
}

void Player::Init()
{
}
//才能の付与 ※レア度によるウェイトがかかってない完全ランダムでの選択なので要修正
void Player::SetTalent()
{
	auto talentManager = TalentManager::GetInstance();
	std::vector<int>talentIds;

	while (remainRankNum > 0) {

		auto talent = talentManager->GetNewTalent(remainRankNum, talentIds);
		talent->SetFixStatus();
		myTalents.emplace_back(talent);
		talentIds.emplace_back(talent->GetId());

		MinusRemainRank(talent->GetThisRank());
	}
	int hoge = 0;
	hoge++;
}

void Player::Move()
{
	//移動量リセット
	moveX = 0;
	moveY = 0;

	//どうにかしてまとめたい　関数化したいがうまく思いつかない
	//上下キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
		//myDir = DIR::UP;
		DrawStringEx(200, 300, -1, "UP");
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
		//myDir = DIR::DOWN;
	}

	//左右キー感知
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
		//myDir = DIR::RIGHT;
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
		//myDir = DIR::LEFT;
		DrawStringEx(200, 400, -1, "LEFT");
	}
	if (moveX == 0 && moveY == 0)return;

	//移動量が0でなければベクトルを正規化して移動させる
	if (moveX != 0 || moveY != 0) {
		//単位ベクトル取得
		tnl::Vector3 fixVec = gManager->GetFixVector(moveX, moveY);

		//速度倍
		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		//座標移動
		drawPos.x += fixMoveX;
		drawPos.y += fixMoveY;

		//向き変更
		SetExDir(fixMoveX, fixMoveY);


#ifdef DEBUG_OFF
		gManager->SendPlayerInfoToServer();
#endif

	}

	//gManager->SetStayMap();
	if (gManager->IsOverChunk()) {
		gManager->CreateMap();
		gManager->SetStayMap();
	}
}
