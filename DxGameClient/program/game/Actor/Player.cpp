#include "Player.h"
#include"../GameManager.h"
#include"Camera.h"
#include"../Talent.h"
#include"../TalentManager.h"

Player::Player(int startX, int startY)
{
	drawPos.x = startX;
	drawPos.y = startY;
	gh = gManager->LoadGraphEx("graphics/Player.png");

	SetTalent();
}

Player::~Player()
{

}

void Player::Update()
{
	Move();
}

void Player::Draw(Camera* camera)
{
	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);
	DrawRotaGraph(x, y, 1, 0, gh, false);
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

	}

	//gManager->SetStayMap();
	if (gManager->IsOverChunk()) {
		gManager->CreateMap();
		gManager->SetStayMap();
	}
}
