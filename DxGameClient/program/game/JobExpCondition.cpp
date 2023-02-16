#include "JobExpCondition.h"


JobExpCondition::JobExpCondition(int JobId, std::string Name, int Condition, int RequiredAmount, int Exp)
{
	jobId = JobId;
	name = Name;
	condition = Condition;
	requiredAmount = RequiredAmount;
	exp = Exp;
}

JobExpCondition::~JobExpCondition()
{
}
