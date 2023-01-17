/*
#include "Inventory.h"
#include"DxLib.h"
#include"../../library/t2klib.h"
#include"../../support/Support.h"
#include"Item.h"
#include"equipItem.h"
#include"../GameManager.h"
#include"../Player.h"
#include"../SoundManager.h"

extern GameManager* gManager;
Inventory::Inventory(int MyInventoryNum)
{
	cursorGh = gManager->LoadGraphEx("graphics/menuCursor.png");
	selectItemBackGh = gManager->LoadGraphEx("graphics/selectItemBack.png");
	myInventoryNum = MyInventoryNum + 1;
}

Inventory::~Inventory()
{
}

void Inventory::AddInventory(Item* item)
{
	if (inventoryList.size() == 10)return;
	inventoryList.emplace_back(item);
	itemNum++;

}

void Inventory::CursorMove()
{
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP)) {
		itemNum = GetItemCount();
		gManager->sound->System_Play(gManager->sound->system_move);
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN)) {
		itemNum = GetItemCount();
		gManager->sound->System_Play(gManager->sound->system_move);
		selectCursor = (selectCursor + 1) % itemNum;
	}
}
//インベントリのカーソル位置を一番上にリセットする関数
void Inventory::CursorReset()
{
	selectCursor = 0;
}
//インベントリ内のアイテム名を描画する関数
void Inventory::DrawInventory(int x, int y)
{
	int i = 0;



for (auto item : inventoryList) {
	//装備アイテムなら
	if (item->getItemData(1) >= 2) {
		equipItem* eItem = static_cast<equipItem*>(item);
		//装備中のアイテムなら'E'を頭に描画する
		if (eItem->GetIsEquiped())DrawStringEx(x + 40, y + 10 + 30 * i, -1, "[E]");
		//アイテム名の描画
		DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->getItemName().c_str());
	}
	else {
		//アイテム名の描画
		DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->getItemName().c_str());
	}
	++i;
}
//選択中アイテムの横にカーソルを描画する
DrawRotaGraph(x + 30, y + 20 + selectCursor * 30, 0.7, 0, cursorGh, true);
SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
DrawRotaGraph(x + 220, y + 20 + selectCursor * 30, 1, 0, selectItemBackGh, true);
SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
//アイテムの説明を描画する関数
void Inventory::DrawItemDesc(int x, int y)
{
	if (inventoryList.empty())return;
	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	(*itr)->DrawItemStringData(x, y);
	//inventory[selectCursor]->DrawItemData(x, y);
}

void Inventory::DrawEquipItemStatus(const int x, const int y)
{
	if (inventoryList.empty())return;

	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	//装備アイテムならデータを取得して描画する
	if ((*itr)->getItemData(1) >= 2) {
		auto item = static_cast<equipItem*>((*itr));
		item->DrawEquipItemStatus(x, y, item->GetSubId());
	}

}

void Inventory::DrawNeedCoin(int x, int y)
{
	if (inventoryList.empty())return;
	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	int needCoin = 0;
	if ((*itr)->getItemData(1) >= 2) {
		auto item = static_cast<equipItem*>((*itr));
		needCoin = item->getItemData(10);
	}
	else {
		needCoin = (*itr)->getItemData(5);
	}
	//文字サイズ変更
	SetFontSize(25);
	DrawStringEx(x + 10, y + 10, -1, "購入必要コイン:%d", needCoin);
	DrawStringEx(x + 10, y + 60, -1, "所持コイン:%d", gManager->player->GetHaveCoin());
	//文字サイズ変更
	SetFontSize(16);
}

int Inventory::GetCursorNum()
{
	return selectCursor;
}

void Inventory::SetCursorNum(int MoveNum)
{
	if (selectCursor != inventoryList.size())return;
	selectCursor += MoveNum;
	if (selectCursor < 0)selectCursor = 0;

}


*/


/*

void GameManager::AddItemToInventory(const int ItemId, std::vector<Inventory*>& Inventories,
	int& InventoryNum)
{
	//今のinventoryの持つアイテム配列がいっぱいなら
	if (Inventories[InventoryNum]->inventoryList.size() >= 10) {
		//if (sharedInventories[inventoryNum]->inventoryList.size() >= 10) {

			//新しくinventoryのインスタンスを生成する
		Inventory* newInventory = new Inventory(InventoryNum + 1);
		//inventory配列に登録
		Inventories.emplace_back(newInventory);

		//登録するinventoryを更新する
		InventoryNum++;
	}
	Item* item = iManager->GetItemData(ItemId);
	//装備アイテムだったら
	if (item->getItemData(1) >= 2) {
		equipItem* eItem = (equipItem*)item;
		//整数データの取得
		std::vector<int> intData = eItem->GetAllIntData();
		//文字列データの取得
		std::vector<std::string> stringData = item->GetAllStringData();

		//装備アイテムを生成 生成時にステータスをランダムに変更
		equipItem* newItem = new equipItem(intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4],
			stringData[1], intData[5], intData[6], stringData[2], intData[7], intData[8], intData[9], intData[10], 0);
		//インベントリ追加
		Inventories[InventoryNum]->AddInventory(newItem);
	}
	else {
		std::vector<int> intData = item->GetAllIntData();
		std::vector<std::string> stringData = item->GetAllStringData();

		Item* newItem = new Item(intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4], intData[5], stringData[1], stringData[2]);

		Inventories[InventoryNum]->AddInventory(newItem);

	}

}

void GameManager::PopItemFromInventory(const int NowInventoryId)
{
	//今の位置の配列番号を取得
	int selectNum = inventories[NowInventoryId]->GetCursorNum();
	//表示中のインベントリを取得
	auto itr = inventories[NowInventoryId]->inventoryList.begin();

	//選択されたアイテムまでイテレータ移動
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}
	//アイテムを消去
	delete((*itr));
	itr = inventories[NowInventoryId]->inventoryList.erase(itr);
	//カーソルの位置をひとつ上に移動
	inventories[NowInventoryId]->SetCursorNum(-1);

	//popするアイテムがいる場所=今いるインベントリが最後のインベントリではない場合
	if (NowInventoryId != inventoryNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

		//次のページの最初のアイテムをコピーして消したアイテムのリストの末尾に加える
			auto item = inventories[checkInventoryNum + 1]->inventoryList.begin();

			//アイテム追加
			inventories[checkInventoryNum]->inventoryList.emplace_back((*item));

			//次のページの最初のアイテムをpopする
			inventories[checkInventoryNum + 1]->inventoryList.pop_front();

			//最後のインベントリページにたどり着いたらbreak
			if (checkInventoryNum + 1 == inventoryNum)break;
			checkInventoryNum++;
		}
	}
	//最初のインベントリ内なら
	else {
		//インベントリ内のアイテム数を1減らす
		inventories[NowInventoryId]->SetItemNum(-1);
	}
	//空のインベントリを消す処理
	if (inventories[inventoryNum]->inventoryList.empty()) {
		if (inventoryNum != 0) {
			delete inventories[inventoryNum];
			inventories[inventoryNum] = nullptr;
			inventories.pop_back();
			inventoryNum--;
			isDeleteInventory = true;
		}
	}
	if (isDeleteInventory)return;
	//カーソルの位置を一番上にリセット
	if (inventories[NowInventoryId]->inventoryList.empty())inventories[NowInventoryId]->CursorReset();
}


*/