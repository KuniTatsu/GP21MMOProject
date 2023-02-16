#pragma once
#include"Item.h"
//#include<memory>
//#include<string>

/*
装備アイテムのクラス
	アイテムクラスを継承する
	装備アイテムでしか持たないデータはこちらで持つ
	各種ステータスなど
*/

//intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4],
//stringData[1], intData[5], intData[6], stringData[2], intData[7], intData[8], intData[9], intData[10], 0

class EquipItem : public Item
{
public:

	EquipItem(int ID, std::string Name, float HP, int STR, int VIT, int INT, int MID, int SPD, int DEX, int EquipId = -1);
	~EquipItem();

	inline bool GetIsEquiped() {
		return isEquiped;
	}
	void DrawEquipItemStatus(int x, int y, int GetSubId);

	int GetSubId();

	inline int GetEquipId() {
		return equipId;
	}

public:


private:

	bool isEquiped = false;

	int equipId = -1;




};

