#include "Item.h"

Item::Item()
{
	//���
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
	intData.emplace_back(id);
	intData.emplace_back(rare);
	//intData.emplace_back(str);
	//intData.emplace_back(vit);
	//intData.emplace_back(inteli);
	//intData.emplace_back(mid);
	//intData.emplace_back(spd);
	//intData.emplace_back(dex);
	intData.emplace_back(stockMax);

	attribute.emplace_back(str);
	attribute.emplace_back(vit);
	attribute.emplace_back(inteli);
	attribute.emplace_back(mid);
	attribute.emplace_back(spd);
	attribute.emplace_back(dex);
}
