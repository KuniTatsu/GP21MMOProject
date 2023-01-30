#pragma once
#include<string>
#include<memory>
#include<list>
#include<vector>

class Item;

class ItemManager
{
private:
	ItemManager();
	~ItemManager();

	static ItemManager* instance;

public:

	static ItemManager* GetInstance();
	void Destory();

private:

	std::vector<std::shared_ptr<Item>>itemMaster;

public:
	/*アイテムリスト*/
	std::list<std::shared_ptr<Item>> itemList;
	
	void CreateItem(int itemId, std::string itemName, int itemStr, int itemVit, int itemInt, int itemMin, int itemSpd, int itemDex);
	//void DrawItemStringData(int x, int y);
	
	std::vector<std::string>GetAllStringData();
	std::vector<int>GetAllIntData();
	int GetItemData(int id);
	
	
};

