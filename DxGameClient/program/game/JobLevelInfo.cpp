#include"JobLevelInfo.h"

JobLevelInfo::JobLevelInfo(int JobId1, int BonusValue1, int JobId2, int BonusValue2) {
	info.insert(std::make_pair(JobId1, BonusValue1));
	info.insert(std::make_pair(JobId2, BonusValue2));
}

JobLevelInfo::~JobLevelInfo()
{
	info.clear();
}
