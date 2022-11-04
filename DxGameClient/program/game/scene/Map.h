#pragma once
#include"../../library/tnl_vector.h"
#include<memory>
#include<vector>

class Camera;
class GameManager;
class Map;

class Map {
public:

	Map(tnl::Vector3 centerPos);

	int test = 0;

	void Update(const float deltatime);
	void Draw(Camera* camera);

	inline tnl::Vector3& GetMapCenterPos() {
		return mapCenterPos;
	}
	inline const std::vector<std::shared_ptr<Map>>& GetNearMaps() {
		return nearMaps;
	}
private:
	tnl::Vector3 PlayerPos;
	GameManager* gManager = nullptr;


	//マップチップの配列
	std::vector<std::vector<int>> mapChips;
	//マップの中心座標
	tnl::Vector3 mapCenterPos;
	//周囲の8マップ
	std::vector<std::shared_ptr<Map>>nearMaps;

	void LoadMap();

	/*画像ハンドル*/
	int img_mapchip_grass = 0;
	int img_mapchip_grass_line = 0;
	int img_mapchip_sea = 0;

	/*チップサイズ、配置数*/
	const int MAPCHIP_SIZE = 32;
	const int ChipMax = 5;
	const int Margin = 2;
	int chanknum = 0;

	int ChipStartX = 0;
	int ChipStartY = 0;


	void DrawMap(Camera* camera);
};