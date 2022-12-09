#include "Player.h"
#include"../GameManager.h"
#include"Camera.h"

Player::Player(int startX, int startY)
{
	drawPos.x = startX;
	drawPos.y = startY;
	gh = gManager->LoadGraphEx("graphics/Player.png");
	testGh = gManager->LoadGraphEx("graphics/test.png");
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
	DrawRotaGraph(x, y, 1, 0, gh, false);


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
