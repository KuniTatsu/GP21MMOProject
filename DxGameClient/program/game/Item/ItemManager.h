#pragma once
#include<string>
#include<memory>
#include<list>
#include<vector>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;

class ItemManager
{
private:
	ItemManager();
	~ItemManager();


	void LoadCsv();
	static ItemManager* instance;


public:

	static ItemManager* GetInstance();
	void Destory();

	void Init();

private:

	/*アイテム[装備or消費][ステータス]*/
	std::vector<std::vector<std::shared_ptr<Item>>>itemMaster;

public:
	/*アイテムリスト*/
	std::list<std::shared_ptr<Item>> itemList;

	enum class ITEMTYPE :uint32_t {
		CONSUME,
		EQUIP,
		MATERIAL,
		MAX
	};

	std::shared_ptr<Item> CreateItem(int itemId, int itemType);
	//void DrawItemStringData(int x, int y);
	//void LoadItemMaster();

	std::vector<std::string>GetAllStringData();
	std::vector<int>GetAllIntData();
	int GetItemData(int id);
	std::shared_ptr<Item>GetItemFromId(int id);
	std::shared_ptr<Item>GetItemFromId(int id, int itemType);

};

