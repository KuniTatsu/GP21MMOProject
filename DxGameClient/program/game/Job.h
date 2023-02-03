#pragma once
#include<string>

class Job
{
private:
	//id,–¼‘O, STR,	VIT, INT, MIN, SPD,	DEX
	int id = 0;
	std::string name = "";
	int str = 0;
	int vit = 0;
	int inteli = 0;
	int min = 0;
	int spd = 0;
	int dex = 0;

	// EƒŒƒxƒ‹‚ÌğŒ‚ğŒˆ‚ß‚é•Ï”
	int conditions = 0;



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
};

