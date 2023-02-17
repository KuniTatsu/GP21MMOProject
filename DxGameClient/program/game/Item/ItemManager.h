#pragma once
#include<string>
#include<memory>
#include<list>
#include<vector>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;
class MaterialConverter;

class ItemManager
{
private:
	ItemManager();
	~ItemManager();


	void LoadCsv();
	static ItemManager* instance;


public:

	static ItemManager* GetInstance();
	void Destory();

	void Init();

	//materialCOnverterMaster�̎擾
	inline const std::vector<std::shared_ptr<MaterialConverter>>& GetConvertMaster() {
		return convertMaster;
	}

	//�G�l�~�[Id���玀�[��Id��Ԃ��֐�
	int GetBaseBodyId(int enemyId);

private:

	/*�A�C�e��[����or����][�X�e�[�^�X]*/
	std::vector<std::vector<std::shared_ptr<Item>>>itemMaster;

	//��̂̂��߂̎��[�Ƒf�ރA�C�e�����X�g
	std::vector<std::shared_ptr<MaterialConverter>> convertMaster;

public:
	/*�A�C�e�����X�g*/
	std::list<std::shared_ptr<Item>> itemList;

	enum class ITEMTYPE :uint32_t {
		CONSUME,
		EQUIP,
		MATERIAL,
		MAX
	};
	/*
	0	�Ȃ�
1	��
2	��
3	��
4	�|
5	�|
6	�����@
7	�����@
8	���@
9	�Ζ��@
10	�Ԗ��@
11	�S���@
12	�S����
	*/
	enum class WEAPONTYPE :uint32_t {
		NONE,
		SWORD,
		AXE,
		SPEAR,
		SHIELD,
		BOW,
		BLACKMAGIC,
		WHITEMAGIC,
		BLUEMAGIC,
		GREENMAGIC,
		REDMAGIC,
		MAX
	};

	std::shared_ptr<Item> CreateItem(int itemId, int itemType);
	//void DrawItemStringData(int x, int y);
	//void LoadItemMaster();

	std::vector<std::string>GetAllStringData();
	std::vector<int>GetAllIntData();
	int GetItemData(int id);
	std::shared_ptr<Item>GetItemFromId(int id);
	std::shared_ptr<Item>GetItemFromId(int id, int itemType);

};


class MaterialConverter
{
public:
	MaterialConverter(int baseId, std::string baseName, int destId1, int weight1, int destId2, int weight2, int destId3, int weight3, int destId4, int weight4);
	~MaterialConverter();

	//���[Id�ƃ}�b�`����s��Ԃ��֐�
	const std::pair<int, int>& GetMatchPair(int baseId);

	//���I�E�F�C�g�����擾����֐�
	inline const std::vector<int>& GetWeight() {
		return weights;
	}

	//���I�ԍ������̌�A�C�e��Id���擾����֐�
	int GetMatchAfterItemNum(int index);

	inline int GetBaseId() {
		return bodyId;
	}

	inline const std::unordered_map<int, int>& GetMap() {
		return disassemblyWeight;
	}

private:

	std::unordered_map<int, int> disassemblyWeight;

	//���[Id	���O	��̌�A�C�e��Id1	�E�F�C�g1	��̌�A�C�e��Id2	�E�F�C�g2	��̌�A�C�e��Id3	�E�F�C�g3	��̌�A�C�e��Id4	�E�F�C�g4

	int bodyId = -1;
	std::string bodyName = "";

	//���I�E�F�C�g�݂̂̔z��
	std::vector<int>weights = {};
};

