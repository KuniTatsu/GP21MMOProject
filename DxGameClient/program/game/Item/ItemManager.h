#pragma once
#include<vector>
#include<list>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"
/*
アイテムのマスター情報を持つ　マスターはcsvから読み込み
外部からアイテムを生成する為に呼ばれる関数をもつが、どのアイテムが選ばれるかはSpawnManagerにやってもらう
選ばれたアイテムを生成し、返り値で返す関数を作り、外部に作られたアイテムを返す
敵からのドロップだった場合は、ItemManagerが持つフィールドドロップリストに入れる

*/
class Item;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();
	//外部からアイテムを作りたいときに呼ぶ関数
	void SpawnItem();

	void update(float deltatime);

	enum class ITEMTYPE {
		CONSUME,
		EQUIP_WEAPON,
		EQUIP_ARMOR,
		MATERIAL,
		MAX
	};

private:
	std::shared_ptr<Item> CreateItem(int type, tnl::Vector3& spawnPos);

	void LoadItemCsv(std::string pass, std::vector< std::vector<int>>& putInVector, int type);

private:
	std::list <std::shared_ptr<Item>>fieldDropItems;

	//アイテムマスター
	std::vector < std::vector<std::shared_ptr<Item>>>itemMaster;
};

