#include "Effect.h"


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
