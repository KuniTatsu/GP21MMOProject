#include "Effect.h"
#include"Actor/Camera.h"
#include"GameManager.h"


Effect::Effect(std::vector<int>& Anim, tnl::Vector3& Pos, int Id, int MaxIndex, float ActSpeed)
{
	animGh = Anim;
	pos = Pos;
	id = Id;
	maxMotionIndex = MaxIndex;
	actSpeed = ActSpeed;
}

Effect::Effect(int Id, int MaxIndex, float ActSpeed)
{
	id = Id;
	maxMotionIndex = MaxIndex;
	actSpeed = ActSpeed;
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if (--actWait <= 0) {
		actIndex++;
		actWait = actSpeed;
		actIndex %= maxMotionIndex;
	}
	else return;

	drawGh = animGh[actIndex];

	if (drawGh == animGh[maxMotionIndex - 1])isAlive = false;
}

void Effect::Draw(Camera* camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraphF(pos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1), pos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1, 0, drawGh, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
