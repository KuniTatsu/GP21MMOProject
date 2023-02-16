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
//�O����ĂԐE�̍X�V�֐�
bool JobManager::UpdateJobInfo(int condition)
{
	//�R���f�B�V����Id�ɑΉ�����R���f�B�V�����I�u�W�F�N�g���擾
	std::vector<std::shared_ptr<JobExpCondition>> conditions;

	for (int i = 0; i < JobExpConditionMaster.size(); ++i) {
		if (condition == JobExpConditionMaster[i]->GetCondition()) {
			conditions.emplace_back(JobExpConditionMaster[i]);
		}
	}

	//player�̐E�ƈꗗ
	auto& jobs = GameManager::GetInstance()->GetPlayerJobs();

	bool isContain = false;

	switch (condition)
	{
		//�������Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::NONE):

		break;
		//kill�Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::KILL):
		isContain = CheckConditionKill(conditions, jobs);
		break;
		//�������Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::KILLWEAPON):
		isContain = CheckConditionKillWeapon(conditions, jobs);
		break;
		//�������Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::USEITEM):

		break;
		//�������Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::GETITEM):

		break;
		//�������Ōo���l�ǉ�
	case static_cast<int>(CONDITIONS::MOVE):

		break;
	default:
		break;
	}

	//��ł��o���l���グ��Ώۂ����邩
	if (isContain) {
		for (int i = 0; i < doneCondition.size(); ++i) {
			//jobID
			int jobId = doneCondition[i]->GetJobId();

			//�����o���l
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
	//�����Ă����R���f�B�V�����̕K�v�������ƃv���C���[�W���u�̓��������ׂāA�������Ă����炨�����X�g�ɓ����
	for (int i = 0; i < conditions.size(); ++i) {
		int needKillCount = conditions[i]->GetRequiredAmount();
		//debug
		std::string jobName = conditions[i]->GetJobName();

		//�v���C���[�̐E�̍��̃L���J�E���g
		int nowKillCount = playerJobs[i]->GetMonsterKills();

		if (needKillCount <= nowKillCount) {
			doneCondition.emplace_back(conditions[i]);

			//�L���J�E���g�����Z�b�g����
			playerJobs[i]->ResetKillCount();

			isContain = true;
		}
	}
	return isContain;
}

bool JobManager::CheckConditionKillWeapon(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs)
{
	bool isContain = false;
	//�����Ă����R���f�B�V�����̕K�v�������ƃv���C���[�W���u�̓��������ׂāA�������Ă����炨�����X�g�ɓ����
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

std::shared_ptr<Job> JobManager::CreateDebugJob(int jobId, int startJobLevel)
{
	std::shared_ptr<Job> buf = nullptr;
	for (int i = 0; i < jobMaster.size(); ++i) {
		if (jobMaster[i]->GetId() == jobId) {
			buf = jobMaster[i];
		}
	}

	if (buf == nullptr)return nullptr;

	// Job��Csv���̃f�[�^�����ׂĎ����Ă���
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
	//jobId����Ή����鍡�̃v���C���[�̐E���擾����
	auto& job = GameManager::GetInstance()->GetPlayer()->GetmyJobs()[jobId];


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

//std::vector<std::shared_ptr<Job>>JobManager::GetJobFromWeapon(int WeaponId)
//{
//	int weapon = 0;
//	//std::vector<int> jobId;
//	int jobId = 0;
//
//	//// ����̏����̐E���擾����
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


