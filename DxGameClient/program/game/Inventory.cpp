/*
#include "Inventory.h"
#include"DxLib.h"
#include"../../library/t2klib.h"
#include"../../support/Support.h"
#include"Item.h"
#include"equipItem.h"
#include"../GameManager.h"
#include"../Player.h"
#include"../SoundManager.h"

extern GameManager* gManager;
Inventory::Inventory(int MyInventoryNum)
{
	cursorGh = gManager->LoadGraphEx("graphics/menuCursor.png");
	selectItemBackGh = gManager->LoadGraphEx("graphics/selectItemBack.png");
	myInventoryNum = MyInventoryNum + 1;
}

Inventory::~Inventory()
{
}

void Inventory::AddInventory(Item* item)
{
	if (inventoryList.size() == 10)return;
	inventoryList.emplace_back(item);
	itemNum++;

}

void Inventory::CursorMove()
{
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP)) {
		itemNum = GetItemCount();
		gManager->sound->System_Play(gManager->sound->system_move);
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN)) {
		itemNum = GetItemCount();
		gManager->sound->System_Play(gManager->sound->system_move);
		selectCursor = (selectCursor + 1) % itemNum;
	}
}
//�C���x���g���̃J�[�\���ʒu����ԏ�Ƀ��Z�b�g����֐�
void Inventory::CursorReset()
{
	selectCursor = 0;
}
//�C���x���g�����̃A�C�e������`�悷��֐�
void Inventory::DrawInventory(int x, int y)
{
	int i = 0;



for (auto item : inventoryList) {
	//�����A�C�e���Ȃ�
	if (item->getItemData(1) >= 2) {
		equipItem* eItem = static_cast<equipItem*>(item);
		//�������̃A�C�e���Ȃ�'E'�𓪂ɕ`�悷��
		if (eItem->GetIsEquiped())DrawStringEx(x + 40, y + 10 + 30 * i, -1, "[E]");
		//�A�C�e�����̕`��
		DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->getItemName().c_str());
	}
	else {
		//�A�C�e�����̕`��
		DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->getItemName().c_str());
	}
	++i;
}
//�I�𒆃A�C�e���̉��ɃJ�[�\����`�悷��
DrawRotaGraph(x + 30, y + 20 + selectCursor * 30, 0.7, 0, cursorGh, true);
SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
DrawRotaGraph(x + 220, y + 20 + selectCursor * 30, 1, 0, selectItemBackGh, true);
SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
//�A�C�e���̐�����`�悷��֐�
void Inventory::DrawItemDesc(int x, int y)
{
	if (inventoryList.empty())return;
	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	(*itr)->DrawItemStringData(x, y);
	//inventory[selectCursor]->DrawItemData(x, y);
}

void Inventory::DrawEquipItemStatus(const int x, const int y)
{
	if (inventoryList.empty())return;

	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	//�����A�C�e���Ȃ�f�[�^���擾���ĕ`�悷��
	if ((*itr)->getItemData(1) >= 2) {
		auto item = static_cast<equipItem*>((*itr));
		item->DrawEquipItemStatus(x, y, item->GetSubId());
	}

}

void Inventory::DrawNeedCoin(int x, int y)
{
	if (inventoryList.empty())return;
	auto itr = inventoryList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryList.end()) {
			break;
		}
		itr++;
	}
	int needCoin = 0;
	if ((*itr)->getItemData(1) >= 2) {
		auto item = static_cast<equipItem*>((*itr));
		needCoin = item->getItemData(10);
	}
	else {
		needCoin = (*itr)->getItemData(5);
	}
	//�����T�C�Y�ύX
	SetFontSize(25);
	DrawStringEx(x + 10, y + 10, -1, "�w���K�v�R�C��:%d", needCoin);
	DrawStringEx(x + 10, y + 60, -1, "�����R�C��:%d", gManager->player->GetHaveCoin());
	//�����T�C�Y�ύX
	SetFontSize(16);
}

int Inventory::GetCursorNum()
{
	return selectCursor;
}

void Inventory::SetCursorNum(int MoveNum)
{
	if (selectCursor != inventoryList.size())return;
	selectCursor += MoveNum;
	if (selectCursor < 0)selectCursor = 0;

}


*/


