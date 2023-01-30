#include "ItemManager.h"
#include"Item.h"

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
	//����A�C�e���̃��[�h
	auto loadCsv = tnl::LoadCsv("Csv/Item/ConsumeItem.csv");
	for (int i = 1; i < loadCsv.size(); ++i) {

		auto itemId = std::stoi(loadCsv[i][0]);
		auto itemId = std::stoi(loadCsv[i][1]);
		auto itemId = std::stoi(loadCsv[i][2]);
		auto itemId = std::stoi(loadCsv[i][3]);
		auto itemId = std::stoi(loadCsv[i][4]);


		auto item = std::make_shared<Item>();

		itemMaster[static_cast<int>(ITEMTYPE::CONSUME)].emplace_back(item);
	}
	//�����A�C�e���̃��[�h
	auto loadCsv = tnl::LoadCsv("Csv/Item/EquipItem.csv");
	for (int i = 1; i < loadCsv.size(); ++i) {

		auto itemId = std::stoi(loadCsv[i][0]);
		auto itemId = std::stoi(loadCsv[i][1]);
		auto itemId = std::stoi(loadCsv[i][2]);
		auto itemId = std::stoi(loadCsv[i][3]);
		auto itemId = std::stoi(loadCsv[i][4]);


		auto item = std::make_shared<Item>();

		itemMaster[static_cast<int>(ITEMTYPE::EQUIP)].emplace_back(item);
	}
}

ItemManager* ItemManager::GetInstance() {
	if (!instance) {
		instance = new ItemManager();
	}
	return instance;
}


std::shared_ptr<Item> ItemManager::CreateItem(int itemId, int itemType)
{
	auto data = GetItemFromId(itemId);

	auto& intData = data->GetAllIntData();
	std::string name = data->GetItemName();

	std::shared_ptr<Item>item = nullptr;

	if (itemType == static_cast<int>(ITEMTYPE::CONSUME)) {
		//����A�C�e�������
		//�ǉ��ŕK�v�ȏ�񂪂���΂�����Getter���Ă�
		//auto HP=item->GetHP();

		item = std::make_shared<Item>();
	}
	else {
		//�����A�C�e�������
		//�ǉ��ŕK�v�ȏ�񂪂���΂�����Getter���Ă�

		item = std::make_shared<Item>();
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