#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"
#include"../Actor/DummyPlayer.h"
#include"../Actor/ActorData.h"
#include"../UI/UIManager.h"
#include"../ResourceManager.h"
#include"../Actor/NPC/SupportNPC.h"
#include"../Actor/NPC/NPC.h"
#include"../Actor/NPC/NPCManager.h"
#include"../InventoryManager.h"
#include"../EffectManager.h"
#include"../Actor/ActorDrawManager.h"
#include"../DebugDef.h"

Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
	rManager = ResourceManager::GetInstance();
	eManager = EnemyManager::GetInstance();
	iManager = InventoryManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
#ifndef DEBUG_ON

	//�`���b�g�ڑ�
	gManager->CreateChat();
#endif

#ifdef DEBUG_ON

	gManager->CreatePlayer(0);
	player = gManager->GetPlayer();
#endif // DEBUG_ON



	//�}�b�v�̐���
	gManager->CreateMap();
	//�G�l�~�[�̐���
	eManager->GetInstance();

	//player�̏����}�b�v��o�^
	gManager->SetStayMap();


#ifndef DEBUG_ON


	player = gManager->GetPlayer();
	//Dummy��������
	player->SetIsCreatedDummy();

	//�G�l�~�[�擾
	gManager->GetServerEnemyInfo();
#endif

	//NPC�̐���
	NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::SUPPORT), 180, 240, 5);

}

void Scene_Map::update(float delta_time)
{
	/*Player����*/
	player->Update();

	/*Enemy����*/
	eManager->SpawnEnemy(player->GetPos());
	/*Enemy����*/
	eManager->Update(delta_time);
	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	/*�G�l�~�[�̕`��*/
	if (eManager != nullptr) {
		eManager->Update(gManager->deltaTime);
	}

	auto npcManager = NPCManager::GetInstance();
	npcManager->Update();

	auto& pos = player->GetPos();
	npcManager->CheckNearPlayer(pos.x, pos.y);


	EffectManager::GetInstance()->Update(gManager->deltaTime);

	mainSequence.update(gManager->deltaTime);


	auto uiManager = UIManager::GetInstance();
	//���j���[�`��؂�ւ� //����̓V�[�N�G���X�ɂ��Ĉ�ԍŏ��̃V�[�N�G���X�ł̂ݕύX�\�ɂ���
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		uiManager->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU));
	}*/
	//debug
	if (uiManager->GetCanDraw()) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 0);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 1);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_3)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 2);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_4)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 3);
		}
	}



}
void Scene_Map::render()
{



	/*�}�b�v�̕`��*/
	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(false);
		map->Draw(&camera);
	}

	///*�G�l�~�[�̕`��*/
	//if (eManager != nullptr) {
	//	eManager->Draw(&camera);
	//}

	/*Player�̕`��*/
	//player->Draw(&camera);

	//Actor�̕`��
	ActorDrawManager::GetInstance()->DrawActorList(&camera);

	EffectManager::GetInstance()->Draw(&camera);

	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(true);
		map->Draw(&camera);
	}

	/*�ǂ��̃V�[���ł��邩*///debugMessage
	/*SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");*/

#ifndef DEBUG_ON


#endif

	UIManager::GetInstance()->Draw();
	NPCManager::GetInstance()->DrawSpeak();
}

bool Scene_Map::SeqWait(const float DeltaTime)
{
	return false;
}

bool Scene_Map::SeqFirstMenu(const float DeltaTime)
{
	return false;
}

bool Scene_Map::SeqStatus(const float DeltaTime)
{
	return false;
}

bool Scene_Map::SeqInventory(const float DeltaTime)
{
	return false;
}

bool Scene_Map::SeqEquip(const float DeltaTime)
{
	return false;
}

void Scene_Map::DrawWaitSequence()
{
}

void Scene_Map::DrawFirstMenuSequence()
{
}

void Scene_Map::DrawStatusSequence()
{
}

void Scene_Map::DrawInventorySequence()
{
}

void Scene_Map::DrawEquipSequence()
{
}
