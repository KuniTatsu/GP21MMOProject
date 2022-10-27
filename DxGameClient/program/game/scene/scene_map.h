#pragma once
#include"scene_base.h"
#include"CreateMap.h"
#include"../Actor/Camera.h"
#include<list>

class Player;
class CreateMapBase;
//class CreateMap;

class Scene_Map : public SceneBase {
public:
	Scene_Map(){}
	~Scene_Map() {}

	std::list<CreateMapBase*> mapBase;
	std::list<CreateMap*>	map;
	//CreateMap* map = nullptr;

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	Player* player = nullptr;
	Camera camera;
};