#include "scene_map.h"
#include"../GameManager.h"
#include"../Actor/Player.h"
//#include"Map.h"

void Scene_Map::initialzie()
{
	gManager = GameManager::GetInstance();
	player = new Player(200, 200);
	//new Map(player->GetPos());
}

void Scene_Map::update(float delta_time)
{
	///aaaaaaa
	/*Player操作*/
	player->Update();

	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;
}

void Scene_Map::render()
{
	/*Playerの生成*/
	player->Draw(&camera);

	/*マップチップの生成*/
	/*for (auto ma : map) {
		ma->Draw(&camera);
	}*/
	
	
	/*どこのシーンであるか*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}