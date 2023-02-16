#pragma once

class GameManager;
class JobLevelInfo;
class TalentManager;

class JobLevelConverter {
public:
	// �C���X�^���X�̎擾
	static JobLevelConverter* GetInstance();
	// �˔\�ɑ΂���E�̃{�[�i�X�l�̎擾
	std::shared_ptr<JobLevelInfo>GetJobLevelInfo(int talentId);


private:
	JobLevelConverter();
	~JobLevelConverter();
	// �˔\�ƐE�̑Ή��\ CSV �̃��[�h�֐�
	void LoadCsv();


private:
	static JobLevelConverter* instance;
	GameManager* gManager = nullptr;
	TalentManager* tManager = nullptr;
	std::vector<std::shared_ptr<JobLevelInfo>>jobLevelConverterMaster;

};