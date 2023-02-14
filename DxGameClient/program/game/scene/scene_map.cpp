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

	//チャット接続
	gManager->CreateChat();
#endif

#ifdef DEBUG_ON

	gManager->CreatePlayer(0);
	player = gManager->GetPlayer();
#endif // DEBUG_ON



	//マップの生成
	gManager->CreateMap();
	//エネミーの生成
	eManager->GetInstance();

	//playerの初期マップを登録
	gManager->SetStayMap();


#ifndef DEBUG_ON


	player = gManager->GetPlayer();
	//Dummy生成完了
	player->SetIsCreatedDummy();

	//エネミー取得
	gManager->GetServerEnemyInfo();
#endif

	//NPCの生成
	NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::SUPPORT), 180, 240, 5);

}

void Scene_Map::update(float delta_time)
{
	/*Player操作*/
	player->Update();

	/*Enemy生成*/
	eManager->SpawnEnemy(player->GetPos());
	/*Enemy動作*/
	eManager->Update(delta_time);
	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	/*エネミーの描画*/
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
	//メニュー描画切り替え //今後はシークエンスにして一番最初のシークエンスでのみ変更可能にする
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



	/*マップの描画*/
	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(false);
		map->Draw(&camera);
	}

	///*エネミーの描画*/
	//if (eManager != nullptr) {
	//	eManager->Draw(&camera);
	//}

	/*Playerの描画*/
	//player->Draw(&camera);

	//Actorの描画
	ActorDrawManager::GetInstance()->DrawActorList(&camera);

	EffectManager::GetInstance()->Draw(&camera);

	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(true);
		map->Draw(&camera);
	}

	/*どこのシーンであるか*///debugMessage
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
