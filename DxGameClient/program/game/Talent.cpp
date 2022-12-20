#include "Talent.h"


Talent::Talent(int talentId, std::string talentName, int talentRare, int lowestRank,
	int addSTR, int addVIT, int addINT, int addMIN, int addSPD, int addDEX, int thisRank)
{

	//‘ã“ü
	id = talentId;
	name = talentName;
	rare = talentRare;
	lowestTalentRank = lowestRank;
	str = addSTR;
	vit = addVIT;
	intelligence = addINT;
	min = addMIN;
	spd = addSPD;
	dex = addDEX;

	rank = thisRank;
	//SetFixStatus();
}

Talent::~Talent()
{
}

void Talent::SetFixStatus()
{

	float fixValue = static_cast<float>(rank / 10.0f);

	fixStr = static_cast<int>(str * fixValue);
	fixVit = static_cast<int>(vit * fixValue);
	fixInt = static_cast<int>(intelligence * fixValue);
	fixMin = static_cast<int>(min * fixValue);
	fixSpd = static_cast<int>(spd * fixValue);
	fixDex = static_cast<int>(dex * fixValue);

	if ((fixStr + fixVit + fixInt + fixMin + fixSpd + fixDex) <= 0) {
		int hoge = 0;
		hoge++;
	}

}
