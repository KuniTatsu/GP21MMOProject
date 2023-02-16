#include "GameManager.h"
#include "JobLevelConverter.h"
#include "JobLevelInfo.h"
#include "TalentManager.h"

JobLevelConverter* JobLevelConverter::instance = nullptr;

JobLevelConverter* JobLevelConverter::GetInstance()
{
	if (!instance) {
		instance = new JobLevelConverter();
	}
	return instance;
}

JobLevelConverter::JobLevelConverter() {
	gManager = GameManager::GetInstance();
	tManager = TalentManager::GetInstance();

	LoadCsv();
}

JobLevelConverter::~JobLevelConverter()
{
}

void JobLevelConverter::LoadCsv()
{
	auto loadCsv = tnl::LoadCsv("csv/JobLevelConverter.csv");

	for (int i = 1; i < loadCsv.size(); i++) {

		auto talentId = std::stoi(loadCsv[i][0]);				// �˔\��ID���擾
		auto jobId1 = std::stoi(loadCsv[i][1]);					// ��ڂ̐E��ID���擾
		auto jobName1 = gManager->UTF8toSjis(loadCsv[i][2]);	// ��ڂ̐E�̖��O���擾
		auto bonusValue1 = std::stoi(loadCsv[i][3]);			// ��ڂ̐E�̃{�[�i�X�o���l���擾
		auto jobId2 = std::stoi(loadCsv[i][4]);					// ��ڂ̐E��ID���擾
		auto jobName2 = gManager->UTF8toSjis(loadCsv[i][5]);	// ��ڂ̐E�̖��O���擾
		auto bonusValue2 = std::stoi(loadCsv[i][6]);			// ��ڂ̐E�̃{�[�i�X�o���l���擾

		/*int TalentId, int JobId1, std::string JobName1, int BonusValue1, int JobId2, std::string JobName2, int BonusValue2*/

		auto jobLevelConverter = std::make_shared<JobLevelInfo>(talentId, jobId1, jobName1, bonusValue1, jobId2, jobName2, bonusValue2);
		jobLevelConverterMaster.emplace_back(jobLevelConverter);

	}
}
//�˔\ID����Ή�����E�ƃ{�[�i�X�l�����N���X��Ԃ��֐�
std::shared_ptr<JobLevelInfo>JobLevelConverter::GetJobLevelInfo(int talentId)
{
	if (talentId > jobLevelConverterMaster.size())return nullptr;

	//�}�X�^�[����˔\ID�ɑΉ�����JobLevelInfo���擾����
	const auto& infoObject = jobLevelConverterMaster[talentId];
	//Info�N���X�C���X�^���X����E�ƃ{�[�i�X�l��������Map�I�u�W�F�N�g���擾����
	const auto& infoMap = infoObject->GetInfoMap();

	//�ꎞ�I�u�W�F�N�g�ɕۑ�
	std::vector<int>jobIds;
	std::vector<int>bonuses;
	for (auto itr = infoMap.begin(); itr != infoMap.end(); ++itr) {
		jobIds.emplace_back(itr->first);
		bonuses.emplace_back(itr->second);
	}
	//���O�̎擾
	const auto& names = infoObject->GetJobNames();

	return std::make_shared<JobLevelInfo>(talentId, jobIds[0], names[0], bonuses[0],
		jobIds[1], names[1], bonuses[1]);
}



