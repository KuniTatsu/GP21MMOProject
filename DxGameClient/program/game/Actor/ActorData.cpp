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

void ActorData::SetAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	str = STR;
	vit = VIT;
	intelligence = INT;
	mid = MID;
	spd = SPD;
	dex = DEX;


	attribute.emplace_back(STR);
	attribute.emplace_back(VIT);
	attribute.emplace_back(INT);
	attribute.emplace_back(MID);
	attribute.emplace_back(SPD);
	attribute.emplace_back(DEX);
}
