#pragma once
#include <string>



class JobExpCondition
{
public:
	JobExpCondition(int JobId, std::string Name, int Condition, int RequiredAmount, int Weapon, int Exp);
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

private:
	std::string name = "";
	int condition = 0;
	int requiredAmount = 0;
	int exp;

	int jobId = 0;
	int weaponId = 0;
};

