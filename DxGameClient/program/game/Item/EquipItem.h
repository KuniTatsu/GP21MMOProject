#pragma once
#include"Item.h"
#include<memory>

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
	/*id = itemId;
	name = itemName;
	HP
	str = itemStr;
	vit = itemVit;
	inteli = itemInt;
	min = itemMin;
	spd = itemSpd;
	dex = itemDex;*/
	EquipItem(int ID,std::string Name,float HP,int STR,int VIT,int INT,int MID,int SPD,int DEX);
	~EquipItem();

private:
	int hp = 0;
	bool isEquiped = false;

public:
	
	inline bool GetIsEquiped() {
		return isEquiped;
	}
	void DrawEquipItemStatus(int x, int y, int GetSubId);
	int GetSubId();
};

