#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"
#include<memory>

class Player;
class CreateMap;
class Map;
class GameManager;

class Scene_Map : public SceneBase {
public:
	Scene_Map();
	~Scene_Map();

	//std::list<CreateMap*>	map;
	std::list<Map*> map;
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	std::shared_ptr<Player> player = nullptr;
	Camera camera;

	GameManager* gManager = nullptr;

	bool createChipRight = false;

};