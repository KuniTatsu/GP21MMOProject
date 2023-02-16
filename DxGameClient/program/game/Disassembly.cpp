#include "Disassembly.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"InventoryManager.h"
#include"Actor/Player.h"


Disassembly* Disassembly::instance = nullptr;

Disassembly::Disassembly()
{
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
	int getNum = GameManager::GetInstance()->CheckRandomNumberInOdds(10);

	//死骸Idから取れるアイテムとウェイトのデータを取得
	const auto& data = disassemblyMaster[deadId];

	//解体後に入手できるアイテムid
	std::vector<int>itemIds;

	//ウェイトだけのデータを生成
	std::vector<int>weights;


	for (auto itr = data->disassemblyResult.begin(); itr != data->disassemblyResult.end(); ++itr) {

		int itemId = itr->first;
		int weight = itr->second;

		itemIds.emplace_back(itemId);
		weights.emplace_back(weight);
	}

	//ウェイトで入手するアイテム個数分抽選
	for (int i = 0; i < getNum; ++i) {
		int selectId = GameManager::GetInstance()->GerRandomNumInWeight(weights);

		//選ばれたIdのアイテムを生成し、インベントリに追加する

		//auto item = ItemManager::GetInstance()->CreateItem(selectId, static_cast<int>(ItemManager::ITEMTYPE::MATERIAL));

		auto player = GameManager::GetInstance()->GetPlayer();
		//アイテムをインベントリに追加
		InventoryManager::GetInstance()->AddItemToInventory(selectId);

	}



}


void Disassembly::LoadDisassemblyResult()
{
	auto loadCsv = tnl::LoadCsv("csv/Item/MonsterParts.csv");
	//死骸Id	名前	解体後アイテムId1	ウェイト1	解体後アイテムId2	ウェイト2	解体後アイテムId3	ウェイト3	解体後アイテムId4	ウェイト4

	for (int i = 1; i < loadCsv.size(); ++i) {

		int id = std::stoi(loadCsv[i][0]);
		std::string name = loadCsv[i][1];

		int itemId1 = std::stoi(loadCsv[i][2]);
		int weight1 = std::stoi(loadCsv[i][3]);

		int itemId2 = std::stoi(loadCsv[i][4]);
		int weight2 = std::stoi(loadCsv[i][5]);

		int itemId3 = std::stoi(loadCsv[i][6]);
		int weight3 = std::stoi(loadCsv[i][7]);

		int itemId4 = std::stoi(loadCsv[i][8]);
		int weight4 = std::stoi(loadCsv[i][9]);

		auto data = std::make_shared<DisassemblyData>(id, name, itemId1, weight1, itemId2, weight2, itemId3, weight3, itemId4, weight4);
		disassemblyMaster.emplace_back(data);
	}
}

DisassemblyData::DisassemblyData(int id, std::string Name, int id1, int weight1, int id2, int weight2, int id3, int weight3, int id4, int weight4)
{
	fromId = id;
	name = Name;

	disassemblyResult.insert(std::make_pair(id1, weight1));
	disassemblyResult.insert(std::make_pair(id2, weight2));
	disassemblyResult.insert(std::make_pair(id3, weight3));
	disassemblyResult.insert(std::make_pair(id4, weight4));
}

DisassemblyData::~DisassemblyData()
{
	disassemblyResult.clear();
}
