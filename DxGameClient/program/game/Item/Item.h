/*
�S�ẴA�C�e���N���X�̊��N���X
	�A�C�e���Ɋւ����{��������

*/

#pragma once
#include<string>

class Item
{
public:
	Item(int itemId, std::string itemName, int itemStr, int itemVit, int itemInt, int itemMin, int itemSpd, int itemDex);
	~Item();

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

public:

	inline int getItemData(int type) {

	}
	inline std::string getItemName() {

	}
	inline std::string DrawItemStringData(int x, int y) {

	}
	void DrawItemData(int x, int y);
	
};

