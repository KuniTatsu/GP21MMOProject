#pragma once
#include"Item.h"
//#include<string>

class ConsumeItem :public Item
{
public:

	ConsumeItem(int ID, std::string Name, int STR, int VIT, int INT, int MID, int SPD, int DEX, float moveHP = 0.0f);
	~ConsumeItem();

private:

};
