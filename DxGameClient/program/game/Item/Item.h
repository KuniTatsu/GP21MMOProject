#pragma once
#include<string>
#include<vector>
#include<memory>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

/*
�S�ẴA�C�e���N���X�̊��N���X
	�A�C�e���Ɋւ����{��������

*/

class Item
{
public:

	Item();

	virtual ~Item() {}

	inline int GetItemId() {
		return id;
	}

	inline int GetItemType() {
		return itemType;
	}
	inline void SetItemType(int type) {
		itemType = type;
	}

	std::vector<int>& GetAllIntData();

	inline std::vector<int>& GetAttributeData() {
		return attribute;
	}
	inline std::string GetItemName() {
		return name;
	}
	inline double GetItemRecover() {
		return recover;
	}
	inline float GetHPFromEquipItem() {
		return hp;
	}

	inline int GetRare() {
		return rare;
	}

	inline int GetMaxStack() {
		return stockMax;
	}
	//�X�^�b�N����ϓ�������֐�
	inline void MoveStackNum(int num) {
		nowStackNum += num;
	}
	//�X�^�b�N�����擾����֐�
	inline int GetNowStackNum() {
		return nowStackNum;
	}

	//Max�X�^�b�N���ǂ����Ԃ��֐�
	inline bool IsMaxStack() {
		if (nowStackNum >= stockMax)return true;
		return false;
	}

	//�������̓o�^
	inline void SetItemDesc(std::string Desc) {
		desc = Desc;
	}

	//�������̎擾
	inline std::string GetItemDesc() {
		return desc;
	}

	//�A�C�e���̐�����`�悷��֐�
	void DrawItemDesc(float x, float y);

protected:

	int id = 0;
	std::string name = "";
	double recover = 0;
	int rare = 0;
	int str = 0;
	int vit = 0;
	int inteli = 0;
	int mid = 0;
	int spd = 0;
	int dex = 0;
	int stockMax = 0;

	int itemType = 0;

	float hp = 0;

	//���݂̃X�^�b�N��
	int nowStackNum = 1;
	//attribute�ȊO��intData
	std::vector<int> intData;

	//attribute
	std::vector<int> attribute;

	//�A�C�e���̐�����
	std::string desc = "";

private:

	void SetIntData();



};
