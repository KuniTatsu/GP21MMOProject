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
	void PopItemFromInventory();

	//選択中のアイテムを使用する関数
	void UseCursorItem();

	//インベントリの描画
	void DrawInventory(float x,float y);

	//カーソル中のアイテムの説明文を表示する関数
	void DrawCursorItemDesc(float x, float y);

	//すべてのインベントリが空か返す関数
	bool isEmptyAllInventory();
};