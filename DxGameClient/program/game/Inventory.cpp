#include "Inventory.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"Item/Item.h"
#include"Item/EquipItem.h"
#include"../library/tnl_input.h"

Inventory::Inventory(int MyInventorynum)
{
	gManager = GameManager::GetInstance();
	iManager = ItemManager::GetInstance();
	
	selectItemBackGh = gManager->LoadGraphEx("graphics/FrameWhite.png");
	myInventoryNum = myInventoryNum + 1;
}

Inventory::~Inventory()
{
}

void Inventory::AddInventory(std::shared_ptr<Item> item)
{
	if (inventoryItemList.size() == 10)return;
	inventoryItemList.emplace_back(item);
	itemNum++;
}

void Inventory::CursorMove()
{
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_UP)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_DOWN)) {

	}
}

void Inventory::CursorReset()
{
	selectCursor = 0;
}

//インベントリ内のアイテム名を描画する関数
void Inventory::DrawInventory(const int x, const int y)
{
	int i = 0;

	for (auto item : inventoryItemList) {
		//装備アイテムなら
		if (item->getItemData(1) >= 2) {
			//auto eItem = static_cast<std::shared_ptr<EquipItem>>(item);
			auto eItem = std::shared_ptr<EquipItem>();
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
	if (inventoryItemList.empty())return;
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	(*itr)->DrawItemStringData(x, y);
	inventory[selectCursor]->DrawItemData(x, y);
}

void Inventory::DrawEquipItemStatus(const int x, const int y)
{
	if (inventoryItemList.empty())return;
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	//装備アイテムならデータを取得して描画する
	if ((*itr)->getItemData(1) >= 2) {
		//auto item = static_cast<std::shared_ptr<EquipItem>>((*itr));
		auto eItem = std::shared_ptr<EquipItem>();
		eItem->DrawEquipItemStatus(x, y, eItem->GetSubId());
	}
}

void Inventory::DrawNeedCoin(int x, int y)
{
	if (inventoryItemList.empty())return;
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	int needCoin = 0;
	if ((*itr)->getItemData(1) >= 2) {
		//auto item = static_cast<EquipItem*>((*itr));
		//needCoin = item->getItemData(10);
		needCoin = (*itr)->getItemData(10);
	}
	else {
		needCoin = (*itr)->getItemData(5);
	}
	//文字サイズ変更
	SetFontSize(25);
	DrawStringEx(x + 10, y + 10, -1, "購入必要コイン:%d", needCoin);
	DrawStringEx(x + 10, y + 60, -1, "所持コイン:%d", /*gManager->player->GetHaveCoin()*/0);
	//文字サイズ変更
	SetFontSize(16);
}

int Inventory::GetCursorNum()
{
	return selectCursor;
}

void Inventory::SetCursorNum(int MoveNum)
{
	if (selectCursor != inventoryItemList.size())return;
	selectCursor += MoveNum;
	if (selectCursor < 0)selectCursor = 0;
}


