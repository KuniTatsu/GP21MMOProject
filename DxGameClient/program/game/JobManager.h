#pragma once
#include<memory>
#include<vector>

class GameManager;
class Job;

class JobManager
{
public:
	JobManager();
	~JobManager();

private:
	static JobManager* GetInstance();

	// Csv����E�����擾����֐�
	void LoadCsv();

private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	std::vector<std::shared_ptr<Job>>jobMaster;
};

