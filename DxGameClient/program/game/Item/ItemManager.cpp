#include "ItemManager.h"
#include"Item.h"
#include"ConsumeItem.h"
#include"EquipItem.h"
#include"MaterialItem.h"
#include"../EnemyManager.h"

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
	auto loadCounsumeCsv = tnl::LoadCsv("csv/Item/ConsumeItem.csv");
	for (int i = 1; i < loadCounsumeCsv.size(); ++i) {

		int itemId = std::stoi(loadCounsumeCsv[i][0]);
		std::string itemName = loadCounsumeCsv[i][1];
		int itemRare = std::stoi(loadCounsumeCsv[i][2]);
		double itemRecovery = std::stod(loadCounsumeCsv[i][3]);
		int itemStr = std::stoi(loadCounsumeCsv[i][4]);
		int itemVit = std::stoi(loadCounsumeCsv[i][5]);
		int itemInt = std::stoi(loadCounsumeCsv[i][6]);
		int itemMin = std::stoi(loadCounsumeCsv[i][7]);
		int itemSpd = std::stoi(loadCounsumeCsv[i][8]);
		int itemDex = std::stoi(loadCounsumeCsv[i][9]);
		int itemStock = std::stoi(loadCounsumeCsv[i][10]);
		std::string desc = loadCounsumeCsv[i][11];



		auto item = std::make_shared<ConsumeItem>(itemId, itemName, itemStr, itemVit, itemInt, itemMin, itemSpd, itemDex, itemRare, itemRecovery, itemStock);

		//�A�C�e���^�C�v�̓o�^
		item->SetItemType(static_cast<int>(ITEMTYPE::CONSUME));
		//�������̓o�^
		item->SetItemDesc(desc);

		itemMaster[static_cast<int>(ITEMTYPE::CONSUME)].emplace_back(item);
	}

	//�����A�C�e���̃��[�h
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

		std::string desc = loadMaterialCsv[i][5];

		auto item = std::make_shared<MaterialItem>(id, name, materialType, rare, maxStack);

		item->SetItemType(static_cast<int>(ITEMTYPE::MATERIAL));

		item->SetItemDesc(desc);

		itemMaster[static_cast<int>(ITEMTYPE::MATERIAL)].emplace_back(item);
	}

	//�R���o�[�g�}�X�^�[�̃��[�h
	auto convertCsv = tnl::LoadCsv("csv/Item/MonsterParts.csv");

	for (int i = 1; i < convertCsv.size(); ++i) {
		//���[Id	���O	��̌�A�C�e��Id1	�E�F�C�g1	��̌�A�C�e��Id2	�E�F�C�g2	��̌�A�C�e��Id3	�E�F�C�g3	��̌�A�C�e��Id4	�E�F�C�g4

		int baseId = std::stoi(convertCsv[i][0]);

		std::string name = convertCsv[i][1];

		int partsId1 = std::stoi(convertCsv[i][2]);
		int weight1 = std::stoi(convertCsv[i][3]);

		int partsId2 = std::stoi(convertCsv[i][4]);
		int weight2 = std::stoi(convertCsv[i][5]);

		int partsId3 = std::stoi(convertCsv[i][6]);
		int weight3 = std::stoi(convertCsv[i][7]);

		int partsId4 = std::stoi(convertCsv[i][8]);
		int weight4 = std::stoi(convertCsv[i][9]);

		auto obj = std::make_shared<MaterialConverter>(baseId, name, partsId1, weight1, partsId2, weight2, partsId3, weight3, partsId4, weight4);

		convertMaster.emplace_back(obj);

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

int ItemManager::GetBaseBodyId(int enemyId)
{
	int ret = -1;
	//enemyId���玀�[��Id���擾
	int baseId = EnemyManager::GetInstance()->GetDeadBodyId(enemyId);

	//�{���͂ǂ������̃}�X�^�[�Ɏ��[Id�Ǝ��[�}�e���A��Id�̂Ђ��Â����s��
	switch (baseId)
	{
	case 2000:
		ret = 90000;
		break;
	case 2001:
		ret = 90001;
		break;
	case 2002:
		ret = 90002;
		break;
	default:
		break;
	}
	return ret;
}


std::shared_ptr<Item> ItemManager::CreateItem(int itemId, int itemType)
{
	//���A�C�e��
	std::shared_ptr<Item>item = nullptr;

	//�}�X�^�[����f�[�^�擾
	auto data = GetItemFromId(itemId);

	std::string desc = data->GetItemDesc();

	//�f�ރA�C�e���̏ꍇ�͕K�v�ȃX�e�[�^�X�����Ȃ��̂Ő�ɍ��
	if (itemType == static_cast<int>(ITEMTYPE::MATERIAL)) {

		std::shared_ptr<MaterialItem> matItem = std::dynamic_pointer_cast<MaterialItem>(data);
		int id = matItem->GetItemId();
		std::string name = matItem->GetItemName();
		int type = matItem->GetMaterialType();
		int rare = matItem->GetRare();
		int max = matItem->GetMaxStack();

		item = std::make_shared<MaterialItem>(id, name, type, rare, max);
		item->SetItemType(static_cast<int>(ITEMTYPE::MATERIAL));
	}
	else {
		//�A�C�e���̊e��f�[�^�̎擾
		auto& intData = data->GetAllIntData();
		std::string name = data->GetItemName();
		auto  id = data->GetItemId();
		auto& attirbute = data->GetAttributeData();

		int rare = data->GetRare();

		int maxStack = data->GetMaxStack();

		if (itemType == static_cast<int>(ITEMTYPE::CONSUME)) {
			//����A�C�e�������
			//�ǉ��ŕK�v�ȏ�񂪂���΂�����Getter���Ă�

			float heal = data->GetItemRecover();

			//								int ID, std::string Name, int STR, int VIT, int INT, int MID, int SPD, int DEX, int Rare, double Recover
			item = std::make_shared<ConsumeItem>(id, name, attirbute[0], attirbute[1], attirbute[2], attirbute[3]
				, attirbute[4], attirbute[5], rare, heal, maxStack);

			item->SetItemType(static_cast<int>(ITEMTYPE::CONSUME));
		}
		else if (itemType == static_cast<int>(ITEMTYPE::EQUIP)) {
			//�����A�C�e�������
			//�ǉ��ŕK�v�ȏ�񂪂���΂�����Getter���Ă�

			auto hp = data->GetHPFromEquipItem();

			item = std::make_shared<EquipItem>(id, name, hp, attirbute[0], attirbute[1], attirbute[2], attirbute[3]
				, attirbute[4], attirbute[5]);

			item->SetItemType(static_cast<int>(ITEMTYPE::EQUIP));


		}

	}
	item->SetItemDesc(desc);
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

MaterialConverter::MaterialConverter(int baseId, std::string baseName, int destId1, int weight1, int destId2, int weight2, int destId3, int weight3, int destId4, int weight4)
{
	disassemblyWeight.insert(std::make_pair(destId1, weight1));
	disassemblyWeight.insert(std::make_pair(destId2, weight2));
	disassemblyWeight.insert(std::make_pair(destId3, weight3));
	disassemblyWeight.insert(std::make_pair(destId4, weight4));

	bodyId = baseId;
	bodyName = baseName;

	weights.emplace_back(weight1);
	weights.emplace_back(weight2);
	weights.emplace_back(weight3);
	weights.emplace_back(weight4);

}

MaterialConverter::~MaterialConverter()
{
}

const std::pair<int, int>& MaterialConverter::GetMatchPair(int baseId)
{
	std::pair<int, int>ret;

	for (auto itr = disassemblyWeight.begin(); itr != disassemblyWeight.end(); ++itr) {
		if (itr->first != baseId)continue;
		ret = (*itr);
		break;
	}

	return ret;
}

int MaterialConverter::GetMatchAfterItemNum(int index)
{
	//index�̕�����itr���C���N�������g���āA�Ώۂ�����o��

	std::pair<int, int>buf;


	auto itr = disassemblyWeight.begin();

	for (int i = 0; i < index; ++i) {
		++itr;
	}
	//Id��Ԃ�
	return itr->first;
}
