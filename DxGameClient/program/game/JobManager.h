#pragma once
#include<vector>
#include<memory>

#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>
#include<memory>

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

	// Csv����E�ƍ˔\�̑��ݐ�������֐�
	void  JobTargetTable();

	// Csv����E�̃��x���ʂ̃X�e�[�^�X���擾����֐�
	void JobLevelStatus();

	//�V�����E���擾����֐�
	std::shared_ptr<Job>CreateNewJob(int id);

	// �E�̃��x���������������̏����擾����֐�
	std::shared_ptr<Job>LevelUpJob(int id);


private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	std::vector<std::shared_ptr<Job>>jobMaster;
	//std::vector<std::shared_ptr<>
};

