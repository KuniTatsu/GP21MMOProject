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

	//debug�p
	std::shared_ptr<Job>CreateDebugJob(int jobId, int startJobLevel = 10);

	//���炩�̍s���ŐE�̌o���l�����������Ƃ��ɌĂԊ֐�
	bool UpdateJobInfo(int condition = 0);

	//�W���u�Ɍo���l��^����ۂ̃R���f�B�V����
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


	//�����Job�Ɍo���l�𑫂��֐�
	void AddExpToJob(int jobId, int addExp);

	// ����ɂ��o���l���グ�邱�Ƃ̂ł���E���擾����֐�
	std::vector<std::shared_ptr<Job>> GetJobFromWeapon(int WeaponId);

	//  �E�ɂ�肻��ɑ΂���o���l���擾����֐�
	// void GetExpToJob(std::vector<int> jobId);


private:

	// Csv����E�����擾����֐�
	void LoadCsv();

	// Csv����E�̌o���l�����擾����֐�
	void LoadCsvJobLevelExp();

	// Csv����o���l���擾���邽�߂̓���̏������擾����֐�
	void LoadCsvJobLevelCondition();


	//�R���f�B�V����:kill�̃`�F�b�N�֐�
	bool CheckConditionKill(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs);

	//�R���f�B�V����:killWeapon�̃`�F�b�N�֐�
	bool CheckConditionKillWeapon(const std::vector<std::shared_ptr<JobExpCondition>>& conditions, std::vector<std::shared_ptr<Job>>& playerJobs);

	//�R���f�B�V����:useItem�̃`�F�b�N�֐�
	bool CheckConditionUseItem();

	//�R���f�B�V����:getItem�̃`�F�b�N�֐�
	bool CheckConditionGetItem();

	//�R���f�B�V����:move�̃`�F�b�N�֐�
	bool CheckConditionMove();
private:
	static JobManager* instance;
	GameManager* gManager = nullptr;
	// �E�̃X�e�[�^�X�i�[
	std::vector<std::shared_ptr<Job>>jobMaster;
	// �E�̕K�v�o���l�i�[
	std::vector < std::shared_ptr<JobNeedExpData>> needExpMaster;
	// ����̏����Ōo���l��^������̃N���X�z��
	std::vector < std::shared_ptr<JobExpCondition> > JobExpConditionMaster;

	//�R���f�B�V�����𖞂������E�Ƃ̃W���uId������ꎞ�ۑ��p�z��
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
