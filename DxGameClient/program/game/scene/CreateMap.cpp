#include"CreateMap.h"
#include"../GameManager.h"
#include"scene_map.h"
#include"../Actor/Camera.h"

CreateMap::CreateMap(tnl::Vector3 start)
{
	PlayerPos = start;
	/*画像ロード*/
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_sea = gManager->LoadGraphEx("graphics/mapchip_sea.png");
	img_mapchip_player = gManager->LoadGraphEx("graphics/player_sample.png");
	//sceneMap->map.emplace_back(this);
}

void CreateMap::Update(float deltatime)
{

}
void CreateMap::Draw(Camera* camera)
{
	CreateMapChip(camera);
}

void CreateMap::CreateMapChip(Camera* camera)
{
	std::vector<std::vector<std::string>>map_csv;
	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

	int sx = 0;
	int sy = 0;

	int x = 0;
	int y = sy - static_cast<int>(camera->pos.y);

	for (auto h : map_csv) {
		x = sx - static_cast<int>(camera->pos.x);
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

void CreateMap::mapSearch(Camera* camera, int x, int y, int n)
{
	playerX = static_cast<int>(PlayerPos.x) + static_cast<int>(camera->pos.x);
	playerY = static_cast<int>(PlayerPos.y) + static_cast<int>(camera->pos.y);

	/*playerの上のセル*/
	int ArrayX00 = playerX - MAPCHIP_SIZE;
	int ArrayY00 = playerY - MAPCHIP_SIZE;
	int ArrayX01 = playerX;
	int ArrayY01 = playerY - MAPCHIP_SIZE;
	int ArrayX02 = playerX + MAPCHIP_SIZE;
	int ArrayY02 = playerY - MAPCHIP_SIZE;
	/*player中のセル*/
	int ArrayY1 = playerY;
	int ArrayX10 = playerX - MAPCHIP_SIZE;
	int ArrayX12 = playerX + MAPCHIP_SIZE;
	/*playerの下のセル*/
	int ArrayX20 = playerX - MAPCHIP_SIZE;
	int ArrayY20 = playerY + MAPCHIP_SIZE;
	int ArrayX21 = playerX;
	int ArrayY21 = playerY + MAPCHIP_SIZE;
	int ArrayX22 = playerX + MAPCHIP_SIZE;
	int ArrayY22 = playerY + MAPCHIP_SIZE;

	for (int i = 0; i < 8; i++) {
		if (x == ArrayX00 && y == ArrayY00 ||
			x == ArrayX01 && y == ArrayY01 ||
			x == ArrayX02 && y == ArrayY02 ||
			x == ArrayX10 && y == ArrayY1 ||
			x == ArrayX12 && y == ArrayY1 ||
			x == ArrayX20 && y == ArrayY20 ||
			x == ArrayX21 && y == ArrayY21 ||
			x == ArrayX22 && y == ArrayY22) {
			if (1 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
			}
			if (2 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_sea, true);
			}
		}
	}
}
