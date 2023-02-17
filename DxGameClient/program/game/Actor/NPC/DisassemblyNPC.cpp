#include "DisassemblyNPC.h"
#include"../../GameManager.h"
#include"../../InventoryManager.h"
#include"../../Inventory.h"
#include"../../Item/MaterialItem.h"
#include"../../Disassembly.h"
#include"../../Item/ItemManager.h"
#include"../../ResourceManager.h"
#include"../Camera.h"

DisassemblyNPC::DisassemblyNPC(float x, float y, int ghNum, float distance) :NPC(x, y, ghNum)
{
	canHearDistance = distance;
	//NPC�̘b�����e�̓ǂݍ���
	/*if (loadNPCHint(static_cast<int>(NPCTYPE::DISASSEMBLY))) {
		maxPageNum = static_cast<int>(std::floor(npcSpeaks.size() / MAXDRAWNUM));
	}*/
	emotions = ResourceManager::GetInstance()->GetEmotionGhs();

	returnKey = GameManager::GetInstance()->LoadGraphEx("graphics/Key/button_Enter.png");
	escKey = GameManager::GetInstance()->LoadGraphEx("graphics/Key/button_Escape.png");
}

DisassemblyNPC::~DisassemblyNPC()
{
}

void DisassemblyNPC::Update()
{
	//�{���̓V�[�N�G���X�Ő��䂵�Ē��点��
	//�߂���player�����Ȃ������疳������
	if (!isNearPlayer)return;

	//enter����������v���C���[�̃C���x���g���ɂ��鎀�[�����ׂĉ�̂���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//�C���x���g������Ȃ疳������


		auto& player = GameManager::GetInstance()->GetPlayer();

		auto& inventories = InventoryManager::GetInstance()->GetInventory();

		if (inventories[0]->GetItemCount() == 0)return;

		for (auto& inventory : inventories) {
			auto deadBodies = inventory->GetDeadBodies();
			for (int i = 0; i < deadBodies.size(); ++i) {

				//���[id���擾
				int id = ItemManager::GetInstance()->GetBaseBodyIdFromItemId(deadBodies[i]->GetItemId());
				Disassembly::GetInstance()->DisassemblyDeadBody(id);
			}
		}

		//���ׂĂ̎��[�A�C�e�����C���x���g���������
		InventoryManager::GetInstance()->PopAllDeadBodyFromInventory();
	}
}

void DisassemblyNPC::Draw(Camera* camera)
{

	DrawRotaGraphF(drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1), drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1),
		1, 0, ghs[10], true);

	//�߂���player�����Ȃ������疳������
	if (!isNearPlayer)return;

	if (--emoteActWait <= 0) {
		emoteActIndex++;
		emoteActWait = emoteActSpeed;
		emoteActIndex %= 3;
		emoteDrawGh = emotions[0][emoteActIndex];
	}
	DrawRotaGraphF(drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1), drawPos.y - 20 - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1, 0, emoteDrawGh, true);
}

void DisassemblyNPC::Init()
{
}
