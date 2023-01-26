#pragma once
#include<vector>
#include<memory>
#include<list>

class Inventory;

class InventoryManager {
private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* instance;

public:
	static InventoryManager* GetInstance();
	void Destory();

private:
	
	std::vector<std::shared_ptr<Inventory>>inventories;
	bool isDeleteInventory = false;
	const int inventoryLastNum = 30;

public:

	void AddItemToInventory(const int ItemId, std::vector<std::shared_ptr<Inventory>>& Inventories, int& InventoryNum);
	void PopItemFromInventory(const int NowInventoryId);

};