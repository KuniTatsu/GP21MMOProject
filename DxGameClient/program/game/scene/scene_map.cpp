#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"
#include"../Actor/DummyPlayer.h"

Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
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

	//listの中のenemyすべてに対して、playerとの距離が一定以下ならplayerの方に移動させる
	//gManager->enemyMove();

	/*Enemy生成*/
	eManager->SpawnEnemy(player->GetPos());
	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

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

	/*他のプレイヤーの描画*/
	auto& others = gManager->GetOtherPlayersList();
	if (others.empty())return;
	for (auto& dummy : others) {
		dummy->Draw(&camera);
	}

}
