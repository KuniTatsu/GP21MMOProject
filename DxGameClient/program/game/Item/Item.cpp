#include "Item.h"

Item::Item()
{
	//‘ã“ü
	/*id = itemId;
	name = itemName;
	str = itemStr;
	vit = itemVit;
	inteli = itemInt;
	min = itemMin;
	spd = itemSpd;
	dex = itemDex;*/

	intData.clear();
}

std::vector<int>& Item::GetAllIntData()
{
	return intData;
}

void Item::SetIntData()
{
	intData.emplace_back(str);
	intData.emplace_back(vit);
	intData.emplace_back(inteli);
	intData.emplace_back(mid);
	intData.emplace_back(spd);
	intData.emplace_back(dex);
}
