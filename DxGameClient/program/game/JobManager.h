#pragma once
#include<vector>
#include<memory>

#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>
#include<memory>

class GameManager;
class Job;

class JobManager
{
public:
	JobManager();
	~JobManager();

private:
	static JobManager* GetInstance();

	// Csvから職情報を取得する関数
	void LoadCsv();

	// Csvから職と才能の相互性を見る関数
	void  JobTargetTable();

	// Csvから職のレベル別のステータスを取得する関数
	void JobLevelStatus();

	//新しく職を取得する関数
	std::shared_ptr<Job>CreateNewJob(int id);

	// 職のレベルがあがった時の情報を取得する関数
	std::shared_ptr<Job>LevelUpJob(int id);


private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	std::vector<std::shared_ptr<Job>>jobMaster;
	//std::vector<std::shared_ptr<>
};

