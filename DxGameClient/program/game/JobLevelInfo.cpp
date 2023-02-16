#include"JobLevelInfo.h"

JobLevelInfo::JobLevelInfo(int TalentId, int JobId1, std::string JobName1, int BonusValue1, int JobId2, std::string JobName2, int BonusValue2) {

	talentId = TalentId;

	names.emplace_back(JobName1);
	names.emplace_back(JobName2);

	info.insert(std::make_pair(JobId1, BonusValue1));
	info.insert(std::make_pair(JobId2, BonusValue2));
}

JobLevelInfo::~JobLevelInfo()
{
	info.clear();
}
