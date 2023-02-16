#pragma once
#include<vector>
#include<memory>

class GameManager;
class Job;

class JobManager
{
public:
	static JobManager* GetInstance();
private:
	JobManager();
	~JobManager();
	// Csvから職情報を取得する関数
	void LoadCsv();

private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	std::vector<std::shared_ptr<Job>>jobMaster;
};

