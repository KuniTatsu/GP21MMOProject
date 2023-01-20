#include "ActorData.h"

ActorData::ActorData()
{
}

ActorData::~ActorData()
{
}

void ActorData::SetAllStatus(float Attack, float Defence, float MoveSpeed)
{
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

void ActorData::CalcMainStatus()
{
	/*
	ï®óùçUåÇóÕ	STR*20+DEX*5

	ñÇñ@çUåÇóÕ	INT*20+MID*5

	ï®óùñhå‰óÕ	VIT*20+SPD*5

	ñÇñ@ñhå‰óÕ	MID*20+SPD*5

	HP	VIT*20+STR*5
	*/
	attack = str * 20 + dex * 5;
	mgAttack = intelligence * 20 + mid * 5;

	defence = vit * 20 + spd * 5;
	mgDefence = mid * 20 + spd * 5;

	moveSpeed = spd * 3 - str * 2;

	HP = vit * 20 + str * 5;
}
