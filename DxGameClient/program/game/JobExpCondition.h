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

	//コンディションのId
	int condition = 0;
	//コンディション達成に必要な値:敵を倒した数,移動した距離など
	int requiredAmount = 0;
	//コンディション達成時に与えられる経験値
	int exp = 0;
	//コンディション達成時に経験値を与える職のId
	int jobId = 0;
	//コンディション達成に必要な武器
	int weaponId = -1;
};

