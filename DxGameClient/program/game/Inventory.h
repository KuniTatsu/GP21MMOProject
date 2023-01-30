#pragma once
#include<memory>
#include<list>

class GameManager;
class ItemManager;
class Item;

class Inventory {
private:

	GameManager* gManager = nullptr;
	ItemManager* iManager = nullptr;


public:
	Inventory(int MyInventorynum);
	~Inventory();

	std::shared_ptr<Item>inventory[10] = { nullptr,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };

	////������Item��10����list
	std::list<std::shared_ptr<Item>> inventoryItemList;

	//�C���x���g�����̃A�C�e�������擾����֐�
	inline int GetItemCount() {
		return inventoryItemList.size();
	}

	//�C���x���g���ɃA�C�e����ǉ�����֐�
	void AddInventory(std::shared_ptr<Item> item);
	//void AddSharedInventory(std::shared_ptr<Item>item);
	//
	//�J�[�\�����㉺�ɓ������֐�
	void CursorMove();
	//�J�[�\������ԏ�ɖ߂��֐�
	void CursorReset();
	//�C���x���g�����̃A�C�e������`�悷��֐�
	void DrawInventory(const int x, const int y);
	//�J�[�\���őI�𒆂̃A�C�e���̐�����`�悷��֐�
	void DrawItemDesc(const int x, const int y);
	//�J�[�\���őI�𒆂̑����A�C�e���̃X�e�[�^�X��`�悷��֐�
	void DrawEquipItemStatus(const int x, const int y);
	//�V���b�v�C���x���g���p �w���z�̕\��
	void DrawNeedCoin(int x, int y);

	//�J�[�\���̈ʒu���擾����֐�
	int GetCursorNum();
	//�J�[�\���̈ʒu��ύX����֐� type:0->���Z�ړ�,1->�w��ʒu�ړ�
	void SetCursorNum(const int MoveNum);
	//�C���x���g���ԍ����擾����֐�
	inline int GetInventoryNum() {
		return myInventoryNum;
	}
	inline void SetItemNum(const int num) {
		itemNum += num;
	}


private:
	//�I�𒆂̃A�C�e�����w���J�[�\���̈ʒu
	int selectCursor = 0;
	//�J�[�\��gh
	int cursorGh = 0;
	//�I�𒆃A�C�e���̔w�i
	int selectItemBackGh = 0;
	//�C���x���g�����̃A�C�e����
	int itemNum = 0;
	//�C���x���g���ԍ�
	int myInventoryNum = 0;
};