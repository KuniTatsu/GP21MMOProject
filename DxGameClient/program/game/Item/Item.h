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
	inline void SetItemType(int type) {
		itemType = type;
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

	inline int GetRare() {
		return rare;
	}

	inline int GetMaxStack() {
		return stockMax;
	}
	//スタック数を変動させる関数
	inline void MoveStackNum(int num) {
		nowStackNum += num;
	}
	//スタック数を取得する関数
	inline int GetNowStackNum() {
		return nowStackNum;
	}

	//Maxスタックかどうか返す関数
	inline bool IsMaxStack() {
		if (nowStackNum >= stockMax)return true;
		return false;
	}

protected:

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

	//現在のスタック数
	int nowStackNum = 1;
	//attribute以外のintData
	std::vector<int> intData;

	//attribute
	std::vector<int> attribute;

private:

	void SetIntData();



};
