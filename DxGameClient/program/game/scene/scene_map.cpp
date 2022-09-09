#include "scene_map.h"
#include"../GameManager.h"

void Scene_Map::initialzie()
{
	img_mapchip_grass = LoadGraph("graphics/mapchip_grass.png");
	img_mapchip_sea = LoadGraph("graphics/mapchip_sea.png");
}

void Scene_Map::update(float delta_time)
{
	///aaaaaaa
}

void Scene_Map::render()
{
	mapChip();
	DrawStringEx(50, 50, -1, "Scene_map");
}

void Scene_Map::mapChip()
{
	std::vector<std::vector<std::string>>map_csv;
	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

	int sx = 0;
	int sy = 0;

	int x = 0;
	int y = sy;
	for (auto h : map_csv) {
		x = sx;
		for (auto w : h) {
			int n = std::atoi(w.c_str());
			if (0 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_sea, true);
			}
			if (1 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
			}
			x += MAPCHIP_SIZE;
		}
		y += MAPCHIP_SIZE;
	}

	

}
