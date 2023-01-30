#pragma once
#include<memory>
#include<list>

class GameManager;
class ItemManager;
class Item;

class Inventory {
public:

	Inventory(int MyInventorynum);
	~Inventory();

	//インベントリ内のアイテム数を取得する関数
	inline int GetItemCount() {
		return static_cast<int>(inventoryItemList.size());
	}

	//インベントリにアイテムを追加する関数
	void AddInventory(std::shared_ptr<Item> item);
	//void AddSharedInventory(std::shared_ptr<Item>item);
	
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

	//カーソルの位置を取得する関数
	int GetCursorNum();
	//カーソルの位置を変更する関数 type:0->加算移動,1->指定位置移動
	void SetCursorNum(const int MoveNum);
	//インベントリ番号を取得する関数
	inline int GetInventoryNum() {
		return myInventoryNum;
	}
	inline void SetItemNum(const int num) {
		itemNum += num;
	}

public:

	std::shared_ptr<Item>inventory[10] = { nullptr,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };

	////内部にItemを10個もつlist
	std::list<std::shared_ptr<Item>> inventoryItemList;

private:

	GameManager* gManager = nullptr;
	ItemManager* iManager = nullptr;

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