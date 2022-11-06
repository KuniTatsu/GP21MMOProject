#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"


Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
	//プレイヤーの生成
	player=gManager->CreatePlayer();
	//マップの生成
	gManager->CreateMap();
	//playerの初期マップを登録
	gManager->SetStayMap();


}

void Scene_Map::update(float delta_time)
{
	/*Player操作*/
	player->Update();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		gManager->CreateMap();
	}

	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	int test = static_cast<int>(player->GetPos().x);
	if ((test % 64) == 0) {
		createChipRight = true;
	}

	/*std::list<CreateMap*>::iterator it = map.begin();
	while (it != map.end()) {
		if (!(*it)->is_alive) {
			delete(*it);
			it = map.erase(it);
			continue;
		}
		it++;
	}*/
}
void Scene_Map::render()
{
	for (auto map : gManager->GetMapList()) {
		map->Draw(&camera);
	}

	/*Playerの描画*/
	player->Draw(&camera);

	/*どこのシーンであるか*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}
