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

	//�V�����E���擾����֐�
	std::shared_ptr<Job>CreateNewJob(int jobId);
private:
	JobManager();
	~JobManager();

	//�����Job�Ɍo���l�𑫂��֐�
	void AddExpToJob(std::shared_ptr<Job> job,int jobId, int addExp);

	// ����ɂ��o���l���グ�邱�Ƃ̂ł���E���擾����֐�
	void GetJobToWeapon(std::shared_ptr<Job> job, int WeaponId);

	//  �E�ɂ�肻��ɑ΂���o���l���擾����֐�
	// void GetExpToJob(std::vector<int> jobId);

	

private:

	// Csv����E�����擾����֐�
	void LoadCsv();

	// Csv����E�̌o���l�����擾����֐�
	void LoadCsvJobLevelExp();

	// Csv����o���l���擾���邽�߂̓���̏������擾����֐�
	void LoadCsvJobLevelCondition();

private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	// �E�̃X�e�[�^�X�i�[
	std::vector<std::shared_ptr<Job>>jobMaster;
	// �E�̕K�v�o���l�i�[
	std::vector < std::shared_ptr<JobNeedExpData>> needExpMaster;
	// ����̍s���ŐE�̃��x�����擾�f�[�^���i�[
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
