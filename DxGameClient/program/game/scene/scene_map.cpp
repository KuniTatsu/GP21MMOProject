#include "scene_map.h"
#include"../GameManager.h"
#include"../Actor/Player.h"

void Scene_Map::initialzie()
{
	gManager = GameManager::GetInstance();
	player = new Player(200, 200);
	/*画像ロード*/
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_sea = gManager->LoadGraphEx("graphics/mapchip_sea.png");
	img_mapchip_player = gManager->LoadGraphEx("graphics/player_sample.png");
}


void Scene_Map::update(float delta_time)
{
	///aaaaaaa
	/*Player操作*/
	player->Update();

	/*カメラ操作*/
	cAmera.pos += (player->GetPos() - cAmera.pos) * 0.1f;
}

void Scene_Map::render()
{
	/*マップチップの生成*/
	mapChip(&cAmera);

	/*Playerの生成*/
	player->Draw(&cAmera);
	
	/*どこのシーンであるか*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
	SetFontSize(16);
}

void Scene_Map::mapChip(Camera* camera)
{
	std::vector<std::vector<std::string>>map_csv;
	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

	int sx = 0;
	int sy = 0;

	int x = 0 - camera->pos.x;
	int y = sy - camera->pos.y;

	for (auto h : map_csv) {
		x = sx;
		for (auto w : h) {
			int n = std::atoi(w.c_str());
			//------------------------------------------------------------
			/*画像の挿入＆描画範囲*/
			//mapSearch(camera,x, y, n);
			if (1 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
			}
			x += MAPCHIP_SIZE;
		}
		y += MAPCHIP_SIZE;
	}

}

/*Playerの周り8マス生成*/
void Scene_Map::mapSearch(Camera* camera,int x, int y,int n)
{

	//playerX = 64 + camera->pos.x;
	//playerY = 64 + camera->pos.y;
	/*playerの上のセル*/
	int ArrowX00 = (playerX - MAPCHIP_SIZE) + camera->pos.x;
	int ArrowY00 = (playerY - MAPCHIP_SIZE) + camera->pos.y;
	int ArrowX01 = playerX + camera->pos.x;
	int ArrowY01 = (playerY - MAPCHIP_SIZE) + camera->pos.y;
	int ArrowX02 = (playerX + MAPCHIP_SIZE) + camera->pos.x;
	int ArrowY02 = (playerY - MAPCHIP_SIZE) + camera->pos.y;
	/*player中のセル*/
	int ArrowY1 = playerY + camera->pos.y;
	int ArrowX10 = (playerX - MAPCHIP_SIZE) + camera->pos.x;
	int ArrowX12 = (playerX + MAPCHIP_SIZE) + camera->pos.x;
	/*playerの下のセル*/
	int ArrowX20 = (playerX - MAPCHIP_SIZE) + camera->pos.x;
	int ArrowY20 = (playerY + MAPCHIP_SIZE) + camera->pos.y;
	int ArrowX21 = playerX + camera->pos.x;
	int ArrowY21 = (playerY + MAPCHIP_SIZE) + camera->pos.y;
	int ArrowX22 = (playerX + MAPCHIP_SIZE) + camera->pos.x;
	int ArrowY22 = (playerY + MAPCHIP_SIZE) + camera->pos.y;

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
