#include "scene_map.h"
#include"../GameManager.h"



void Scene_Map::initialzie()
{
	gManager = GameManager::GetInstance();
	/*画像ロード*/
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_sea = gManager->LoadGraphEx("graphics/mapchip_sea.png");
	img_mapchip_player = gManager->LoadGraphEx("graphics/player_sample.png");
}


void Scene_Map::update(float delta_time)
{
	///aaaaaaa
	
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RIGHT)) {
		playerX += MAPCHIP_SIZE;
	}
}

void Scene_Map::render()
{
	/*マップチップの生成*/
	mapChip();
	
	SetFontSize(50);
	DrawRotaGraph(playerX, playerY, 1.0f, 0, img_mapchip_player, true);

	/*どこのシーンであるか*/
	DrawStringEx(50, 50, -1, "Scene_map");
}

void Scene_Map::mapChip()
{
	std::vector<std::vector<std::string>>map_csv;
	std::vector<std::vector<std::string>>::iterator itr = map_csv.begin();
	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

	int sx = 0;
	int sy = 0;

	int x = 0;
	int y = sy;

	for (auto h : map_csv) {
		x = sx;
		for (auto w : h) {
			int n = std::atoi(w.c_str());
			//------------------------------------------------------------
			/*画像の挿入＆描画範囲*/
			mapSearch(x, y, n);

			x += MAPCHIP_SIZE;
		}
		y += MAPCHIP_SIZE;
	}

}

/*Playerの周り8マス生成*/
void Scene_Map::mapSearch(int x, int y,int n)
{
	/*playerの上のセル*/
	int ArrowX00 = playerX - MAPCHIP_SIZE;
	int ArrowY00 = playerY - MAPCHIP_SIZE;
	int ArrowX01 = playerX;
	int ArrowY01 = playerY - MAPCHIP_SIZE;
	int ArrowX02 = playerX + MAPCHIP_SIZE;
	int ArrowY02 = playerY - MAPCHIP_SIZE;
	/*player中のセル*/
	int ArrowY1 = playerY;
	int ArrowX10 = playerX - MAPCHIP_SIZE;
	int ArrowX12 = playerX + MAPCHIP_SIZE;
	/*playerの下のセル*/
	int ArrowX20 = playerX - MAPCHIP_SIZE;
	int ArrowY20 = playerY + MAPCHIP_SIZE;
	int ArrowX21 = playerX;
	int ArrowY21 = playerY + MAPCHIP_SIZE;
	int ArrowX22 = playerX + MAPCHIP_SIZE;
	int ArrowY22 = playerY + MAPCHIP_SIZE;

	for (int i = 0; i < 8; i++) {
		if (x == ArrowX00 && y == ArrowY00 ||
			x == ArrowX01 && y == ArrowY01 ||
			x == ArrowX02 && y == ArrowY02 ||
			x == ArrowX10 && y == ArrowY1  ||
			x == ArrowX12 && y == ArrowY1  ||
			x == ArrowX20 && y == ArrowY20 ||
			x == ArrowX21 && y == ArrowY21 ||
			x == ArrowX22 && y == ArrowY22) {
			if (1 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
			}
			if (2 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_sea, true);
			}
		}
		
	}
}
