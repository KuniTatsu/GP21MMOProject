#include "JobManager.h"
#include "Job.h"
#include "GameManager.h"
#include "JobExpCondition.h"
#include"Actor/Player.h"
#include"Item/EquipItem.h"



JobManager* JobManager::instance = nullptr;

JobManager::JobManager()
{
	gManager = GameManager::GetInstance();
	LoadCsv();
	doneCondition.clear();
}

JobManager::~JobManager()
{
}
//外から呼ぶ職の更新関数
bool JobManager::UpdateJobInfo(int condition)
{
	//コンディションIdに対応するコンディションオブジェクトを取得
	std::vector<std::shared_ptr<JobExpCondition>> conditions;

	for (int i = 0; i < JobExpConditionMaster.size(); ++i) {
		if (condition == JobExpConditionMaster[i]->GetCondition()) {
			conditions.emplace_back(JobExpConditionMaster[i]);
		}
	}

	//playerの職業一覧
	auto& jobs = GameManager::GetInstance()->GetPlayerJobs();

	bool isContain = false;

	switch (condition)
	{
		//無条件で経験値追加
	case static_cast<int>(CONDITIONS::NONE):

		break;
		//killで経験値追加
	case static_cast<int>(CONDITIONS::KILL):
		isContain = CheckConditionKill(conditions, jobs);
		break;
		//無条件で経験値追加
	case static_cast<int>(CONDITIONS::KILLWEAPON):
		isContain = CheckConditionKillWeapon(conditions, jobs);
		break;
		//無条件で経験値追加
	case static_cast<int>(CONDITIONS::USEITEM):

		break;
		//無条件で経験値追加
	case static_cast<int>(CONDITIONS::GETITEM):

		break;
		//無条件で経験値追加
	case static_cast<int>(CONDITIONS::MOVE):

		break;
	default:
		break;
	}

	//一つでも経験値を上げる対象があるか
	if (isContain) {
		for (int i = 0; i < doneCondition.size(); ++i) {
			//jobID
			int jobId = doneCondition[i]->GetJobId();

			//足す経験値
			int addExp = doneCondition[i]->GetExp();

			AddExpToJob(jobId, addExp);
		}
	}
	return false;
}

JobManager* JobManager::GetInstance()
{
	if (!instance) {
		instance = new JobManager();
	}
	return instance;
}

void JobManager::LoadCsv()
{
	auto loadCsv = tnl::LoadCsv("csv/JobMaster.csv");

	for (int i = 1; i < loadCsv.size(); ++i) {
		auto id = std::stoi(loadCsv[i][0]);
		auto& name = loadCsv[i][1];
		auto str = std::stoi(loadCsv[i][2]);
		auto vit = std::stoi(loadCsv[i][3]);
		auto inteli = std::stoi(loadCsv[i][4]);
		auto min = std::stoi(loadCsv[i][5]);
		auto spd = std::stoi(loadCsv[i][6]);
		auto dex = std::stoi(loadCsv[i][7]);

		auto job = std::make_shared<Job>(id, name, str, vit, inteli, min, spd, dex);
		jobMaster.emplace_back(job);
	}
}

void JobManager::LoadCsvJobLevelExp()
{
	auto loadCsv = tnl::LoadCsv("csv/JobLevelExpMaster.csv");

	for (int i = 1; i < loadCsv.size(); ++i) {
		int id = std::stoi(loadCsv[i][0]);
		auto& name = loadCsv[i][1];
		int needExp = std::stoi(loadCsv[i][2]);

		auto needExpData = std::make_shared<JobNeedExpData>(id, name, needExp);
		needExpMaster.emplace_back(needExpData);
	}
}

void JobManager::LoadCsvJobLevelCondition()
{
	auto loadCsv = tnl::LoadCsv("csv/JobLevelConditionMaster.csv");

	for (int i = 1; i < loadCsv.size(); ++i) {
		int id = std::stoi(loadCsv[i][0]);
		auto& name = loadCsv[i][1];
		int condition = std::stoi(loadCsv[i][2]);
		int requiredAmount = std::stoi(loadCsv[i][3]);
		int weapon = std::stoi(loadCsv[i][4]);
		int exp = std::stoi(loadCsv[i][5]);

		auto jobLevelCondition = std::make_shared<JobExpCondition>(id, name, condition, requiredAmount, exp);

		if (weapon != -1)jobLevelCondition->SetWeaponId(weapon);

		JobExpConditionMaster.emplace_back(jobLevelCondition);
	}
}

