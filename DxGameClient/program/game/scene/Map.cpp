#include"Map.h"
#include"../Actor/Camera.h"
#include"../GameManager.h"

Map::Map(tnl::Vector3 start, int Chanknum)
{
	/*インスタンス生成*/
	gManager = GameManager::GetInstance();

	/*Playerのポジション代入*/
	PlayerPos = start;

	chanknum = Chanknum;

	/*画像ロード*/
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_grass_line = gManager->LoadGraphEx("graphics/mapchip_grass_line.png");
}

void Map::Update(const float deltatime)
{

}

void Map::Draw(Camera* camera)
{
	/*for (int i = 1; i < 10; ++i) {
		MapChipCreate(camera, i);
	}*/
	MapChipCreate(camera, chanknum);
}

/*マップチップの生成、iはマスの場所番号*/
void Map::MapChipCreate(Camera* camera, int i)
{
	std::vector<std::vector<std::string>>map_csv;
	//map_csv = tnl::LoadCsv("csv/mapchip_island.csv");
	map_csv = tnl::LoadCsv("csv/test.csv");

	/*PosX*/
	if (1 == i || 4 == i || 7 == i) {
		ChipStartX = static_cast<int>(PlayerPos.x) + (gManager->SCREEN_WIDTH >> 1)
			- (MAPCHIP_SIZE * (ChipMax + Margin));
	}
	if (2 == i || 5 == i || 8 == i) {
		ChipStartX = static_cast<int>(PlayerPos.x) + (gManager->SCREEN_WIDTH >> 1)
			- (MAPCHIP_SIZE * (ChipMax >> 1));
	}
	if (3 == i || 6 == i || 9 == i) {
		ChipStartX = static_cast<int>(PlayerPos.x) + (gManager->SCREEN_WIDTH >> 1)
			+ (MAPCHIP_SIZE * (Margin + 1));
	}
	/*PosY*/
	if (1 == i || 2 == i || 3 == i) {
		ChipStartY = static_cast<int>(PlayerPos.y) + (gManager->SCREEN_HEIGHT >> 1)
			- (MAPCHIP_SIZE * (ChipMax + Margin));
	}
	if (4 == i || 5 == i || 6 == i) {
		ChipStartY = static_cast<int>(PlayerPos.y) + (gManager->SCREEN_HEIGHT >> 1)
			- (MAPCHIP_SIZE * (ChipMax >> 1));
	}
	if (7 == i || 8 == i || 9 == i) {
		ChipStartY = static_cast<int>(PlayerPos.y) + (gManager->SCREEN_HEIGHT >> 1)
			- (MAPCHIP_SIZE * (ChipMax - (ChipMax + Margin + 1)));
	}


	int x = 0;
	int y = ChipStartY - static_cast<int>(camera->pos.y);

	for (auto h : map_csv) {
		x = ChipStartX - static_cast<int>(camera->pos.x);
		for (auto w : h) {
			int n = std::atoi(w.c_str());
			//------------------------------------------------------------
			/*画像の挿入＆描画範囲*/
			//mapSearch(camera,x, y, n);
			if (1 == n) {
				DrawRotaGraph(x, y, 1.0f, 0, img_mapchip_grass, true);
			}
			if (2 == n) {
				DrawRotaGraph(x, y, 1.0, 0, img_mapchip_grass_line, true);
			}
			x += MAPCHIP_SIZE;
		}
		y += MAPCHIP_SIZE;
	}
}
