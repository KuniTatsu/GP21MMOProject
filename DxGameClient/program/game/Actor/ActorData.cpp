#include "ActorData.h"

ActorData::ActorData()
{
}

ActorData::~ActorData()
{
}

void ActorData::SetAllStatus(double AttackRange, float Attack, float Defence, float MoveSpeed)
{
	attackRange = AttackRange;
	attack = Attack;
	defence = Defence;
	moveSpeed = MoveSpeed;
}
