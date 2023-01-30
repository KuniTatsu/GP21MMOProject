#include "ItemManager.h"
#include"Item.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

ItemManager* ItemManager::GetInstance() {
	if (!instance) {
		instance = new ItemManager();
	}
	return instance;
}


void ItemManager::CreateItem(int itemId, std::string itemName, int itemStr, int itemVit, int itemInt, int itemMin, int itemSpd, int itemDex)
{

}
