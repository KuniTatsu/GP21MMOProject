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

std::vector<std::string> ItemManager::GetAllStringData()
{
	return std::vector<std::string>();
}

std::vector<int> ItemManager::GetAllIntData()
{
	return std::vector<int>();
}

int ItemManager::GetItemData(int id) {
	return 0;
}