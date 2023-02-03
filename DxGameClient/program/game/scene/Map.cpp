#include"Map.h"
#include"../Actor/Camera.h"
#include"../GameManager.h"

Map::Map(tnl::Vector3 centerPos, int type)
{
	/*�C���X�^���X����*/
	gManager = GameManager::GetInstance();

	nearMaps.resize(8);

	mapType = type;

	/*�`�b�v*/
	//��
	if (type == static_cast<int>(Map::MAPTYPE::VILLAGE)) {
		mapChipsVillageHit.resize(gManager->MAPSIZE);
		mapChipsVillageGround.resize(gManager->MAPSIZE);
		mapChipsVillageBack.resize(gManager->MAPSIZE);
		mapChipsVillageMiddle.resize(gManager->MAPSIZE);
		mapChipsVillageFront.resize(gManager->MAPSIZE);
	}

	//����
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

	//���S���W�����Ƀ}�b�v�`�b�v��ǂݍ����vector�ɂ��܂�
	LoadMap();

	///*Player�̃|�W�V�������*/
	//PlayerPos = start;

	/*�摜���[�h*/
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
	DrawMap(camera);
}

void Map::SetNearMap(int dirNum, std::shared_ptr<Map> map)
{
	nearMaps[dirNum] = map;
}

/*�}�b�v�̃��[�h*/
void Map::LoadMap()
{

	/*�����}�b�v*/
	if (mapType == static_cast<int>(MAPTYPE::GRASS)) {
		std::vector<std::vector<std::string>>map_csv;
		map_csv = tnl::LoadCsv("csv/mapchip_island.csv");

		for (int i = 0; i < map_csv.size(); ++i) {
			for (int k = 0; k < map_csv.size(); ++k) {
				mapChips[i].emplace_back(std::stoi(map_csv[i][k]));
			}
		}
	}

	/*���}�b�v*/
	if (mapType == static_cast<int>(MAPTYPE::VILLAGE)) {
		//�n�ʁ������蔻��
		std::vector<std::vector<std::string>>map_village_hit;
		std::vector<std::vector<std::string>>map_village_ground;
		//�I�u�W�F�N�g
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
				//�n�ʁ������蔻��
				mapChipsVillageHit[i].emplace_back(std::stoi(map_village_hit[i][k]));
				mapChipsVillageGround[i].emplace_back(std::stoi(map_village_ground[i][k]));
				//�I�u�W�F�N�g
				mapChipsVillageBack[i].emplace_back(std::stoi(map_village_back[i][k]));
				mapChipsVillageMiddle[i].emplace_back(std::stoi(map_village_middle[i][k]));
				mapChipsVillageFront[i].emplace_back(std::stoi(map_village_front[i][k]));
			}
		}
	}
}

/*�}�b�v�`�b�v�̐����Ai�̓}�X�̏ꏊ�ԍ�*/
void Map::DrawMap(Camera* camera)
{
	float dis = (gManager->MAPSIZE - 1) / 2;

	/*���̍�����W*/
	tnl::Vector3 leftTopVillageChipPos;
	if (mapType == static_cast<int>(MAPTYPE::VILLAGE)) {
		leftTopVillageChipPos = mapCenterPos - (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0));
	}

	/*�����Ȃǂ̎��Ӓn�`���\*/
	tnl::Vector3 leftTopChipPos = mapCenterPos
		- (tnl::Vector3(gManager->CHIPWIDTH, gManager->CHIPHEIGHT, 0) *
			tnl::Vector3(dis, dis, 0));

	int x = 0;
	int y = 0;

	/*�ŏ��̑�*/
	if (mapType == static_cast<int>(MAPTYPE::VILLAGE)) {

		x = static_cast<int>(leftTopVillageChipPos.x);
		y = static_cast<int>(leftTopVillageChipPos.y);


		/*�n��*/
		for (auto h : mapChipsVillageGround) {
			for (auto w : h) {
				if (-1 != w) {
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}

		/*���W������*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*��_�w�i*/
		for (auto h : mapChipsVillageBack) {
			for (auto w : h) {
				if (-1 != w) {
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}

		/*���W������*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*���^��*/
		for (auto h : mapChipsVillageMiddle) {
			for (auto w : h) {
				if (-1 != w) {
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}

		/*���W������*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*����O*/
		for (auto h : mapChipsVillageFront) {
			for (auto w : h) {
				if (-1 != w) {
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}

		/*���W������*/
		x = leftTopVillageChipPos.x;
		y = leftTopVillageChipPos.y;

		/*��_�����蔻��*/
		for (auto h : mapChipsVillageHit) {
			for (auto w : h) {
				if (-1 != w) {
					int gh = img_mapchip_localmap[w];
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_localmap[w], true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopVillageChipPos.x;
			y += gManager->CHIPHEIGHT;
		}
	}

	/*����*/
	if (mapType == static_cast<int>(MAPTYPE::GRASS)) {

		x = leftTopChipPos.x;
		y = leftTopChipPos.y;

		for (auto h : mapChips) {
			for (auto w : h) {
				if (0 == w) {
					DrawRotaGraph(x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1),
						y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1), 1.0f, 0, img_mapchip_grass, true);
				}
				x += gManager->CHIPWIDTH;
			}
			x = leftTopChipPos.x;
			y += gManager->CHIPHEIGHT;
		}
	}
}
