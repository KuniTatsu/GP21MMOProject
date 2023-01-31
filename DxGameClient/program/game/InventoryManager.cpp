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
/*�V���O���g��*/
InventoryManager* InventoryManager::GetInstance() {
	if (!instance) {
		instance = new InventoryManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// �j��
void InventoryManager::Destory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}


/*�C���x���g���ɃA�C�e���ǉ�*/
void InventoryManager::AddItemToInventory(const int ItemId, std::vector<std::shared_ptr<Inventory>>& Inventories, int& InventoryNum)
{
	//����inventory�̎��A�C�e���z�񂪂����ς��Ȃ�
	if (Inventories[InventoryNum]->inventoryItemList.size() >= 10) {
		//�V����inventory�̃C���X�^���X�𐶐�����
		auto newInventory = std::make_shared<Inventory>(InventoryNum + 1);
		
		//inventory�z��ɓo�^
		Inventories.emplace_back(newInventory);
		
		//�o�^����inventory���X�V����
		InventoryNum++;
	}
	auto item = iManager->GetItemFromId(ItemId);
	
	int type = item->GetItemType();

	//�f�[�^���擾���āA�A�C�e���𐶐����A�C���x���g���ɒǉ�����
	auto createItem = iManager->CreateItem(ItemId, type);

	//�C���x���g���ǉ�
	Inventories[InventoryNum]->AddInventory(createItem);

}

/*�C���x���g���ɂ���A�C�e�����g�por�g���[�h�Ȃ�*/
void InventoryManager::PopItemFromInventory(const int NowInventoryId)
{
	//���̈ʒu�̔z��ԍ����擾
	int selectNum = inventories[NowInventoryId]->GetCursorNum();

	//�\�����̃C���x���g�����擾
	auto itr = inventories[NowInventoryId]->inventoryItemList.begin();

	//�I�����ꂽ�A�C�e���܂ŃC�e���[�^�ړ�
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}

	//�A�C�e��������
	itr = inventories[NowInventoryId]->inventoryItemList.erase(itr);

	//�J�[�\���̈ʒu���ЂƂ�Ɉړ�
	inventories[NowInventoryId]->SetCursorNum(-1);
	
	//pop����A�C�e��������ꏊ=������C���x���g�����Ō�̃C���x���g���ł͂Ȃ��ꍇ
	if (NowInventoryId != inventoryLastNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->inventoryItemList.empty())break;
			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//���̃y�[�W�̍ŏ��̃A�C�e�����R�s�[���ď������A�C�e���̃��X�g�̖����ɉ�����
			auto item = inventories[checkInventoryNum + 1]->inventoryItemList.begin();

			//�A�C�e���ǉ�
			inventories[checkInventoryNum]->inventoryItemList.emplace_back((*item));

			//���̃y�[�W�̍ŏ��̃A�C�e����pop����
			inventories[checkInventoryNum + 1]->inventoryItemList.pop_front();

			//�Ō�̃C���x���g���y�[�W�ɂ��ǂ蒅������break
			if (checkInventoryNum + 1 == inventoryLastNum)break;
			checkInventoryNum++;
		}
	}
	//�ŏ��̃C���x���g�����Ȃ�
	else {
		//�C���x���g�����̃A�C�e������1���炷
		inventories[NowInventoryId]->SetItemNum(-1);
	}

	//��̃C���x���g������������
	if (inventories[inventoryLastNum]->inventoryItemList.empty()) {
		if (inventoryLastNum != 0) {
			inventories[inventoryLastNum]->inventoryItemList.clear();
			inventories[inventoryLastNum] = nullptr;
			inventories.pop_back();
			inventoryLastNum--;

			//fukushi_isDelteteInventory��fales�ɂȂ�ꍇ�̏������ǂ����ŕK�v
			isDeleteInventory = true;
		}
	}

	if (isDeleteInventory)return;

	//�J�[�\���̈ʒu����ԏ�Ƀ��Z�b�g
	if (inventories[NowInventoryId]->inventoryItemList.empty()) {
		inventories[NowInventoryId]->CursorReset();
	}
}
