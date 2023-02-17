#include "Disassembly.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"InventoryManager.h"
#include"Actor/Player.h"
#include"Item/ItemManager.h"

Disassembly* Disassembly::instance = nullptr;

Disassembly::Disassembly()
{
	convertMaster.clear();

	convertMaster = ItemManager::GetInstance()->GetConvertMaster();
}

Disassembly::~Disassembly()
{
}

Disassembly* Disassembly::GetInstance()
{
	if (!instance) {
		instance = new Disassembly();
	}
	return instance;
}

void Disassembly::DisassemblyDeadBody(int deadId)
{
	//死骸から取れるアイテムの個数を抽選　最大10個 今後死骸の大きさで変動予定
	int getNum = GameManager::GetInstance()->GetRandBetweenNum(1, 10);

	std::shared_ptr<MaterialConverter> buf = nullptr;

	//死骸IdとマッチするConverterを取得する
	for (auto& masterData : convertMaster) {
		if (masterData->GetBaseId() == deadId) {
			buf = masterData;
			break;
		}
	}
	//失敗
	if (buf == nullptr) {
		tnl::DebugTrace("\nアイテム解体失敗\n");
		return;
	}

	//死骸Idから取れるアイテムとウェイトのデータを取得
	const auto& data = buf->GetMap();

	//解体後に入手できるアイテムid
	std::vector<int>itemIds;

	//ウェイトだけのデータを生成
	std::vector<int>weights;


	for (auto itr = data.begin(); itr != data.end(); ++itr) {

		int itemId = itr->first;
		int weight = itr->second;

		itemIds.emplace_back(itemId);
		weights.emplace_back(weight);
	}

	//ウェイトで入手するアイテム個数分抽選
	for (int i = 0; i < getNum; ++i) {
		int selectId = GameManager::GetInstance()->GerRandomNumInWeight(weights);

		//選ばれたIdのアイテムを生成し、インベントリに追加する

		//auto item = ItemManager::GetInstance()->CreateItem(itemIds[selectId], static_cast<int>(ItemManager::ITEMTYPE::MATERIAL));

		auto player = GameManager::GetInstance()->GetPlayer();
		//アイテムをインベントリに追加
		InventoryManager::GetInstance()->AddItemToInventory(itemIds[selectId]);
	}
}

