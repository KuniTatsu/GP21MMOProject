#pragma once
#include<memory>
#include<list>
#include<vector>

class GameManager;
class ItemManager;
class Item;
class MaterialItem;

class Inventory {
public:

	Inventory(int MyInventorynum);
	~Inventory();

	//インベントリ内のアイテム数を取得する関数
	inline int GetItemCount() {
		return inventoryItemList.size();
	}

	//インベントリにアイテムを追加する関数
	void AddInventory(std::shared_ptr<Item> item);
	//void AddSharedInventory(std::shared_ptr<Item>item);

	//インベントリの中の死骸アイテムのみを配列にして返す関数
	std::vector<std::shared_ptr<MaterialItem>>GetDeadBodies();

	//インベントリのUpdate
	void Update();

	//カーソルを上下に動かす関数
	void CursorMove();
	//カーソルを一番上に戻す関数
	void CursorReset();
	//インベントリ内のアイテム名を描画する関数
	void DrawInventory(int x, int y);
	//カーソルで選択中のアイテムの説明を描画する関数
	void DrawItemDesc(float x, float y);
	//カーソルで選択中の装備アイテムのステータスを描画する関数
	void DrawEquipItemStatus(const int x, const int y);
	//ショップインベントリ用 購入額の表示
	void DrawNeedCoin(int x, int y);

	//カーソル中のアイテムを使う関数
	bool UseCursorItem();

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

	inline std::list<std::shared_ptr<Item>>& GetItemList() {
		return inventoryItemList;
	}

public:

	//std::shared_ptr<Item>inventory[10] = { nullptr,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };

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


	//内部にItemを10個もつlist
	std::list<std::shared_ptr<Item>> inventoryItemList;
};