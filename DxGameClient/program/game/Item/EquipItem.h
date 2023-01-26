/*
装備アイテムのクラス
	アイテムクラスを継承する
	装備アイテムでしか持たないデータはこちらで持つ
	各種ステータスなど
*/


#pragma once
#include"Item.h"

//intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4],
//stringData[1], intData[5], intData[6], stringData[2], intData[7], intData[8], intData[9], intData[10], 0

class EquipItem:public Item
{
public:
	EquipItem();
	~EquipItem();

private:

};

