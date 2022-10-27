#include "scene_map.h"
#include"../Actor/Player.h"
//#include"CreateMap.h"
#include"../GameManager.h"

void Scene_Map::initialzie()
{
	player = new Player(200, 200);
	//new CreateMapBase();
	new CreateMap(player->GetPos());
	//map = new CreateMap(player->GetPos());
}

void Scene_Map::update(float delta_time)
{
	/*Player‘€ì*/
	player->Update();

	/*ƒJƒƒ‰‘€ì*/
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
		ma->DrawM(&camera);
	}

	std::list<CreateMap*>::iterator it = map.begin();
	while (it != map.end()) {
		if (!(*it)->is_alive) {
			delete(*it);
			it = map.erase(it);
			continue;
		}
		it++;
	}

	//map->Draw(&camera);
	
	/*Player‚Ì•`‰æ*/
	player->Draw(&camera);
	
	/*‚Ç‚±‚ÌƒV[ƒ“‚Å‚ ‚é‚©*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}

/*‚±‚Á‚¿‚Å‚Í¬Œ÷*/
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
//			/*‰æ‘œ‚Ì‘}“ü••`‰æ”ÍˆÍ*/
//			//mapSearch(camera,x, y, n);
//			if (1 == n) {
//				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
//			}
//			x += 32;
//		}
//		y += 32;
//	}
//}