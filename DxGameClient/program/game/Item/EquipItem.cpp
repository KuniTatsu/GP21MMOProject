#include "EquipItem.h"


//EquipItem::EquipItem() {
//
//}

EquipItem::EquipItem(int ID, std::string Name, float HP, int STR, int VIT, int INT, int MID, int SPD, int DEX, int EquipId )
{
	id = ID;
	name = Name;
	hp = HP;
	str = STR;
	vit = VIT;
	inteli = INT;
	mid = MID;
	spd = SPD;
	dex = DEX;
	equipId = EquipId;

}

EquipItem::~EquipItem()
{
}


//bool EquipItem::GetIsEquiped()
//{
//	return false;
//}

void EquipItem::DrawEquipItemStatus(int x, int y, int GetSubId)
{
}

int EquipItem::GetSubId()
{
	return 0;
}
