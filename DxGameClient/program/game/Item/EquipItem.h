/*
装備アイテムのクラス
	アイテムクラスを継承する
	装備アイテムでしか持たないデータはこちらで持つ
	各種ステータスなど
*/


#pragma once
#include"Item.h"

class EquipItem:public Item
{
public:
	EquipItem();
	~EquipItem();

private:

};

