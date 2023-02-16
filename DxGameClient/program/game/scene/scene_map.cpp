#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"
#include"../Actor/DummyPlayer.h"
#include"../UI/UIManager.h"
#include"../ResourceManager.h"

Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
	rManager = ResourceManager::GetInstance();
	eManager = EnemyManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
	//プレイヤーの生成
	player = gManager->CreatePlayer();
	//マップの生成
	gManager->CreateMap();
	//エネミーの生成
	eManager->GetInstance();

	//playerの初期マップを登録
	gManager->SetStayMap();

	///*Playerの生成*/
	//player->Draw(&camera);

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


	auto uiManager = UIManager::GetInstance();
	//メニュー描画切り替え //今後はシークエンスにして一番最初のシークエンスでのみ変更可能にする
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		uiManager->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU));
	}
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



	int test = static_cast<int>(player->GetPos().x);
	if ((test % 64) == 0) {
		createChipRight = true;
	}

}
void Scene_Map::render()
{
	/*マップの描画*/
	for (auto map : gManager->GetMapList()) {
		map->Draw(&camera);
	}

	/*エネミーの描画*/
	if (eManager != nullptr) {
		eManager->Draw(&camera);
	}

	/*Playerの描画*/
	player->Draw(&camera);

	/*どこのシーンであるか*///debugMessage
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");

#ifdef DEBUG_OFF
	/*他のプレイヤーの描画*/
	auto& others = gManager->GetOtherPlayersList();
	if (!others.empty()) {
		for (auto& dummy : others) {
			dummy->Draw(&camera);
		}
	}


	
#endif

	UIManager::GetInstance()->Draw();
}
