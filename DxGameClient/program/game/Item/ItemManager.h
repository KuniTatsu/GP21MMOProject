#pragma once
#include<string>
#include<memory>
#include<list>
#include<vector>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;
class MaterialConverter;

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

	//materialCOnverterMasterの取得
	inline const std::vector<std::shared_ptr<MaterialConverter>>& GetConvertMaster() {
		return convertMaster;
	}

	//エネミーIdから死骸のIdを返す関数
	int GetBaseBodyId(int enemyId);

private:

	/*アイテム[装備or消費][ステータス]*/
	std::vector<std::vector<std::shared_ptr<Item>>>itemMaster;

	//解体のための死骸と素材アイテムリスト
	std::vector<std::shared_ptr<MaterialConverter>> convertMaster;

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


class MaterialConverter
{
public:
	MaterialConverter(int baseId, std::string baseName, int destId1, int weight1, int destId2, int weight2, int destId3, int weight3, int destId4, int weight4);
	~MaterialConverter();

	//死骸Idとマッチする行を返す関数
	const std::pair<int, int>& GetMatchPair(int baseId);

	//抽選ウェイトだけ取得する関数
	inline const std::vector<int>& GetWeight() {
		return weights;
	}

	//抽選番号から解体後アイテムIdを取得する関数
	int GetMatchAfterItemNum(int index);

	inline int GetBaseId() {
		return bodyId;
	}

	inline const std::unordered_map<int, int>& GetMap() {
		return disassemblyWeight;
	}

private:

	std::unordered_map<int, int> disassemblyWeight;

	//死骸Id	名前	解体後アイテムId1	ウェイト1	解体後アイテムId2	ウェイト2	解体後アイテムId3	ウェイト3	解体後アイテムId4	ウェイト4

	int bodyId = -1;
	std::string bodyName = "";

	//抽選ウェイトのみの配列
	std::vector<int>weights = {};
};

