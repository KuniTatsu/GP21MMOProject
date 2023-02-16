#include "JobExpCondition.h"


JobExpCondition::JobExpCondition(int JobId, std::string Name, int Condition, int RequiredAmount, int Weapon, int Exp)
{
	jobId = JobId;
	name = Name;
	condition = Condition;
	requiredAmount = RequiredAmount;
	weaponId = Weapon;
	exp = Exp;
}

JobExpCondition::~JobExpCondition()
{
}
