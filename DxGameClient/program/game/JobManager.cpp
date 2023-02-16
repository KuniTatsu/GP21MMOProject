#include "JobManager.h"
#include "Job.h"
#include "GameManager.h"
#include "JobExpCondition.h"



JobManager* JobManager::instance = nullptr;

JobManager::JobManager()
{
	gManager = GameManager::GetInstance();
	LoadCsv();
}

JobManager::~JobManager()
{
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

		auto jobLevelCondition = std::make_shared<JobExpCondition>(id, name, condition, requiredAmount, weapon, exp);
		JobExpConditionMaster.emplace_back(jobLevelCondition);
	}
}

std::shared_ptr<Job> JobManager::CreateNewJob(int jobId)
{
	if (jobId > jobMaster.size())return nullptr;


	// Job��Csv���̃f�[�^�����ׂĎ����Ă���
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

void JobManager::AddExpToJob(std::shared_ptr<Job> job, int jobId, int addExp)
{
	//�����܂��Ă���o���l���擾
	int nowExp = job->GetNowExp();
	//���̃��x���܂ŕK�v�Ȍo���l���擾
	int needExp = needExpMaster[jobId]->GetNeedExp();

	//���݂̃��x�����擾
	int nowLevel = job->GetNowLevel();

	//���x���ɉ������K�v�o���l���擾 �W���͌�Ō���
	int fixNeedExp = needExp + 20 * (nowLevel + 1);

	
	//�o���l�𑫂�
	int addedExp = nowExp + addExp;
	//�����K�v�o���l�������Ă����烌�x������グ�āA�I�[�o�[�t���[�����o���l���Z�b�g����
	if (fixNeedExp <= addedExp) {
		job->LevelUp();
		int overExp = addedExp - fixNeedExp;
		job->SetNowExp(overExp);
	}
	//���x���A�b�v���Ȃ�
	else {
		job->SetNowExp(addedExp);
	}
}

void JobManager::GetJobToWeapon(std::shared_ptr<Job> job, int WeaponId)
{
	int weapon = 0;
	//std::vector<int> jobId;
	int jobId = 0;

	//// ����̏����̐E���擾����
	for (int i = 1; i > JobExpConditionMaster.size(); i++) {
		weapon = JobExpConditionMaster[i]->GetWeaponId();
		if (WeaponId == weapon) {
			jobId = JobExpConditionMaster[i]->GetJobId();
			//jobId = static_cast <std::vector<int>>(JobExpConditionMaster[i]->GetJobId());
		};
	}
}

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


