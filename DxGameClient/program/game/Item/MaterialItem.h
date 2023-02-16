#pragma once
#include"Item.h"
#include<vector>
#include<string>

class MaterialItem:public Item
{
public:
	MaterialItem(int ID, std::string Name,int MaterialType,int Rare,int MaxStack);
	~MaterialItem();

	inline int GetMaterialType() {
		return materialType;
	}

private:

	//素材アイテムのタイプ
	int materialType = 0;

};

