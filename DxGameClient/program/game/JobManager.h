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
	// Csv‚©‚çEî•ñ‚ğæ“¾‚·‚éŠÖ”
	void LoadCsv();

private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	std::vector<std::shared_ptr<Job>>jobMaster;
};

