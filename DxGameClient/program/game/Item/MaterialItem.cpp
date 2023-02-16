#include "MaterialItem.h"

MaterialItem::MaterialItem(int ID, std::string Name, int MaterialType, int Rare, int MaxStack)
{
	id = ID;
	name = Name;
	materialType = MaterialType;
	rare = Rare;
	stockMax = MaxStack;
}

MaterialItem::~MaterialItem()
{
}
