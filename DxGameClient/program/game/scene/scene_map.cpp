#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"CreateMap.h"


void Scene_Map::initialzie()
{
	player = new Player(200, 200);
	new CreateMap(player->GetPos());
}

void Scene_Map::update(float delta_time)
{
	/*Player操作*/
	player->Update();

	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

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

	for (auto ma : map) {
		ma->Draw(&camera);
	}

	/*Playerの描画*/
	player->Draw(&camera);
	
	/*どこのシーンであるか*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}

/*こっちでは成功*/
//void Scene_Map::test(Camera* camera) {
//	std::vector<std::vector<std::string>>map_csv;
//	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");
//
//	int sx = 0;
//	int sy = 0;
//
//	int x = 0;
//	int y = sy - static_cast<int>(camera->pos.y);
//
//	for (auto h : map_csv) {
//		x = sx - static_cast<int>(camera->pos.x);
//		for (auto w : h) {
//			int n = std::atoi(w.c_str());
//			//------------------------------------------------------------
//			/*画像の挿入＆描画範囲*/
//			//mapSearch(camera,x, y, n);
//			if (1 == n) {
//				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
//			}
//			x += 32;
//		}
//		y += 32;
//	}
//}