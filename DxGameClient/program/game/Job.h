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


public:
	Job(int id, std::string name,int str, int vit,
		int inteli, int min, int spd, int dex);
	~Job();

private:

};

