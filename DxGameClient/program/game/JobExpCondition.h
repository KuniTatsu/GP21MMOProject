#pragma once
#include <string>



class JobExpCondition
{
public:
	JobExpCondition(int JobId, std::string Name, int Condition, int RequiredAmount, int Exp);
	~JobExpCondition();

	inline std::string GetJobName() {
		return name;
	}
	inline int GetCondition() {
		return condition;
	}
	inline int GetRequiredAmount() {
		return requiredAmount;
	}
	inline int GetExp() {
		return exp;
	}

	inline int GetJobId() {
		return jobId;
	}
	inline int GetWeaponId() {
		return weaponId;
	}

	inline void SetWeaponId(int WeaponId) {
		weaponId = WeaponId;
	}

private:
	std::string name = "";

	//�R���f�B�V������Id
	int condition = 0;
	//�R���f�B�V�����B���ɕK�v�Ȓl:�G��|������,�ړ����������Ȃ�
	int requiredAmount = 0;
	//�R���f�B�V�����B�����ɗ^������o���l
	int exp = 0;
	//�R���f�B�V�����B�����Ɍo���l��^����E��Id
	int jobId = 0;
	//�R���f�B�V�����B���ɕK�v�ȕ���
	int weaponId = -1;
};

