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

	//debug用
	std::shared_ptr<Job>CreateDebugJob(int jobId, int startJobLevel = 10);

	//何らかの行動で職の経験値が発生したときに呼ぶ関数
	bool UpdateJobInfo(int condition = 0);

	//ジョブに経験値を与える際のコンディション
	enum class CONDITIONS :uint32_t {
		NONE,
		KILL,
		KILLWEAPON,
		USEITEM,
		GETITEM,
		MOVE,
		MAKEITEM,
		TRADE,
		MAX

	};
private:
	JobManager();
	~JobManager();


	//特定のJobに経験値を足す関数
	void AddExpToJob(int jobId, int addExp);

	// 武器により経験値を上げることのできる職を取得する関数
	std::vector<std::shared_ptr<Job>> GetJobFromWeapon(int WeaponId);

	//  職によりそれに対する経験値を取得する関数
	// void GetExpToJob(std::vector<int> jobId);


private:

	// Csvから職情報を取得する関数
	void LoadCsv();

	// Csvから職の経験値情報を取得する関数
	void LoadCsvJobLevelExp();

	// Csvから経験値を取得するための特定の条件を取得する関数
	void LoadCsvJobLevelCondition();


	//コンディション:killのチェック関数
	bool CheckConditionKill(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs);

	//コンディション:killWeaponのチェック関数
	bool CheckConditionKillWeapon(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs);

	//コンディション:useItemのチェック関数
	bool CheckConditionUseItem();

	//コンディション:getItemのチェック関数
	bool CheckConditionGetItem();

	//コンディション:moveのチェック関数
	bool CheckConditionMove();
private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	// 職のステータス格納
	std::vector<std::shared_ptr<Job>>jobMaster;
	// 職の必要経験値格納
	std::vector < std::shared_ptr<JobNeedExpData>> needExpMaster;
	// 特定の条件で経験値を与える情報のクラス配列
	std::vector < std::shared_ptr<JobExpCondition> > JobExpConditionMaster;

	//コンディションを満たした職業のジョブIdを入れる一時保存用配列
	std::vector<std::shared_ptr<JobExpCondition>>doneCondition = {};

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
