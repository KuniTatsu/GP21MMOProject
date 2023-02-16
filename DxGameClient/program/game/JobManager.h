#pragma once
#include<vector>
#include<memory>

#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>
#include<memory>

class GameManager;
class Job;
class JobNeedExpData;
class JobExpCondition;

class JobManager
{
public:
	static JobManager* GetInstance();

	inline int GetJobMasterCount() {
		return jobMaster.size();
	}

	//新しく職を取得する関数
	std::shared_ptr<Job>CreateNewJob(int jobId);
private:
	JobManager();
	~JobManager();

	//特定のJobに経験値を足す関数
	void AddExpToJob(std::shared_ptr<Job> job,int jobId, int addExp);

	// 武器により経験値を上げることのできる職を取得する関数
	void GetJobToWeapon(std::shared_ptr<Job> job, int WeaponId);

	//  職によりそれに対する経験値を取得する関数
	// void GetExpToJob(std::vector<int> jobId);

	

private:

	// Csvから職情報を取得する関数
	void LoadCsv();

	// Csvから職の経験値情報を取得する関数
	void LoadCsvJobLevelExp();

	// Csvから経験値を取得するための特定の条件を取得する関数
	void LoadCsvJobLevelCondition();

private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	// 職のステータス格納
	std::vector<std::shared_ptr<Job>>jobMaster;
	// 職の必要経験値格納
	std::vector < std::shared_ptr<JobNeedExpData>> needExpMaster;
	// 特定の行動で職のレベルを取得データを格納
	std::vector < std::shared_ptr<JobExpCondition> > JobExpConditionMaster;
};



class JobNeedExpData
{
public:
	JobNeedExpData(int Id, std::string Name, int NeedExp);
	~JobNeedExpData();

	inline int GetJobId() {
		return id;
	}

	inline std::string GetJobName() {
		return name;
	}

	inline int GetNeedExp() {
		return needExp;
	}

private:

	int id = 0;
	std::string name = "";

	int needExp = 0;

};
