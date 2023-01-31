#include "InventoryManager.h"
#include "Inventory.h"
#include"Item/ItemManager.h"
#include"Item/EquipItem.h"
//#include<string>

InventoryManager* InventoryManager::instance = nullptr;

InventoryManager::InventoryManager() {
	iManager = ItemManager::GetInstance();
}

InventoryManager::~InventoryManager()
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


/*インベントリにアイテム追加*/
void InventoryManager::AddItemToInventory(const int ItemId, std::vector<std::shared_ptr<Inventory>>& Inventories, int& InventoryNum)
{
	//今のinventoryの持つアイテム配列がいっぱいなら
	if (Inventories[InventoryNum]->inventoryItemList.size() >= 10) {
		//新しくinventoryのインスタンスを生成する
		auto newInventory = std::make_shared<Inventory>(InventoryNum + 1);
		
		//inventory配列に登録
		Inventories.emplace_back(newInventory);
		
		//登録するinventoryを更新する
		InventoryNum++;
	}
	auto item = iManager->GetItemFromId(ItemId);
	
	int type = item->GetItemType();

	//データを取得して、アイテムを生成し、インベントリに追加する
	auto createItem = iManager->CreateItem(ItemId, type);

	//インベントリ追加
	Inventories[InventoryNum]->AddInventory(createItem);

}

/*インベントリにあるアイテムを使用orトレードなど*/
void InventoryManager::PopItemFromInventory(const int NowInventoryId)
{
	//今の位置の配列番号を取得
	int selectNum = inventories[NowInventoryId]->GetCursorNum();

	//表示中のインベントリを取得
	auto itr = inventories[NowInventoryId]->inventoryItemList.begin();

	//選択されたアイテムまでイテレータ移動
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}

	//アイテムを消去
	itr = inventories[NowInventoryId]->inventoryItemList.erase(itr);

	//カーソルの位置をひとつ上に移動
	inventories[NowInventoryId]->SetCursorNum(-1);
	
	//popするアイテムがいる場所=今いるインベントリが最後のインベントリではない場合
	if (NowInventoryId != inventoryLastNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->inventoryItemList.empty())break;
			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//次のページの最初のアイテムをコピーして消したアイテムのリストの末尾に加える
			auto item = inventories[checkInventoryNum + 1]->inventoryItemList.begin();

			//アイテム追加
			inventories[checkInventoryNum]->inventoryItemList.emplace_back((*item));

			//次のページの最初のアイテムをpopする
			inventories[checkInventoryNum + 1]->inventoryItemList.pop_front();

			//最後のインベントリページにたどり着いたらbreak
			if (checkInventoryNum + 1 == inventoryLastNum)break;
			checkInventoryNum++;
		}
	}
	//最初のインベントリ内なら
	else {
		//インベントリ内のアイテム数を1減らす
		inventories[NowInventoryId]->SetItemNum(-1);
	}

	//空のインベントリを消す処理
	if (inventories[inventoryLastNum]->inventoryItemList.empty()) {
		if (inventoryLastNum != 0) {
			inventories[inventoryLastNum]->inventoryItemList.clear();
			inventories[inventoryLastNum] = nullptr;
			inventories.pop_back();
			inventoryLastNum--;

			//fukushi_isDelteteInventoryがfalesになる場合の処理がどこかで必要
			isDeleteInventory = true;
		}
	}

	if (isDeleteInventory)return;

	//カーソルの位置を一番上にリセット
	if (inventories[NowInventoryId]->inventoryItemList.empty()) {
		inventories[NowInventoryId]->CursorReset();
	}
}
