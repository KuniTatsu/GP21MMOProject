#include "GameManager.h"
#include "JobLevelConverter.h"
#include "JobLevelInfo.h"
#include "TalentManager.h"

JobLevelConverter* JobLevelConverter::instance = nullptr;

JobLevelConverter* JobLevelConverter::GetInstance()
{
	if (!instance) {
		instance = new JobLevelConverter();
	}
	return instance;
}

JobLevelConverter::JobLevelConverter() {
	gManager = GameManager::GetInstance();
	tManager = TalentManager::GetInstance();

	LoadCsv();
}

JobLevelConverter::~JobLevelConverter()
{
}

void JobLevelConverter::LoadCsv()
{
	auto loadCsv = tnl::LoadCsv("csv/JobLevelConverter.csv");

	for (int i = 1; i < loadCsv.size(); i++) {

		auto talentId = std::stoi(loadCsv[i][0]);				// 才能のIDを取得
		auto jobId1 = std::stoi(loadCsv[i][1]);					// 一つ目の職のIDを取得
		auto jobName1 = gManager->UTF8toSjis(loadCsv[i][2]);	// 一つ目の職の名前を取得
		auto bonusValue1 = std::stoi(loadCsv[i][3]);			// 一つ目の職のボーナス経験値を取得
		auto jobId2 = std::stoi(loadCsv[i][4]);					// 二つ目の職のIDを取得
		auto jobName2 = gManager->UTF8toSjis(loadCsv[i][5]);	// 二つ目の職の名前を取得
		auto bonusValue2 = std::stoi(loadCsv[i][6]);			// 二つ目の職のボーナス経験値を取得

		/*int TalentId, int JobId1, std::string JobName1, int BonusValue1, int JobId2, std::string JobName2, int BonusValue2*/

		auto jobLevelConverter = std::make_shared<JobLevelInfo>(talentId, jobId1, jobName1, bonusValue1, jobId2, jobName2, bonusValue2);
		jobLevelConverterMaster.emplace_back(jobLevelConverter);

	}
}
//才能IDから対応する職とボーナス値を持つクラスを返す関数
std::shared_ptr<JobLevelInfo>JobLevelConverter::GetJobLevelInfo(int talentId)
{
	if (talentId > jobLevelConverterMaster.size())return nullptr;

	//マスターから才能IDに対応するJobLevelInfoを取得する
	const auto& infoObject = jobLevelConverterMaster[talentId];
	//Infoクラスインスタンスから職とボーナス値が入ったMapオブジェクトを取得する
	const auto& infoMap = infoObject->GetInfoMap();

	//一時オブジェクトに保存
	std::vector<int>jobIds;
	std::vector<int>bonuses;
	for (auto itr = infoMap.begin(); itr != infoMap.end(); ++itr) {
		jobIds.emplace_back(itr->first);
		bonuses.emplace_back(itr->second);
	}
	//名前の取得
	const auto& names = infoObject->GetJobNames();

	return std::make_shared<JobLevelInfo>(talentId, jobIds[0], names[0], bonuses[0],
		jobIds[1], names[1], bonuses[1]);
}



