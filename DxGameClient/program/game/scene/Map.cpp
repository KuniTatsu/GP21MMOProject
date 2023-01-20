#include"Map.h"
#include"../Actor/Camera.h"
#include"../GameManager.h"

Map::Map(tnl::Vector3 centerPos)
{
	/*�C���X�^���X����*/
	gManager = GameManager::GetInstance();

	nearMaps.resize(8);
	mapChips.resize(gManager->MAPSIZE);

	mapCenterPos = centerPos;

	float dis = (gManager->MAPSIZE - 1) / 2;
	mapLeftTopPos = mapCenterPos
		- (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0)) - tnl::Vector3(gManager->CHIPWIDTH / 2, gManager->CHIPHEIGHT / 2, 0);
	mapRightBottomPos = mapCenterPos
		+ (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0)) + tnl::Vector3(gManager->CHIPWIDTH / 2, gManager->CHIPHEIGHT / 2, 0);

	//���S���W�����Ƀ}�b�v�`�b�v��ǂݍ����vector�ɂ��܂�
	LoadMap();

	///*Player�̃|�W�V�������*/
	//PlayerPos = start;

	/*�摜���[�h*/
	img_mapchip_grass = gManager->LoadGraphEx("graphics/mapchip_grass.png");
	img_mapchip_grass_line = gManager->LoadGraphEx("graphics/mapchip_grass_line.png");
}

void Map::Update(const float deltatime)
{

}

void Map::Draw(Camera* camera)
{
	DrawMap(camera);
}

void Map::SetNearMap(int dirNum, std::shared_ptr<Map> map)
{
	nearMaps[dirNum] = map;
}

void Map::LoadMap()
{
	std::vector<std::vector<std::string>>map_csv;
	map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

	for (int i = 0; i < map_csv.size(); ++i) {
		for (int k = 0; k < map_csv.size(); ++k) {
			mapChips[i].emplace_back(std::stoi(map_csv[i][k]));
		}
	}
}

/*�}�b�v�`�b�v�̐����Ai�̓}�X�̏ꏊ�ԍ�*/
void Map::DrawMap(Camera* camera)
{
	float dis = (gManager->MAPSIZE - 1) / 2;
	tnl::Vector3 leftTopChipPos = mapCenterPos
		- (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0));

	int x = leftTopChipPos.x;
	int y = leftTopChipPos.y;

	for (auto h : mapChips) {
		for (auto w : h) {
			if (1 == w) {
				DrawRotaGraph(x - static_cast<int>(camera->pos.x) + (GameManager::SCREEN_WIDTH >> 1),
					y - static_cast<int>(camera->pos.y) + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_grass, true);
			}
			if (2 == w) {
				DrawRotaGraph(x - static_cast<int>(camera->pos.x) + (GameManager::SCREEN_WIDTH >> 1),
					y - static_cast<int>(camera->pos.y) + (GameManager::SCREEN_HEIGHT >> 1), 1.0, 0, img_mapchip_grass_line, true);
			}
			x += gManager->CHIPWIDTH;
		}
		x = leftTopChipPos.x;
		y += gManager->CHIPHEIGHT;
	}
}
