//#include "InventoryManager.h"
//#include "Inventory.h"
//#include"Item/ItemManager.h"
//#include"Item/EquipItem.h"
//#include<string>
//
//InventoryManager* InventoryManager::instance = nullptr;
//
//InventoryManager::InventoryManager() {
//
//}
//
//InventoryManager::~InventoryManager()
//{
//}
//
////-----------------------------------------------------------------------------------------
///*�V���O���g��*/
//InventoryManager* InventoryManager::GetInstance(){
//	if (!instance) {
//		instance = new InventoryManager();
//	}
//	return instance;
//}
//
////-----------------------------------------------------------------------------------------
//// �j��
//void InventoryManager::Destory()
//{
//	if (instance) {
//		delete instance;
//		instance = nullptr;
//	}
//}
//
//
//
//void InventoryManager::AddItemToInventory(const int ItemId, std::vector<std::shared_ptr<Inventory>>& Inventories, int& InventoryNum)
//{
//	//����inventory�̎��A�C�e���z�񂪂����ς��Ȃ�
//	//if (Inventories[InventoryNum]->inventoryItemList.size() >= 10) {
//	//	//if (sharedInventories[inventoryNum]->inventoryList.size() >= 10) {
//	//		//�V����inventory�̃C���X�^���X�𐶐�����
//	//	Inventory* newInventory = new Inventory(InventoryNum + 1);
//	//	//inventory�z��ɓo�^
//	//	Inventories.emplace_back(newInventory);
//	//	//�o�^����inventory���X�V����
//	//	InventoryNum++;
//	//}
//	//std::shared_ptr<Item> item = iManager->GetItemData(ItemId);
//	////�����A�C�e����������
//	//if (item->getItemData(1) >= 2) {
//	//	auto eItem = static_cast<std::shared_ptr<EquipItem>>(item);
//	//	
//	//	//�����f�[�^�̎擾
//	//	std::vector<int> intData = eItem->GetAllIntData();
//	//	
//	//	//������f�[�^�̎擾
//	//	std::vector<std::string> stringData = item->GetAllStringData();
//	//	
//	//	//�����A�C�e���𐶐� �������ɃX�e�[�^�X�������_���ɕύX
//	//	auto newItem =  std::make_shared<EquipItem>();
//	//	
//	//	//�C���x���g���ǉ�
//	//	Inventories[InventoryNum]->AddInventory(newItem);
//	//}
//	//else {
//	//	std::vector<int> intData = item->GetAllIntData();
//	//	std::vector<std::string> stringData = item->GetAllStringData();
//	//	auto newItem = std::make_shared<Item>();
//	//	Inventories[InventoryNum]->AddInventory(newItem);
//	//}
//}
//
//void InventoryManager::PopItemFromInventory(const int NowInventoryId)
//{
//	//���̈ʒu�̔z��ԍ����擾
//	int selectNum = inventories[NowInventoryId]->GetCursorNum();
//	
//	//�\�����̃C���x���g�����擾
//	auto itr = inventories[NowInventoryId]->inventoryItemList.begin();
//	
//	//�I�����ꂽ�A�C�e���܂ŃC�e���[�^�ړ�
//	for (int i = 0; i < selectNum; ++i) {
//		itr++;
//	}
//	
//	//�A�C�e��������
//	//delete((*itr));
//	itr = inventories[NowInventoryId]->inventoryItemList.erase(itr);
//	
//	//�J�[�\���̈ʒu���ЂƂ�Ɉړ�
//	inventories[NowInventoryId]->SetCursorNum(-1);
//	//pop����A�C�e��������ꏊ=������C���x���g�����Ō�̃C���x���g���ł͂Ȃ��ꍇ
//	if (NowInventoryId != inventoryLastNum) {
//		int checkInventoryNum = NowInventoryId;
//		while (1) {
//			if (inventories[checkInventoryNum + 1]->inventoryItemList.empty())break;
//			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;
//		
//			//���̃y�[�W�̍ŏ��̃A�C�e�����R�s�[���ď������A�C�e���̃��X�g�̖����ɉ�����
//			auto item = inventories[checkInventoryNum + 1]->inventoryItemList.begin();
//			
//			//�A�C�e���ǉ�
//			inventories[checkInventoryNum]->inventoryItemList.emplace_back((*item));
//			
//			//���̃y�[�W�̍ŏ��̃A�C�e����pop����
//			inventories[checkInventoryNum + 1]->inventoryItemList.pop_front();
//			
//			//�Ō�̃C���x���g���y�[�W�ɂ��ǂ蒅������break
//			if (checkInventoryNum + 1 == inventoryLastNum)break;
//			checkInventoryNum++;
//		}
//	}
//	//�ŏ��̃C���x���g�����Ȃ�
//	else {
//		//�C���x���g�����̃A�C�e������1���炷
//		inventories[NowInventoryId]->SetItemNum(-1);
//	}
//	
//	//��̃C���x���g������������
//	if (inventories[inventoryLastNum]->inventoryItemList.empty()) {
//		if (inventoryLastNum != 0) {
//			/*delete inventories[inventoryLastNum]
//			inventories[inventoryLastNum] = nullptr;
//			inventories.pop_back();
//			inventoryLastNum--;*/
//			isDeleteInventory = true;
//		}
//	}
//	
//	if (isDeleteInventory)return;
//	
//	//�J�[�\���̈ʒu����ԏ�Ƀ��Z�b�g
//	if (inventories[NowInventoryId]->inventoryItemList.empty())inventories[NowInventoryId]->CursorReset();
//}
