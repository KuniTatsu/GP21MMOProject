#include "Inventory.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"Item/Item.h"
#include"Item/EquipItem.h"
#include"Item/ConsumeItem.h"
#include"Item/MaterialItem.h"

#include"../library/tnl_input.h"
#include"ChatBase.h"

Inventory::Inventory(int MyInventorynum)
{
	gManager = GameManager::GetInstance();
	iManager = ItemManager::GetInstance();

	cursorGh = gManager->LoadGraphEx("graphics/menuCursor.png");

	selectItemBackGh = gManager->LoadGraphEx("graphics/FrameWhite.png");
	myInventoryNum = myInventoryNum + 1;
}

Inventory::~Inventory()
{
}

/*�C���x���g���̒ǉ�*/
void Inventory::AddInventory(std::shared_ptr<Item> item)
{
	if (inventoryItemList.size() == 10)return;
	inventoryItemList.emplace_back(item);
	itemNum++;
}

std::vector<std::shared_ptr<MaterialItem>> Inventory::GetDeadBodies()
{
	std::vector<std::shared_ptr<MaterialItem>>ret;
	//auto itr = EnemyList.begin(); itr != EnemyList.end();
	for (auto itr = inventoryItemList.begin(); itr != inventoryItemList.end(); ++itr) {

		if ((*itr)->GetItemId() != 90000 || (*itr)->GetItemId() != 90001 || (*itr)->GetItemId() != 90002)continue;

		auto item = std::dynamic_pointer_cast<MaterialItem>((*itr));
		ret.emplace_back(item);
	}

	return ret;
}

void Inventory::Update()
{
	CursorMove();
}

/*�J�[�\���̓����ikey�Łj*/
void Inventory::CursorMove()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + 1) % itemNum;
	}
}

/*�J�[�\���A�����l�ړ�*/
void Inventory::CursorReset()
{
	selectCursor = 0;
}

//�C���x���g�����̃A�C�e������`�悷��֐�
void Inventory::DrawInventory(int x, int y)
{
	if (inventoryItemList.empty())return;
	int i = 0;

	for (auto& item : inventoryItemList) {

		//�����A�C�e���Ȃ�
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			auto eItem = std::shared_ptr<EquipItem>();

			if (eItem->GetIsEquiped()) {
				//�����A�C�e������������Ȃ�'E'�𓪂ɕ`�悷��
				if (eItem->GetIsEquiped()) {
					DrawStringEx(x + 40, y + 10 + 30 * i, -1, "[E]");
				}
				//�A�C�e�����̕`��
				DrawStringEx(x + 80, y + 10 + 30 * i, -1, "%s", item->GetItemName());
			}
		}
		else if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::CONSUME) || item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::MATERIAL))
		{
			//�A�C�e�����̕`��
			DrawStringEx(x + 80, y + 10 + 30 * i, -1, item->GetItemName().c_str());
		}
		//���̎擾
		int stackNum = item->GetNowStackNum();
		std::string stackText = "������:" + std::to_string(stackNum) + "��";
		//���̕`��
		DrawStringEx(x + 300, y + 10 + 30 * i, -1, stackText.c_str());

		++i;
	}



	//�I�𒆃A�C�e���̉��ɃJ�[�\����`�悷��
	DrawRotaGraph(x + 30, y + 20 + selectCursor * 30, 0.7, 0, cursorGh, true);
}

//�A�C�e���̐�����`�悷��֐�
void Inventory::DrawItemDesc(float x, float y)
{
	if (inventoryItemList.empty())return;

	//�C���x���g�����X�g�̌��݃J�[�\�����̃A�C�e���̐�����`�悷��
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	(*itr)->DrawItemDesc(x, y);
	//inventoryItemList[selectCursor]->DrawItemData(x, y);

}

/*�����A�C�e���̐����`��*/
void Inventory::DrawEquipItemStatus(const int x, const int y)
{
	if (inventoryItemList.empty())return;
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	//�����A�C�e���Ȃ�f�[�^���擾���ĕ`�悷��
	for (auto item : inventoryItemList) {
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			auto eItem = std::shared_ptr<EquipItem>();
			eItem->DrawEquipItemStatus(x, y, eItem->GetSubId());
		}
	}
}

/*�K�v�R�C���̕`��*/
void Inventory::DrawNeedCoin(int x, int y)
{
	if (inventoryItemList.empty())return;
	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}

	int needCoin = 0;
	for (auto item : inventoryItemList) {
		if (item->GetItemType() == static_cast<int>(ItemManager::ITEMTYPE::EQUIP)) {
			//needCoin = (*itr)->getItemData(10);
		}
		else {
			//needCoin = (*itr)->getItemData(5);
		}
	}
	//�����T�C�Y�ύX
	SetFontSize(25);
	DrawStringEx(x + 10, y + 10, -1, "�w���K�v�R�C��:%d", needCoin);
	DrawStringEx(x + 10, y + 60, -1, "�����R�C��:%d", 0);
	//�����T�C�Y�ύX
	SetFontSize(16);
}

bool Inventory::UseCursorItem()
{
	//�I�𒆂̃A�C�e���̌��ʂ𔭓�����
	//�g�p�ł��Ȃ��A�C�e���Ȃ�g�p�ł��Ȃ��ƃ`���b�g���ɏo�͂���

	auto itr = inventoryItemList.begin();
	for (int i = 0; i < selectCursor; ++i) {
		if (itr == inventoryItemList.end()) {
			break;
		}
		itr++;
	}
	//����A�C�e������Ȃ��Ȃ�x���������ďI���
	if ((*itr)->GetItemType() != static_cast<int>(ItemManager::ITEMTYPE::CONSUME)) {

		GameManager::GetInstance()->GetChat()->InsertStringToChatVector("���̃A�C�e���͎g���܂���I");
		return false;
	}
	//����A�C�e���Ȃ�g�p����
	auto consumeItem = std::dynamic_pointer_cast<ConsumeItem>((*itr));

	//Develop_kunitake ���͉񕜃A�C�e���̂ݎ������Ă��邱�Ƃɒ��� 2023/02/16
	consumeItem->UseItem();
	std::string useString = consumeItem->GetItemName() + "���g����";
	GameManager::GetInstance()->GetChat()->InsertStringToChatVector(useString);

	return true;
}

int Inventory::GetCursorNum()
{
	return selectCursor;
}

void Inventory::SetCursorNum(int MoveNum)
{
	if (selectCursor != inventoryItemList.size())return;
	selectCursor += MoveNum;
	if (selectCursor < 0)selectCursor = 0;
}


