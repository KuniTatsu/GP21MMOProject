#pragma once
#include<string>

class Talent
{
public:

	Talent(int talentId, std::string talentName, int talentRare, int lowestRank,
		int addSTR, int addVIT, int addINT, int addMIN, int addSPD, int addDEX, int thisRank = -1);
	~Talent();

	//タレントランクに沿った値のステータスを決定する関数
	void SetFixStatus();


	inline const int& GetId() {
		return id;
	}
	inline const int& GetRare() {
		return rare;
	}
	inline const int& GetLowestTalentRank() {
		return lowestTalentRank;
	}
	inline const int& GetRank() {
		return rank;
	}
	inline const int& GetStr() {
		return str;
	}
	inline const int& GetVit() {
		return vit;
	}
	inline const int& GetInt() {
		return intelligence;
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
	inline const int& GetThisRank() {
		return rank;
	}
private:

private:
	//id,名前	レア度	最低値	STR	VIT	INT	MIN	SPD	DEX

	int id = 0;

	std::string name = "";

	int rare = 1;//1~5

	int lowestTalentRank = 1;//1~8

	int rank = 1;//1~10


	//ランク10時のステータス系
	int str = 0;
	int vit = 0;
	int intelligence = 0;
	int min = 0;
	int spd = 0;
	int dex = 0;

	//このタレントのランクでの実質ステータス系
	int fixStr = 0;
	int fixVit = 0;
	int fixInt = 0;
	int fixMin = 0;
	int fixSpd = 0;
	int fixDex = 0;



};