/*

void GameManager::AddItemToInventory(const int ItemId, std::vector<Inventory*>& Inventories,
	int& InventoryNum)
{
	//����inventory�̎��A�C�e���z�񂪂����ς��Ȃ�
	if (Inventories[InventoryNum]->inventoryList.size() >= 10) {
		//if (sharedInventories[inventoryNum]->inventoryList.size() >= 10) {

			//�V����inventory�̃C���X�^���X�𐶐�����
		Inventory* newInventory = new Inventory(InventoryNum + 1);
		//inventory�z��ɓo�^
		Inventories.emplace_back(newInventory);

		//�o�^����inventory���X�V����
		InventoryNum++;
	}
	Item* item = iManager->GetItemData(ItemId);
	//�����A�C�e����������
	if (item->getItemData(1) >= 2) {
		equipItem* eItem = (equipItem*)item;
		//�����f�[�^�̎擾
		std::vector<int> intData = eItem->GetAllIntData();
		//������f�[�^�̎擾
		std::vector<std::string> stringData = item->GetAllStringData();

		//�����A�C�e���𐶐� �������ɃX�e�[�^�X�������_���ɕύX
		equipItem* newItem = new equipItem(intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4],
			stringData[1], intData[5], intData[6], stringData[2], intData[7], intData[8], intData[9], intData[10], 0);
		//�C���x���g���ǉ�
		Inventories[InventoryNum]->AddInventory(newItem);
	}
	else {
		std::vector<int> intData = item->GetAllIntData();
		std::vector<std::string> stringData = item->GetAllStringData();

		Item* newItem = new Item(intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4], intData[5], stringData[1], stringData[2]);

		Inventories[InventoryNum]->AddInventory(newItem);

	}

}

void GameManager::PopItemFromInventory(const int NowInventoryId)
{
	//���̈ʒu�̔z��ԍ����擾
	int selectNum = inventories[NowInventoryId]->GetCursorNum();
	//�\�����̃C���x���g�����擾
	auto itr = inventories[NowInventoryId]->inventoryList.begin();

	//�I�����ꂽ�A�C�e���܂ŃC�e���[�^�ړ�
	for (int i = 0; i < selectNum; ++i) {
		itr++;
	}
	//�A�C�e��������
	delete((*itr));
	itr = inventories[NowInventoryId]->inventoryList.erase(itr);
	//�J�[�\���̈ʒu���ЂƂ�Ɉړ�
	inventories[NowInventoryId]->SetCursorNum(-1);

	//pop����A�C�e��������ꏊ=������C���x���g�����Ō�̃C���x���g���ł͂Ȃ��ꍇ
	if (NowInventoryId != inventoryNum) {
		int checkInventoryNum = NowInventoryId;
		while (1) {
			if (inventories[checkInventoryNum + 1]->inventoryList.empty())break;

			//if (sharedInventories[checkInventoryNum + 1]->inventoryList.empty())break;

		//���̃y�[�W�̍ŏ��̃A�C�e�����R�s�[���ď������A�C�e���̃��X�g�̖����ɉ�����
			auto item = inventories[checkInventoryNum + 1]->inventoryList.begin();

			//�A�C�e���ǉ�
			inventories[checkInventoryNum]->inventoryList.emplace_back((*item));

			//���̃y�[�W�̍ŏ��̃A�C�e����pop����
			inventories[checkInventoryNum + 1]->inventoryList.pop_front();

			//�Ō�̃C���x���g���y�[�W�ɂ��ǂ蒅������break
			if (checkInventoryNum + 1 == inventoryNum)break;
			checkInventoryNum++;
		}
	}
	//�ŏ��̃C���x���g�����Ȃ�
	else {
		//�C���x���g�����̃A�C�e������1���炷
		inventories[NowInventoryId]->SetItemNum(-1);
	}
	//��̃C���x���g������������
	if (inventories[inventoryNum]->inventoryList.empty()) {
		if (inventoryNum != 0) {
			delete inventories[inventoryNum];
			inventories[inventoryNum] = nullptr;
			inventories.pop_back();
			inventoryNum--;
			isDeleteInventory = true;
		}
	}
	if (isDeleteInventory)return;
	//�J�[�\���̈ʒu����ԏ�Ƀ��Z�b�g
	if (inventories[NowInventoryId]->inventoryList.empty())inventories[NowInventoryId]->CursorReset();
}


*/