#include "ConsumeItem.h"
#include"../GameManager.h"

ConsumeItem::ConsumeItem(int ID, std::string Name, int STR, int VIT, int INT, int MID, int SPD, int DEX, int Rare, double Recover, int MaxStack)
{
	id = ID;
	name = Name;
	str = STR;
	vit = VIT;
	inteli = INT;
	mid = MID;
	spd = SPD;
	dex = DEX;

	attribute.emplace_back(STR);
	attribute.emplace_back(VIT);
	attribute.emplace_back(INT);
	attribute.emplace_back(MID);
	attribute.emplace_back(SPD);
	attribute.emplace_back(DEX);

	rare = Rare;
	recover = Recover;
	stockMax = MaxStack;
}

ConsumeItem::~ConsumeItem()
{
}

void ConsumeItem::UseItem()
{
	//今は回復アイテムのみ実装する 今後時限制のバフアイテムなどを実装する際はActorDataの作りを変えること
	GameManager::GetInstance()->UpdatePlayerHP(recover);

}
