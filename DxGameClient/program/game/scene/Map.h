#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include"../Actor/Camera.h"

class Scene_Map;
class GameManager;

class Map {
public:
	/*マップの構成*/
	//マップチップサイズ：32×32
	//1チャンク個数:35×35
	//マップサイズ:1120×1120
	Map(tnl::Vector3 plapos);
	tnl::Vector3 PlayerPos;

	const int MAPCHIP_SIZE = 32;
	int img_mapchip_grass = 0;
	int img_mapchip_sea = 0;
	int img_mapchip_player = 0;

	/*マップチップの生成*/
	void CreateMapChip(Camera* camera);

	void Update(float deltatime);
	void Draw(Camera* camera);
private:

	int playerX = 0;
	int playerY = 0;

	//Scene_Map* scenemap = nullptr;
	GameManager* gManager = nullptr;

	void mapSearch(Camera* camera, int x, int y, int n);
};