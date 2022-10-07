#pragma once
#include"scene_base.h"
class Scene_Map : public SceneBase {
public:
	Scene_Map(){}
	~Scene_Map() {}

	int img_mapchip_grass = 0;
	int img_mapchip_sea = 0;
	int img_mapchip_player = 0;

	/*test*/
	int playerX = 64;
	int playerY = 64;
	
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	const int MAPCHIP_SIZE = 32;

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	
	void mapChip();
	void mapSearch(int x,int y,int n);
};