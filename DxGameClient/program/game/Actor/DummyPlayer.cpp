#include "DummyPlayer.h"
#include"Camera.h"
#include"../GameManager.h"

DummyPlayer::DummyPlayer(float posX, float posY)
{
	drawPos.x = posX;
	drawPos.y = posY;
}

DummyPlayer::~DummyPlayer()
{
}

void DummyPlayer::Draw(Camera* camera)
{
	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);
	DrawRotaGraph(x, y, 1, 0, gh, false);
}

void DummyPlayer::SetGh(std::string ghPass)
{
	gManager->LoadDivGraphEx(ghPass, 4, 4, 1, 32, 32, ghs);
}

void DummyPlayer::UpdatePosition(float posX, float posY)
{
	drawPos.x = posX;
	drawPos.y = posY;
}
