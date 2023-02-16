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

void InventoryManager::Init()
{
	//�V����inventory�̃C���X�^���X�𐶐�����
	auto newInventory = std::make_shared<Inventory>(0);

	//inventory�z��ɓo�^
	inventories.emplace_back(newInventory);

	//debug
	AddItemToInventory(1);


}


void InventoryManager::UpdateInventory()
{
	//�I�𒆂̃C���x���g���𓮂���
	inventories[nowSelectInventoryNum]->Update();
}

/*�C���x���g���ɃA�C�e���ǉ�*/
void InventoryManager::AddItemToInventory(const int ItemId)
{
	//�X�^�b�N�𑝂₵�ďI��邩�ǂ���
	bool canFinishAddStack = false;

	//���ׂẴC���x���g���̃A�C�e����Id���������āA���Ɏ����Ă��邩�ǂ����m���߂�
	for (auto& inventory : inventories) {
		auto& itemList = inventory->GetItemList();

		for (auto itr = itemList.begin(); itr != itemList.end(); ++itr) {

			int id = (*itr)->GetItemId();
			//Id��������玟
			if (ItemId != id)continue;
			//Id�������Ă��āA�X�^�b�N���]�T�������炱���ŏI���
			if (!(*itr)->IsMaxStack()) {

				(*itr)->MoveStackNum(+1);
				canFinishAddStack = true;
				break;
			}
		}
		if (canFinishAddStack)break;
	}
	//���Ɏ����Ă���A�C�e���̃X�^�b�N���𑝂₵�Ă�����A�C�e����V�K���������ɏI���
	if (canFinishAddStack)return;

	//����inventory�̎��A�C�e���z�񂪂����ς��Ȃ�
	if (inventories[latestIntentoryNum]->GetItemList().size() >= 10) {
		//�V����inventory�̃C���X�^���X�𐶐�����
		auto newInventory = std::make_shared<Inventory>(latestIntentoryNum + 1);
		
		//inventory�z��ɓo�^
		inventories.emplace_back(newInventory);
		
		//�o�^����inventory���X�V����
		latestIntentoryNum++;
	}
	auto item = iManager->GetItemFromId(ItemId);
	
	int type = item->GetItemType();

	//�f�[�^���擾���āA�A�C�e���𐶐�
	auto createItem = iManager->CreateItem(ItemId, type);

	//�A�C�e���ǉ�
	inventories[latestIntentoryNum]->AddInventory(createItem);

}

/*�C���x���g���ɂ���A�C�e�����g�por�g���[�h�Ȃ�*/
void InventoryManager::PopItemFromInventory(const int NowInventoryId)
{
	//���̈ʒu�̔z��ԍ����擾
	int selectNum = inventories[NowInventoryId]->GetCursorNum();

	//�\�����̃C���x���g�����擾
	auto itr = inventories[NowInventoryId]->GetItemList().begin();

	//�I�����ꂽ�A�C�e���܂ŃC�e���[�^�ړ�
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}

	//�A�C�e��������
	itr = inventories[NowInventoryId]->GetItemList().erase(itr);

	//�J�[�\���̈ʒu���ЂƂ�Ɉړ�
	inventories[NowInventoryId]->SetCursorNum(-1);
	
	//pop����A�C�e��������ꏊ=������C���x���g�����Ō�̃C���x���g���ł͂Ȃ��ꍇ
	if (NowInventoryId != latestIntentoryNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->GetItemList().empty())break;
			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//���̃y�[�W�̍ŏ��̃A�C�e�����R�s�[���ď������A�C�e���̃��X�g�̖����ɉ�����
			auto item = inventories[checkInventoryNum + 1]->GetItemList().begin();

			//�A�C�e���ǉ�
			inventories[checkInventoryNum]->GetItemList().emplace_back((*item));

			//���̃y�[�W�̍ŏ��̃A�C�e����pop����
			inventories[checkInventoryNum + 1]->GetItemList().pop_front();

			//�Ō�̃C���x���g���y�[�W�ɂ��ǂ蒅������break
			if (checkInventoryNum + 1 == latestIntentoryNum)break;
			checkInventoryNum++;
		}
	}
	//�ŏ��̃C���x���g�����Ȃ�
	else {
		//�C���x���g�����̃A�C�e������1���炷
		inventories[NowInventoryId]->SetItemNum(-1);
	}

	//����̃C���x���g������������
	bool isDelete = false;

	//��̃C���x���g������������
	if (inventories[latestIntentoryNum]->GetItemList().empty()) {
		if (latestIntentoryNum != 0) {
			inventories[latestIntentoryNum]->GetItemList().clear();
			inventories[latestIntentoryNum] = nullptr;
			inventories.pop_back();
			latestIntentoryNum--;

			//fukushi_isDelteteInventory��fales�ɂȂ�ꍇ�̏������ǂ����ŕK�v
			isDelete = true;
		}
	}

	if (isDelete)return;

	//�J�[�\���̈ʒu����ԏ�Ƀ��Z�b�g
	if (inventories[NowInventoryId]->GetItemList().empty()) {
		inventories[NowInventoryId]->CursorReset();
	}
}

void InventoryManager::DrawInventory(float x, float y)
{
	inventories[nowSelectInventoryNum]->DrawInventory(x, y);
}
