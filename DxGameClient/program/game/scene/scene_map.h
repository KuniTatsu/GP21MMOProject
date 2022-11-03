#pragma once
#include"scene_base.h"
#include"CreateMap.h"
#include"../Actor/Camera.h"

class Player;
class CreateMap;
class Map;

class Scene_Map : public SceneBase {
public:
	Scene_Map(){}
	~Scene_Map() {}

	//std::list<CreateMap*>	map;
	std::list<Map*> map;
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	Player* player = nullptr;
	CreateMap* createMap = nullptr;
	Camera camera;

	bool createChipRight = false;

};