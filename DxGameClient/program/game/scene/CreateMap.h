#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include"CreateMapBase.h"

class Camera;
class GameManager;

class CreateMap  : public CreateMapBase {
public:
	CreateMap(tnl::Vector3 start);
	
	
	tnl::Vector3 PlayerPos;

	bool is_alive = true;

	const int MAPCHIP_SIZE = 32;
	int img_mapchip_grass = 0;
	int img_mapchip_sea = 0;
	
	/*マップチップの生成*/
	void CreateMapChip(Camera* camera);

	void Update(float deltatime);
	void Draw(Camera* camera);

	void UpdateMap(float deltatime) override;
	void DrawMap(Camera* camera) override;
private:

	int playerX = 0;
	int playerY = 0;

	GameManager* gManager = nullptr;

	void mapSearch(Camera* camera, int x, int y, int n);
};