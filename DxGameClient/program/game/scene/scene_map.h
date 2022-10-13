#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"


class GameManager;
class Player;
//class Camera;

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
	void render(Camera* camera) override;
private:

	GameManager* gManager = nullptr;
    //std::shared_ptr<Player> player = nullptr;
	Player* player = nullptr;
	
	/*マップチップの生成*/
	void mapChip();
	//近接のマップの生成
	void mapSearch(int x,int y,int n);
};