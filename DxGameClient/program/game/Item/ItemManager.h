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

	/*�A�C�e��[����or����][�X�e�[�^�X]*/
	std::vector<std::vector<std::shared_ptr<Item>>>itemMaster;

public:
	/*�A�C�e�����X�g*/
	std::list<std::shared_ptr<Item>> itemList;

	enum class ITEMTYPE :uint32_t {
		CONSUME,
		EQUIP,
		MATERIAL,
		MAX
	};
	/*
	0	�Ȃ�
1	��
2	��
3	��
4	�|
5	�|
6	�����@
7	�����@
8	���@
9	�Ζ��@
10	�Ԗ��@
11	�S���@
12	�S����
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

