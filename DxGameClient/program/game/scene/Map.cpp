#include"Map.h"
#include"../Actor/Camera.h"
#include"../GameManager.h"

Map::Map(tnl::Vector3 centerPos, int type)
{
	/*インスタンス生成*/
	gManager = GameManager::GetInstance();

	nearMaps.resize(8);

	mapType = type;

	/*チップ*/
	//村
	if (type == static_cast<int>(Map::MAPTYPE::VILLAGE)) {
		mapChipsVillageHit.resize(gManager->MAPSIZE);
		mapChipsVillageGround.resize(gManager->MAPSIZE);
		mapChipsVillageBack.resize(gManager->MAPSIZE);
		mapChipsVillageMiddle.resize(gManager->MAPSIZE);
		mapChipsVillageFront.resize(gManager->MAPSIZE);
	}

	//草原
	if (type == static_cast<int>(Map::MAPTYPE::GRASS)) {
		mapChips.resize(gManager->MAPSIZE);
	}

	mapCenterPos = centerPos;

	float dis = (gManager->MAPSIZE - 1) / 2;
	mapLeftTopPos = mapCenterPos
		- (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0)) - tnl::Vector3(gManager->CHIPWIDTH / 2, gManager->CHIPHEIGHT / 2, 0);
	mapRightBottomPos = mapCenterPos
		+ (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0)) + tnl::Vector3(gManager->CHIPWIDTH / 2, gManager->CHIPHEIGHT / 2, 0);

	//中心座標を元にマップチップを読み込んでvectorにしまう
	LoadMap();

	///*Playerのポジション代入*/
	//PlayerPos = start;

	/*画像ロード*/
	/*release_fukushi ↓修正ポイント（このままだと村以外のマップの描画ができない状態）*/
	if (type == static_cast<int>(MAPTYPE::VILLAGE)) {
		gManager->LoadDivGraphEx("graphics/LocalMapChip.png", 1992, 8, 249, 32, 32, img_mapchip_localmap);
	}
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_grass_line = gManager->LoadGraphEx("graphics/mapchip_grass_line.png");
}

void Map::Update(const float deltatime)
{

}

void Map::Draw(Camera* camera)
{
	DrawLayer(camera, isDrawFront, mapType);
}

void Map::SetNearMap(int dirNum, std::shared_ptr<Map> map)
{
	nearMaps[dirNum] = map;
}

/*マップのロード*/
void Map::LoadMap()
{

	/*草原マップ*/
	if (mapType == static_cast<int>(MAPTYPE::GRASS)) {
		std::vector<std::vector<std::string>>map_csv;
		map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

		for (int i = 0; i < map_csv.size(); ++i) {
			for (int k = 0; k < map_csv.size(); ++k) {
				mapChips[i].emplace_back(std::stoi(map_csv[i][k]));
			}
		}
	}

	/*村マップ*/
	if (mapType == static_cast<int>(MAPTYPE::VILLAGE)) {
		//地面＆当たり判定
		std::vector<std::vector<std::string>>map_village_hit;
		std::vector<std::vector<std::string>>map_village_ground;
		//オブジェクト
		std::vector<std::vector<std::string>>map_village_back;
		std::vector<std::vector<std::string>>map_village_middle;
		std::vector<std::vector<std::string>>map_village_front;
		map_village_hit = tnl::LoadCsv("csv/VillageMap/village_hit.csv");
		map_village_ground = tnl::LoadCsv("csv/VillageMap/village_ground.csv");
		map_village_back = tnl::LoadCsv("csv/VillageMap/village_object_back.csv");
		map_village_middle = tnl::LoadCsv("csv/VillageMap/village_object_middle.csv");
		map_village_front = tnl::LoadCsv("csv/VillageMap/village_object_front.csv");

		for (int i = 0; i < map_village_hit.size(); ++i) {
			for (int k = 0; k < map_village_hit.size(); ++k) {
				//地面＆当たり判定
				mapChipsVillageHit[i].emplace_back(std::stoi(map_village_hit[i][k]));
				mapChipsVillageGround[i].emplace_back(std::stoi(map_village_ground[i][k]));
				//オブジェクト
				mapChipsVillageBack[i].emplace_back(std::stoi(map_village_back[i][k]));
				mapChipsVillageMiddle[i].emplace_back(std::stoi(map_village_middle[i][k]));
				mapChipsVillageFront[i].emplace_back(std::stoi(map_village_front[i][k]));
			}
		}
	}
}

/*マップチップの生成、iはマスの場所番号*/
void Map::DrawLayer(Camera* camera, bool isFront, int maptype)
{
	float dis = (gManager->MAPSIZE - 1) / 2;
	float x = 0;
	float y = 0;

	/*マップごとの左上座標*/
	tnl::Vector3 leftTopVillageChipPos;
	/*中心座標の保存*/
	//村
	if (maptype == static_cast<int>(MAPTYPE::VILLAGE)) {
		leftTopVillageChipPos = mapLeftTopPos;
	}

	//レイヤー後方
	if (!isFront) {
		/*村*/
		if (maptype == static_cast<int>(MAPTYPE::VILLAGE)) {

			/*座標初期化*/
			x = leftTopVillageChipPos.x;
			y = leftTopVillageChipPos.y;

			/*村_地面*/
			for (auto h : mapChipsVillageGround) {
				for (auto w : h) {
					if (-1 != w) {
						DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
							y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
					}
					x += gManager->CHIPWIDTH;
				}
				x = leftTopVillageChipPos.x;
				y += gManager->CHIPHEIGHT;
			}

			/*座標初期化*/
			x = leftTopVillageChipPos.x;
			y = leftTopVillageChipPos.y;

			/*村_背景*/
			for (auto h : mapChipsVillageBack) {
				for (auto w : h) {
					if (-1 != w) {
						DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
							y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
					}
					x += gManager->CHIPWIDTH;
				}
				x = leftTopVillageChipPos.x;
				y += gManager->CHIPHEIGHT;
			}

			/*座標初期化*/
			x = leftTopVillageChipPos.x;
			y = leftTopVillageChipPos.y;

			/*村真ん中*/
			for (auto h : mapChipsVillageMiddle) {
				for (auto w : h) {
					if (-1 != w) {
						DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
							y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
					}
					x += gManager->CHIPWIDTH;
				}
				x = leftTopVillageChipPos.x;
				y += gManager->CHIPHEIGHT;
			}
		}

		//---------------------------------------------------------------------------------------
		/*草原*/
		if (maptype == static_cast<int>(MAPTYPE::GRASS)) {
			/*草原の左上座標*/
			tnl::Vector3 leftTopGrassChipPos = mapLeftTopPos;

			x = leftTopGrassChipPos.x;
			y = leftTopGrassChipPos.y;

			for (auto h : mapChips) {
				for (auto w : h) {
					if (0 == w) {
						DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
							y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_grass, true);
					}
					x += gManager->CHIPWIDTH;
				}
				x = leftTopGrassChipPos.x;
				y += gManager->CHIPHEIGHT;
			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------------------
	//レイヤー前方
	if (!isFront)return;

	/*村*/
	if (maptype == static_cast<int>(MAPTYPE::VILLAGE)) {
		/*座標初期化*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*村手前*/
		for (auto h : mapChipsVillageFront) {
			for (auto w : h) {
				if (-1 != w) {
					DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}

		/*座標初期化*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*村_当たり判定*/
		for (auto h : mapChipsVillageHit) {
			for (auto w : h) {
				if (-1 != w) {
					/*DrawRotaGraphF(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);*/
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}
	}

}
