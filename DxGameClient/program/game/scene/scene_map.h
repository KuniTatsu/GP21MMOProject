#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"

class GameManager;
class Player;
class Map;

class Scene_Map : public SceneBase {
public:
	Scene_Map(){}
	~Scene_Map() {}

	std::list<Map*> map;

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	GameManager* gManager = nullptr;
    Player* player = nullptr;
	Camera camera;
};