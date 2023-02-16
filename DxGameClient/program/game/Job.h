#pragma once
#include<string>

class Job
{
private:
	//id,名前, STR,	VIT, INT, MIN, SPD,	DEX
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

	//モンスターのキル数
	int monsterKills = 0;
	// 現在の移動距離
	int MovingDistance = 0;
	// 使用したアイテム数
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

	//現在の経験値取得関数
	inline int GetNowExp() {
		return exp;
	}
	//現在の経験値セット関数
	inline void SetNowExp(int nowExp) {
		exp = nowExp;
	}

	//現在のレベル取得関数
	inline int GetNowLevel() {
		return level;
	}

	//レベルアップ
	inline void LevelUp() {
		level++;
	}

	// 現在のモンスター討伐数取得関数
	inline int GetMonsterKills() {
		return monsterKills;
	}
	// 現在の移動距離を取得する関数
	inline int GetMovingDistance() {
		return MovingDistance;
	}
	// 現在のアイテムの使用数
	inline int GetUseItem() {
		return useItem;
	}
};

