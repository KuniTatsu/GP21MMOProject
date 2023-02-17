#include "Disassembly.h"
#include"GameManager.h"
#include"Item/ItemManager.h"
#include"InventoryManager.h"
#include"Actor/Player.h"
#include"Item/ItemManager.h"

Disassembly* Disassembly::instance = nullptr;

Disassembly::Disassembly()
{
	convertMaster.clear();

	convertMaster = ItemManager::GetInstance()->GetConvertMaster();
}

Disassembly::~Disassembly()
{
}

Disassembly* Disassembly::GetInstance()
{
	if (!instance) {
		instance = new Disassembly();
	}
	return instance;
}

void Disassembly::DisassemblyDeadBody(int deadId)
{
	//���[�������A�C�e���̌��𒊑I�@�ő�10�� ���㎀�[�̑傫���ŕϓ��\��
	int getNum = GameManager::GetInstance()->GetRandBetweenNum(1, 10);

	std::shared_ptr<MaterialConverter> buf = nullptr;

	//���[Id�ƃ}�b�`����Converter���擾����
	for (auto& masterData : convertMaster) {
		if (masterData->GetBaseId() == deadId) {
			buf = masterData;
			break;
		}
	}
	//���s
	if (buf == nullptr) {
		tnl::DebugTrace("\n�A�C�e����̎��s\n");
		return;
	}

	//���[Id�������A�C�e���ƃE�F�C�g�̃f�[�^���擾
	const auto& data = buf->GetMap();

	//��̌�ɓ���ł���A�C�e��id
	std::vector<int>itemIds;

	//�E�F�C�g�����̃f�[�^�𐶐�
	std::vector<int>weights;


	for (auto itr = data.begin(); itr != data.end(); ++itr) {

		int itemId = itr->first;
		int weight = itr->second;

		itemIds.emplace_back(itemId);
		weights.emplace_back(weight);
	}

	//�E�F�C�g�œ��肷��A�C�e���������I
	for (int i = 0; i < getNum; ++i) {
		int selectId = GameManager::GetInstance()->GerRandomNumInWeight(weights);

		//�I�΂ꂽId�̃A�C�e���𐶐����A�C���x���g���ɒǉ�����

		//auto item = ItemManager::GetInstance()->CreateItem(itemIds[selectId], static_cast<int>(ItemManager::ITEMTYPE::MATERIAL));

		auto player = GameManager::GetInstance()->GetPlayer();
		//�A�C�e�����C���x���g���ɒǉ�
		InventoryManager::GetInstance()->AddItemToInventory(itemIds[selectId]);
	}
}

