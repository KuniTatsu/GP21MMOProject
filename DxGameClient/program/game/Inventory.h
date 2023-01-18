#pragma once
#include<memory>
#include<list>

class Item;

class Inventory {
public:
	Inventory(int MyInventorynum);
	~Inventory();

	//std::shared_ptr<Item>inventory[10] = { nullptr,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };

	////内部にItemを10個もつlist
	//std::list<std::shared_ptr<Item>> inventoryItemList;

	//インベントリ内のアイテム数を取得する関数
	inline int GetItemCount() {
		//return inventoryItemList.size();
	}

	//インベントリにアイテムを追加する関数
	//void AddInventory(Item* item);
	//void AddSharedInventory(std::shared_ptr<Item>item);
	//
	//カーソルを上下に動かす関数
	void CursorMove();
	//カーソルを一番上に戻す関数
	void CursorReset();
	//インベントリ内のアイテム名を描画する関数
	void DrawInventory(const int x, const int y);
	//カーソルで選択中のアイテムの説明を描画する関数
	void DrawItemDesc(const int x, const int y);
	//カーソルで選択中の装備アイテムのステータスを描画する関数
	void DrawEquipItemStatus(const int x, const int y);
	//ショップインベントリ用 購入額の表示
	void DrawNeedCoin(int x, int y);

private:
	//選択中のアイテムを指すカーソルの位置
	int selectCursor = 0;
	//カーソルgh
	int cursorGh = 0;
	//選択中アイテムの背景
	int selectItemBackGh = 0;
	//インベントリ内のアイテム数
	int itemNum = 0;
	//インベントリ番号
	int myInventoryNum = 0;
};