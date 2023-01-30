#pragma once
#include<vector>
#include<memory>
#include<list>

class Inventory;
class ItemManager;

class InventoryManager {
private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* instance;
	ItemManager* iManager = nullptr;

public:
	static InventoryManager* GetInstance();
	void Destory();

private:
	
	std::vector<std::shared_ptr<Inventory>>inventories;
	bool isDeleteInventory = false;
	int inventoryLastNum = 30;

public:

	void AddItemToInventory(const int ItemId, std::vector<std::shared_ptr<Inventory>>& Inventories, int& InventoryNum);
	void PopItemFromInventory(const int NowInventoryId);

};