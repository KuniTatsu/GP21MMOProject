#include "ItemManager.h"
#include"Item.h"
#include"ConsumeItem.h"
#include"EquipItem.h"
#include"MaterialItem.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager::ItemManager()
{
	itemMaster.resize(static_cast<int>(ITEMTYPE::MAX));
}

ItemManager::~ItemManager()
{
}

void ItemManager::LoadCsv()
{
	//消費アイテムのロード
	auto loadCounsumeCsv = tnl::LoadCsv("csv/Item/ConsumeItem.csv");
	for (int i = 1; i < loadCounsumeCsv.size(); ++i) {

		auto itemId = std::stoi(loadCounsumeCsv[i][0]);
		auto itemName = loadCounsumeCsv[i][1];
		auto itemRare = std::stoi(loadCounsumeCsv[i][2]);
		auto itemRecovery = std::stoi(loadCounsumeCsv[i][3]);
		auto itemStr = std::stoi(loadCounsumeCsv[i][4]);
		auto itemVit = std::stoi(loadCounsumeCsv[i][5]);
		auto itemInt = std::stoi(loadCounsumeCsv[i][6]);
		auto itemMin = std::stoi(loadCounsumeCsv[i][7]);
		auto itemSpd = std::stoi(loadCounsumeCsv[i][8]);
		auto itemDex = std::stoi(loadCounsumeCsv[i][9]);
		auto itemStock = std::stoi(loadCounsumeCsv[i][10]);


		auto item = std::make_shared<ConsumeItem>(itemId, itemName, itemStr, itemVit, itemInt, itemMin, itemSpd, itemDex, itemRare, itemRecovery);

		item->SetItemType(static_cast<int>(ITEMTYPE::CONSUME));

		itemMaster[static_cast<int>(ITEMTYPE::CONSUME)].emplace_back(item);
	}

	//装備アイテムのロード
	auto loadEquipCsv = tnl::LoadCsv("csv/Item/EquipItem.csv");
	for (int i = 1; i < loadEquipCsv.size(); ++i) {

		auto itemId = std::stoi(loadEquipCsv[i][0]);
		auto itemName = loadEquipCsv[i][1];
		auto itemRare = std::stoi(loadEquipCsv[i][2]);
		auto itemStr = std::stoi(loadEquipCsv[i][3]);
		auto itemVit = std::stoi(loadEquipCsv[i][4]);


		auto item = std::make_shared<Item>();

		itemMaster[static_cast<int>(ITEMTYPE::EQUIP)].emplace_back(item);
	}

	auto loadMaterialCsv = tnl::LoadCsv("csv/Item/MaterialItem.csv");
	for (int i = 1; i < loadMaterialCsv.size(); ++i) {

		int id = std::stoi(loadMaterialCsv[i][0]);
		std::string name = loadMaterialCsv[i][1];
		int materialType = std::stoi(loadMaterialCsv[i][2]);
		int rare = std::stoi(loadMaterialCsv[i][3]);
		int maxStack = std::stoi(loadMaterialCsv[i][4]);

		auto item = std::make_shared<MaterialItem>(id, name, materialType, rare, maxStack);

		itemMaster[static_cast<int>(ITEMTYPE::MATERIAL)].emplace_back(item);
	}


}

ItemManager* ItemManager::GetInstance() {
	if (!instance) {
		instance = new ItemManager();
	}
	return instance;
}

void ItemManager::Init()
{
	LoadCsv();
}


std::shared_ptr<Item> ItemManager::CreateItem(int itemId, int itemType)
{
	//作るアイテム
	std::shared_ptr<Item>item = nullptr;

	//マスターからデータ取得
	auto data = GetItemFromId(itemId);

	//素材アイテムの場合は必要なステータスが少ないので先に作る
	if (itemType == static_cast<int>(ITEMTYPE::MATERIAL)) {

		std::shared_ptr<MaterialItem> matItem = std::dynamic_pointer_cast<MaterialItem>(data);
		int id = matItem->GetItemId();
		std::string name = matItem->GetItemName();
		int type = matItem->GetMaterialType();
		int rare = matItem->GetRare();
		int max = matItem->GetMaxStack();

		item = std::make_shared<MaterialItem>(id, name, type, rare, max);
	}
	else {
		//アイテムの各種データの取得
		auto& intData = data->GetAllIntData();
		std::string name = data->GetItemName();
		auto  id = data->GetItemId();
		auto& attirbute = data->GetAttributeData();

		int rare = data->GetRare();

		if (itemType == static_cast<int>(ITEMTYPE::CONSUME)) {
			//消費アイテムを作る
			//追加で必要な情報があればここでGetterを呼ぶ


			float heal = data->GetItemRecover();

			//								int ID, std::string Name, int STR, int VIT, int INT, int MID, int SPD, int DEX, int Rare, double Recover
			item = std::make_shared<ConsumeItem>(id, name, attirbute[0], attirbute[1], attirbute[2], attirbute[3]
				, attirbute[4], attirbute[5],rare, heal);
		}
		else if (itemType == static_cast<int>(ITEMTYPE::EQUIP)) {
			//装備アイテムを作る
			//追加で必要な情報があればここでGetterを呼ぶ

			auto hp = data->GetHPFromEquipItem();

			item = std::make_shared<EquipItem>(id, name, hp, attirbute[0], attirbute[1], attirbute[2], attirbute[3]
				, attirbute[4], attirbute[5]);
		}
	}
	return item;
}

std::vector<std::string> ItemManager::GetAllStringData()
{
	return std::vector<std::string>();
}

std::vector<int> ItemManager::GetAllIntData()
{
	return std::vector<int>();
}
std::shared_ptr<Item> ItemManager::GetItemFromId(int id) {
	for (auto& master : itemMaster) {
		for (auto& item : master) {
			if (item->GetItemId() == id) {
				return item;
				break;
			}
		}
	}
}


std::shared_ptr<Item> ItemManager::GetItemFromId(int id, int itemType)
{
	for (auto& item : itemMaster[itemType]) {
		if (item->GetItemId() == id) {
			return item;
			break;
		}
	}

}

int ItemManager::GetItemData(int id) {
	return 0;
}