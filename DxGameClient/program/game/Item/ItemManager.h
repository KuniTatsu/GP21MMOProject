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
	/*
	0	なし
1	剣
2	斧
3	槍
4	楯
5	弓
6	黒魔法
7	白魔法
8	青魔法
9	緑魔法
10	赤魔法
11	全魔法
12	全武器
	*/
	enum class WEAPONTYPE :uint32_t {
		NONE,
		SWORD,
		AXE,
		SPEAR,
		SHIELD,
		BOW,
		BLACKMAGIC,
		WHITEMAGIC,
		BLUEMAGIC,
		GREENMAGIC,
		REDMAGIC,
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