bool JobManager::CheckConditionKill(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs)
{
	bool isContain = false;
	//持ってきたコンディションの必要討伐数とプレイヤージョブの討伐数を比べて、満たしていたらおｋリストに入れる
	for (int i = 0; i < conditions.size(); ++i) {
		int needKillCount = conditions[i]->GetRequiredAmount();
		//debug
		std::string jobName = conditions[i]->GetJobName();

		//プレイヤーの職の今のキルカウント
		int nowKillCount = playerJobs[i]->GetMonsterKills();

		if (needKillCount <= nowKillCount) {
			doneCondition.emplace_back(conditions[i]);

			//キルカウントをリセットする
			playerJobs[i]->ResetKillCount();

			isContain = true;
		}
	}
	return isContain;
}

bool JobManager::CheckConditionKillWeapon(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs)
{
	bool isContain = false;
	//持ってきたコンディションの必要討伐数とプレイヤージョブの討伐数を比べて、満たしていたらおｋリストに入れる
	for (int i = 0; i < conditions.size(); ++i) {



	}


	return isContain;
}

bool JobManager::CheckConditionUseItem()
{
	return false;
}

bool JobManager::CheckConditionGetItem()
{
	return false;
}

bool JobManager::CheckConditionMove()
{
	return false;
}

std::shared_ptr<Job> JobManager::CreateNewJob(int jobId)
{
	if (jobId > jobMaster.size())return nullptr;

	// JobのCsv内のデータをすべて持ってくる
	auto id = jobMaster[jobId]->GetId();
	auto& name = jobMaster[jobId]->GetName();
	auto str = jobMaster[jobId]->GetStr();
	auto vit = jobMaster[jobId]->GetVit();
	auto inteli = jobMaster[jobId]->GetInt();
	auto min = jobMaster[jobId]->GetMin();
	auto spd = jobMaster[jobId]->GetSpd();
	auto dex = jobMaster[jobId]->GetDex();

	return std::make_shared<Job>(id, name, str, vit, inteli, min, spd, dex);
}

std::shared_ptr<Job> JobManager::CreateDebugJob(int jobId, int startJobLevel)
{
	std::shared_ptr<Job> buf = nullptr;
	for (int i = 0; i < jobMaster.size(); ++i) {
		if (jobMaster[i]->GetId() == jobId) {
			buf = jobMaster[i];
		}
	}

	if (buf == nullptr)return nullptr;

	// JobのCsv内のデータをすべて持ってくる
	auto id = buf->GetId();
	auto& name = buf->GetName();
	auto str = buf->GetStr();
	auto vit = buf->GetVit();
	auto inteli = buf->GetInt();
	auto min = buf->GetMin();
	auto spd = buf->GetSpd();
	auto dex = buf->GetDex();

	return std::make_shared<Job>(id, name, str, vit, inteli, min, spd, dex, startJobLevel);
}

void JobManager::AddExpToJob(int jobId, int addExp)
{
	//jobIdから対応する今のプレイヤーの職を取得する
	auto& job = GameManager::GetInstance()->GetPlayer()->GetmyJobs()[jobId];


	//今たまっている経験値を取得
	int nowExp = job->GetNowExp();
	//次のレベルまで必要な経験値を取得
	int needExp = needExpMaster[jobId]->GetNeedExp();

	//現在のレベルを取得
	int nowLevel = job->GetNowLevel();

	//レベルに応じた必要経験値を取得 係数は後で決定
	int fixNeedExp = needExp + 20 * (nowLevel + 1);


	//経験値を足す
	int addedExp = nowExp + addExp;
	//もし必要経験値を上回っていたらレベルを一つ上げて、オーバーフローした経験値をセットする
	if (fixNeedExp <= addedExp) {
		job->LevelUp();
		int overExp = addedExp - fixNeedExp;
		job->SetNowExp(overExp);
	}
	//レベルアップしない
	else {
		job->SetNowExp(addedExp);
	}
}

//std::vector<std::shared_ptr<Job>>JobManager::GetJobFromWeapon(int WeaponId)
//{
//	int weapon = 0;
//	//std::vector<int> jobId;
//	int jobId = 0;
//
//	//// 特定の条件の職を取得する
//	for (int i = 1; i < JobExpConditionMaster.size(); i++) {
//		weapon = JobExpConditionMaster[i]->GetWeaponId();
//		if (WeaponId == weapon) {
//			jobId = JobExpConditionMaster[i]->GetJobId();
//			//jobId = static_cast <std::vector<int>>(JobExpConditionMaster[i]->GetJobId());
//		};
//	}
//}

//void JobManager::GetExpToJob(std::vector<int> jobId)
//{
//	
//}

JobNeedExpData::JobNeedExpData(int Id, std::string Name, int NeedExp)
{
	id = Id;
	name = Name;
	needExp = NeedExp;
}

JobNeedExpData::~JobNeedExpData()
{
}


