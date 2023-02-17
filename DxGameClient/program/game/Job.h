#pragma once
#include<string>

class Job
{
public:
	Job(int jobId, std::string jobName, int jobStr, int jobVit, int jobInt, int jobMin, int jobSpd, int jobDex);
	//debug�p
	Job(int jobId, std::string jobName, int jobStr, int jobVit, int jobInt, int jobMin, int jobSpd, int jobDex, int startLevel);
	~Job();

	inline const int& GetId() {
		return id;
	}
	inline const int& GetStr() {
		return str;
	}
	inline const int& GetVit() {
		return vit;
	}
	inline const int& GetInt() {
		return inteli;
	}
	inline const int& GetMin() {
		return min;
	}
	inline const int& GetSpd() {
		return spd;
	}
	inline const int& GetDex() {
		return dex;
	}

	inline const std::string& GetName() {
		return name;
	}

	//���݂̌o���l�擾�֐�
	inline int GetNowExp() {
		return exp;
	}
	//���݂̌o���l�Z�b�g�֐�
	inline void SetNowExp(int nowExp) {
		exp = nowExp;
	}

	//���݂̃��x���擾�֐�
	inline int GetNowLevel() {
		return level;
	}

	//���x���A�b�v
	inline void LevelUp() {
		if (level >= 10)return;
		level++;
	}

	inline int GetJobLevel() {
		return level;
	}
	inline std::string GetJobName() {
		return name;
	}

	// ���݂̃����X�^�[�������擾�֐�
	inline int GetMonsterKills() {
		return killCount;
	}

	inline void AddKillCount(int num) {
		killCount += num;
	}

	//�����X�^�[���������Z�b�g
	inline void ResetKillCount() {
		killCount = 0;
	}

	// ���݂̈ړ��������擾����֐�
	inline int GetMovingDistance() {
		return MovingDistance;
	}
	// ���݂̃A�C�e���̎g�p��
	inline int GetUseItem() {
		return useItem;
	}
private:
	//id,���O, STR,	VIT, INT, MIN, SPD,	DEX
	int id = 0;
	std::string name = "";
	int str = 0;
	int vit = 0;
	int inteli = 0;
	int min = 0;
	int spd = 0;
	int dex = 0;


	int exp = 0;

	int level = 0;

	//�����X�^�[�̃L����(�R���f�B�V�����`�F�b�N�p�@���܂ŒB�����烊�Z�b�g�����)
	int killCount = 0;
	// ���݂̈ړ�����
	int MovingDistance = 0;
	// �g�p�����A�C�e����
	int useItem = 0;
private:


};

