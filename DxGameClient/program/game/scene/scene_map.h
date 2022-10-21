#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"

class Player;
class CreateMap;

class Scene_Map : public SceneBase {
public:
	Scene_Map(){}
	~Scene_Map() {}

	std::list<CreateMap*>	map;

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	Player* player = nullptr;
	Camera camera;
};