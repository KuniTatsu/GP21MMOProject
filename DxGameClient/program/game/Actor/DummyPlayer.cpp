#include "DummyPlayer.h"
#include"Camera.h"
#include"../GameManager.h"
#include"../ResourceManager.h"
#include"ActorData.h"

DummyPlayer::DummyPlayer(float posX, float posY, std::string UUID, int dir, float HP, int ghNum)
{
	drawPos.x = posX;
	drawPos.y = posY;
	auto rManager = ResourceManager::GetInstance();
	ghs = rManager->GetCharaVectorAtGhNum(ghNum);
	myUUID = UUID;
	SetExDirFromInt(dir);

	myData = std::make_shared<ActorData>();
	myData->SetHP(HP);
}

DummyPlayer::~DummyPlayer()
{
}

void DummyPlayer::Update()
{
}

void DummyPlayer::Draw(Camera* camera)
{
	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);
	//アニメーション更新
	Anim(ghs, 3);
	DrawRotaGraphF(x, y, 1, 0, drawGh, true);
}

void DummyPlayer::Init()
{
}


void DummyPlayer::SetGh(std::string ghPass)
{
	gManager->LoadDivGraphEx(ghPass, 4, 4, 1, 32, 32, ghs);
}

void DummyPlayer::UpdatePosition(float posX, float posY, int dir)
{
	SetExDirFromInt(dir);

	drawPos.x = posX;
	drawPos.y = posY;
}
