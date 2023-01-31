#pragma once
#include<string>
#include<vector>
#include<memory>
#include<string>

/*
全てのアイテムクラスの基底クラス
	アイテムに関する基本情報を持つ

*/

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

	inline std::vector<int>& GetAttributeData() {
		return attribute;
	}
	inline std::string GetItemName() {
		return name;
	}
	inline double GetItemRecover() {
		return recover;
	}
	inline float GetHPFromEquipItem() {
		return hp;
	}


private:

	int id = 0;
	std::string name = "";
	double recover = 0;
	int rare = 0;
	int str = 0;
	int vit = 0;
	int inteli = 0;
	int mid = 0;
	int spd = 0;
	int dex = 0;
	int stockMax = 0;

	int itemType = 0;

	float hp = 0;

	//attribute以外のintData
	std::vector<int> intData;

	//attribute
	std::vector<int> attribute;

private:

	void SetIntData();



};
