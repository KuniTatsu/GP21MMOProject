#include "Inventory.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"Item/Item.h"
#include"Item/EquipItem.h"
#include"Item/ConsumeItem.h"
#include"../library/tnl_input.h"
#include"ChatBase.h"

Inventory::Inventory(int MyInventorynum)
{
	gManager = GameManager::GetInstance();
	iManager = ItemManager::GetInstance();

	cursorGh = gManager->LoadGraphEx("graphics/menuCursor.png");

	selectItemBackGh = gManager->LoadGraphEx("graphics/FrameWhite.png");
	myInventoryNum = myInventoryNum + 1;
}

Inventory::~Inventory()
{
}

/*インベントリの追加*/
void Inventory::AddInventory(std::shared_ptr<Item> item)
{
	if (inventoryItemList.size() == 10)return;
	inventoryItemList.emplace_back(item);
	itemNum++;
}

void Inventory::Update()
{
	CursorMove();
}

/*カーソルの動き（key版）*/
void Inventory::CursorMove()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + 1) % itemNum;
	}
}

/*カーソル、初期値移動*/
void Inventory::CursorReset()
{
	selectCursor = 0;
}

//インベントリ内のアイテム名を描画する関数
void Inventory::DrawInventory(int x, int y)
{
	if (inventoryItemList.empty())return;
	int i = 0;

	for (auto& item : inventoryItemList) {

		//装備アイテムなら
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			auto eItem = std::shared_ptr<EquipItem>();

			if (eItem->GetIsEquiped()) {
				//装備アイテムかつ装備するなら'E'を頭に描画する
				if (eItem->GetIsEquiped()) {
					DrawStringEx(x + 40, y + 10 + 30 * i, -1, "[E]");
				}
				//アイテム名の描画
				DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->GetItemName());
			}
		}
		else if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::CONSUME))
		{
			//アイテム名の描画
			DrawStringEx(x + 80, y + 10 + 30 * i, -1, item->GetItemName().c_str());
		}
		//個数の取得
		int stackNum = item->GetNowStackNum();
		std::string stackText = "所持数:" + std::to_string(stackNum) + "個";
		//個数の描画
		DrawStringEx(x + 200, y + 10 + 30 * i, -1, stackText.c_str());

		++i;
	}



	//選択中アイテムの横にカーソルを描画する
	DrawRotaGraph(x + 30, y + 20 + selectCursor * 30, 0.7, 0, cursorGh, true);
}

//アイテムの説明を描画する関数
void Inventory::DrawItemDesc(float x, float y)
{
	if (inventoryItemList.empty())return;

	//インベントリリストの現在カーソル中のアイテムの説明を描画する
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	(*itr)->DrawItemDesc(x, y);
	//inventoryItemList[selectCursor]->DrawItemData(x, y);

}

/*装備アイテムの説明描画*/
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
	for (auto item : inventoryItemList) {
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			auto eItem = std::shared_ptr<EquipItem>();
			eItem->DrawEquipItemStatus(x, y, eItem->GetSubId());
		}
	}
}

/*必要コインの描画*/
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
	for (auto item : inventoryItemList) {
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			//needCoin = (*itr)->getItemData(10);
		}
		else {
			//needCoin = (*itr)->getItemData(5);
		}
	}
	//文字サイズ変更
	SetFontSize(25);
	DrawStringEx(x + 10, y + 10, -1, "購入必要コイン:%d", needCoin);
	DrawStringEx(x + 10, y + 60, -1, "所持コイン:%d", 0);
	//文字サイズ変更
	SetFontSize(16);
}

bool Inventory::UseCursorItem()
{
	//選択中のアイテムの効果を発動する
	//使用できないアイテムなら使用できないとチャット欄に出力する

	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	//消費アイテムじゃないなら警告をだして終わる
	if ((*itr)->GetItemType() != static_cast<int>(ItemManager::ITEMTYPE::CONSUME)) {

		GameManager::GetInstance()->GetChat()->InsertStringToChatVector("このアイテムは使えません！");
		return false;
	}
	//消費アイテムなら使用する
	auto consumeItem = std::dynamic_pointer_cast<ConsumeItem>((*itr));

	//Develop_kunitake 今は回復アイテムのみ実装していることに注意 2023/02/16
	consumeItem->UseItem();
	std::string useString = consumeItem->GetItemName() + "を使った";
	GameManager::GetInstance()->GetChat()->InsertStringToChatVector(useString);

	return true;
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


