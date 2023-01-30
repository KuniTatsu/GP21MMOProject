/*
�S�ẴA�C�e���N���X�̊��N���X
	�A�C�e���Ɋւ����{��������

*/

#pragma once
#include<string>
#include<vector>
#include<memory>

class Item
{
public:

	Item();

	virtual ~Item() {}

	inline int GetItemId() {
		return id;
	}

	inline int GetItemType() {
		return itemType;
	}
	std::vector<int>& GetAllIntData();

	inline std::string GetItemName() {
		return name;
	}

private:

	//id,���O, STR,	VIT, INT, MIN, SPD,	DEX
	int id = 0;
	std::string name = "";
	int str = 0;
	int vit = 0;
	int inteli = 0;
	int mid = 0;
	int spd = 0;
	int dex = 0;

	int itemType = 0;

	std::vector<int> intData;

private:

	void SetIntData();



};
