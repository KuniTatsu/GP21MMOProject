#include "Item.h"

Item::Item(int itemId, std::string itemName, int itemStr, int itemVit, int itemInt, int itemMin, int itemSpd, int itemDex)
{
	//‘ã“ü
	id = itemId;
	name = itemName;
	str = itemStr;
	vit = itemVit;
	inteli = itemInt;
	min = itemMin;
	spd = itemSpd;
	dex = itemDex;
}

Item::~Item()
{
}
