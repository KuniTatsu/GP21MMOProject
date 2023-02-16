#pragma once
#include<unordered_map>
#include<string>


class GameManager;


class JobLevelInfo {
public:

public:

	JobLevelInfo(int TalentId, int JobId1, std::string JobName1, int BonusValue1, int JobId2, std::string JobName2, int BonusValue2);
	~JobLevelInfo();

	// --------------------------------------------------------------------------------


	// ----------------------------------------------------------------------
	inline const std::vector<std::string>& GetJobNames() {
		return names;
	}

	// --------------------------------------------------------------------------------

	//タレントID取得
	inline const int GetTalentId() {
		return talentId;
	}
	//職とボーナス値の組み合わせのMapを返す関数
	inline const std::unordered_map<int, int>& GetInfoMap() {
		return info;
	}

	// ------二つ目の職のボーナス経験値が一つ目の職と違う場合のみコメントアウト---------

	/*inline const int& GetBonusValue() {
		return info.at(jobId2);
	}*/

	// --------------------------------------------------------------------------------

private:
	std::unordered_map<int, int> info;	// 職に対するボーナス値の格納
	int talentId = 0;					// タレントID
	std::vector<std::string> names;


private:
};