#pragma once
#include"../../library/tnl_vector.h"
#include<memory>
#include<vector>

class Camera;
class GameManager;
class Map;

class Map {
public:

	Map(tnl::Vector3 centerPos,int type);

	int test = 0;

	void Update(const float deltatime);
	void Draw(Camera* camera);

	inline tnl::Vector3& GetMapCenterPos() {
		return mapCenterPos;
	}
	inline const std::vector<std::shared_ptr<Map>>& GetNearMaps() {
		return nearMaps;
	}

	inline tnl::Vector3& GetMapLeftTopPos() {
		return mapLeftTopPos;
	}
	inline tnl::Vector3& GetMapRightBottomPos() {
		return mapRightBottomPos;
	}


	enum class MAPTYPE : uint32_t {
		VILLAGE,
		GRASS,
		MAX
	};

	void SetNearMap(int dirNum,std::shared_ptr<Map>map);
private:
	tnl::Vector3 PlayerPos;
	GameManager* gManager = nullptr;


	//マップチップの配列
	//村
	std::vector<std::vector<int>>mapChipsVillageHit;
	std::vector<std::vector<int>>mapChipsVillageGround;
	std::vector<std::vector<int>>mapChipsVillageBack;
	std::vector<std::vector<int>>mapChipsVillageMiddle;
	std::vector<std::vector<int>>mapChipsVillageFront;
	//草原
	std::vector<std::vector<int>> mapChips;
	//マップの中心座標
	tnl::Vector3 mapCenterPos;
	//マップの左上の座標
	tnl::Vector3 mapLeftTopPos;
	//マップの右下の座標
	tnl::Vector3 mapRightBottomPos;

	//周囲の8マップ
	std::vector<std::shared_ptr<Map>>nearMaps;

	/*マップのロード*/
	//草原
	void LoadMap();
	
	/*画像ハンドル*/
	int img_mapchip_grass = 0;
	int img_mapchip_grass_line = 0;
	int img_mapchip_sea = 0;
	std::vector<int> img_mapchip_localmap;

	/*チップサイズ、配置数*/
	int chanknum = 0;

	/*マップの種類*/
	int mapType = 0;

	/*最初の初期村をロードするマップフラグ*/
	bool isLoadLocalMap = false;


	void DrawMap(Camera* camera);
};