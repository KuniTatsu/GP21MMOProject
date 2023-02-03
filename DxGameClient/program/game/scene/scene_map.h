#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"
#include<memory>
#include"../UI/UIEditor.h"

class Player;
class CreateMap;
class GameManager;
class EnemyManager;
class ResourceManager;
class InventoryManager;

class Scene_Map : public SceneBase {
public:
	Scene_Map();
	~Scene_Map();

	//std::list<CreateMap*>	map;
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	std::shared_ptr<Player> player = nullptr;
	Camera camera;

	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;
	ResourceManager* rManager = nullptr;
	InventoryManager* iManager = nullptr;

	bool createChipRight = false;

};