#pragma once

class GameManager;
class JobLevelInfo;
class TalentManager;

class JobLevelConverter {
public:
	// インスタンスの取得
	static JobLevelConverter* GetInstance();
	// 才能に対する職のボーナス値の取得
	std::shared_ptr<JobLevelInfo>GetJobLevelInfo(int talentId);


private:
	JobLevelConverter();
	~JobLevelConverter();
	// 才能と職の対応表 CSV のロード関数
	void LoadCsv();


private:
	static JobLevelConverter* instance;
	GameManager* gManager = nullptr;
	TalentManager* tManager = nullptr;
	std::vector<std::shared_ptr<JobLevelInfo>>jobLevelConverterMaster;

};