#pragma once
#include<vector>
#include<memory>
//#include<list>

class Inventory;
class ItemManager;

class InventoryManager {
private:
	InventoryManager();
	~InventoryManager();

	//インベントリ切り替え
	void MoveSelectInventory();

private:
	static InventoryManager* instance;
	ItemManager* iManager = nullptr;

	std::vector<std::shared_ptr<Inventory>>inventories;

	//今の一番新しいインベントリ番号
	int latestIntentoryNum = 0;

	//選択中のインベントリNum
	int nowSelectInventoryNum = 0;

public:
	static InventoryManager* GetInstance();
	void Destory();

	void Init();

	//インベントリ更新
	void UpdateInventory();

	void AddItemToInventory(const int ItemId);

	//アイテムを特定のインベントリから削除する関数 args:消すアイテムがあるインベントリの番号
	void PopItemFromInventory(const int NowInventoryId);


	//インベントリの描画
	void DrawInventory(float x,float y);
};