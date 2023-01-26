#pragma once
#include<vector>
#include<list>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"
/*
�A�C�e���̃}�X�^�[�������@�}�X�^�[��csv����ǂݍ���
�O������A�C�e���𐶐�����ׂɌĂ΂��֐��������A�ǂ̃A�C�e�����I�΂�邩��SpawnManager�ɂ���Ă��炤
�I�΂ꂽ�A�C�e���𐶐����A�Ԃ�l�ŕԂ��֐������A�O���ɍ��ꂽ�A�C�e����Ԃ�
�G����̃h���b�v�������ꍇ�́AItemManager�����t�B�[���h�h���b�v���X�g�ɓ����

*/
class Item;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();
	//�O������A�C�e������肽���Ƃ��ɌĂԊ֐�
	void SpawnItem();

	void update(float deltatime);

	enum class ITEMTYPE {
		CONSUME,
		EQUIP_WEAPON,
		EQUIP_ARMOR,
		MATERIAL,
		MAX
	};

private:
	std::shared_ptr<Item> CreateItem(int type, tnl::Vector3& spawnPos);

	void LoadItemCsv(std::string pass, std::vector< std::vector<int>>& putInVector, int type);

private:
	std::list <std::shared_ptr<Item>>fieldDropItems;

	//�A�C�e���}�X�^�[
	std::vector < std::vector<std::shared_ptr<Item>>>itemMaster;
};

