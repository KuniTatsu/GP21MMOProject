#pragma once
#include<vector>
#include<memory>
//#include<list>

class Inventory;
class ItemManager;

class InventoryManager {
private:
	InventoryManager();
	~InventoryManager();

	//�C���x���g���؂�ւ�
	void MoveSelectInventory();

private:
	static InventoryManager* instance;
	ItemManager* iManager = nullptr;

	std::vector<std::shared_ptr<Inventory>>inventories;

	//���̈�ԐV�����C���x���g���ԍ�
	int latestIntentoryNum = 0;

	//�I�𒆂̃C���x���g��Num
	int nowSelectInventoryNum = 0;

public:
	static InventoryManager* GetInstance();
	void Destory();

	void Init();

	//�C���x���g���X�V
	void UpdateInventory();

	//���ׂẴC���x���g�����擾
	inline std::vector<std::shared_ptr<Inventory>>& GetInventory() {
		return inventories;
	}

	void AddItemToInventory(const int ItemId);

	//�A�C�e�������̃C���x���g������폜����֐� args:�����A�C�e��������C���x���g���̔ԍ�
	void PopItemFromInventory();

	//�C���x���g�����̂��ׂĂ̎��[�A�C�e������������֐�
	void PopAllDeadBodyFromInventory();

	//�I�𒆂̃A�C�e�����g�p����֐�
	void UseCursorItem();

	//�C���x���g���̕`��
	void DrawInventory(float x,float y);

	//�J�[�\�����̃A�C�e���̐�������\������֐�
	void DrawCursorItemDesc(float x, float y);

	//���ׂẴC���x���g�����󂩕Ԃ��֐�
	bool isEmptyAllInventory();
};