#pragma once
#include<string>

class Job
{
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

	//�����X�^�[�̃L����
	int monsterKills = 0;
	// ���݂̈ړ�����
	int MovingDistance = 0;
	// �g�p�����A�C�e����
	int useItem = 0;

public:
	Job(int id, std::string name,int str, int vit,
		int inteli, int min, int spd, int dex);
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
		level++;
	}

	// ���݂̃����X�^�[�������擾�֐�
	inline int GetMonsterKills() {
		return monsterKills;
	}
	// ���݂̈ړ��������擾����֐�
	inline int GetMovingDistance() {
		return MovingDistance;
	}
	// ���݂̃A�C�e���̎g�p��
	inline int GetUseItem() {
		return useItem;
	}
};

