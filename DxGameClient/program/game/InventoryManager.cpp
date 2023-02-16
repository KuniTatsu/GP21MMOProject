#include "InventoryManager.h"
#include "Inventory.h"
#include"Item/ItemManager.h"
#include"Item/EquipItem.h"
#include"Item/ConsumeItem.h"
#include"Item/MaterialItem.h"
//#include<string>

InventoryManager* InventoryManager::instance = nullptr;

InventoryManager::InventoryManager() {
	iManager = ItemManager::GetInstance();
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::MoveSelectInventory()
{
}

//-----------------------------------------------------------------------------------------
/*シングルトン*/
InventoryManager* InventoryManager::GetInstance() {
	if (!instance) {
		instance = new InventoryManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// 破棄
void InventoryManager::Destory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void InventoryManager::Init()
{
	//新しくinventoryのインスタンスを生成する
	auto newInventory = std::make_shared<Inventory>(0);

	//inventory配列に登録
	inventories.emplace_back(newInventory);

	//debug
	AddItemToInventory(1);


}


void InventoryManager::UpdateInventory()
{
	//選択中のインベントリを動かす
	inventories[nowSelectInventoryNum]->Update();
}

/*インベントリにアイテム追加*/
void InventoryManager::AddItemToInventory(const int ItemId)
{
	//スタックを増やして終わるかどうか
	bool canFinishAddStack = false;

	//すべてのインベントリのアイテムのIdを検索して、既に持っているかどうか確かめる
	for (auto& inventory : inventories) {
		auto& itemList = inventory->GetItemList();

		for (auto itr = itemList.begin(); itr != itemList.end(); ++itr) {

			int id = (*itr)->GetItemId();
			//Idが違ったら次
			if (ItemId != id)continue;
			//Idがあっていて、スタックが余裕あったらここで終わる
			if (!(*itr)->IsMaxStack()) {

				(*itr)->MoveStackNum(+1);
				canFinishAddStack = true;
				break;
			}
		}
		if (canFinishAddStack)break;
	}
	//既に持っているアイテムのスタック数を増やしていたらアイテムを新規生成せずに終わる
	if (canFinishAddStack)return;

	//今のinventoryの持つアイテム配列がいっぱいなら
	if (inventories[latestIntentoryNum]->GetItemList().size() >= 10) {
		//新しくinventoryのインスタンスを生成する
		auto newInventory = std::make_shared<Inventory>(latestIntentoryNum + 1);
		
		//inventory配列に登録
		inventories.emplace_back(newInventory);
		
		//登録するinventoryを更新する
		latestIntentoryNum++;
	}
	auto item = iManager->GetItemFromId(ItemId);
	
	int type = item->GetItemType();

	//データを取得して、アイテムを生成
	auto createItem = iManager->CreateItem(ItemId, type);

	//アイテム追加
	inventories[latestIntentoryNum]->AddInventory(createItem);

}

/*インベントリにあるアイテムを使用orトレードなど*/
void InventoryManager::PopItemFromInventory(const int NowInventoryId)
{
	//今の位置の配列番号を取得
	int selectNum = inventories[NowInventoryId]->GetCursorNum();

	//表示中のインベントリを取得
	auto itr = inventories[NowInventoryId]->GetItemList().begin();

	//選択されたアイテムまでイテレータ移動
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}

	//アイテムを消去
	itr = inventories[NowInventoryId]->GetItemList().erase(itr);

	//カーソルの位置をひとつ上に移動
	inventories[NowInventoryId]->SetCursorNum(-1);
	
	//popするアイテムがいる場所=今いるインベントリが最後のインベントリではない場合
	if (NowInventoryId != latestIntentoryNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->GetItemList().empty())break;
			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//次のページの最初のアイテムをコピーして消したアイテムのリストの末尾に加える
			auto item = inventories[checkInventoryNum + 1]->GetItemList().begin();

			//アイテム追加
			inventories[checkInventoryNum]->GetItemList().emplace_back((*item));

			//次のページの最初のアイテムをpopする
			inventories[checkInventoryNum + 1]->GetItemList().pop_front();

			//最後のインベントリページにたどり着いたらbreak
			if (checkInventoryNum + 1 == latestIntentoryNum)break;
			checkInventoryNum++;
		}
	}
	//最初のインベントリ内なら
	else {
		//インベントリ内のアイテム数を1減らす
		inventories[NowInventoryId]->SetItemNum(-1);
	}

	//からのインベントリを消したか
	bool isDelete = false;

	//空のインベントリを消す処理
	if (inventories[latestIntentoryNum]->GetItemList().empty()) {
		if (latestIntentoryNum != 0) {
			inventories[latestIntentoryNum]->GetItemList().clear();
			inventories[latestIntentoryNum] = nullptr;
			inventories.pop_back();
			latestIntentoryNum--;

			//fukushi_isDelteteInventoryがfalesになる場合の処理がどこかで必要
			isDelete = true;
		}
	}

	if (isDelete)return;

	//カーソルの位置を一番上にリセット
	if (inventories[NowInventoryId]->GetItemList().empty()) {
		inventories[NowInventoryId]->CursorReset();
	}
}

void InventoryManager::DrawInventory(float x, float y)
{
	inventories[nowSelectInventoryNum]->DrawInventory(x, y);
}
