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

	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<Scene_Map> mainSequence =
		tnl::Sequence<Scene_Map>(this, &Scene_Map::SeqWait);

	//�e�V�[�N�G���X��Update�֐�
	bool SeqWait(const float DeltaTime);
	bool SeqFirstMenu(const float DeltaTime);
	bool SeqStatus(const float DeltaTime);
	bool SeqInventory(const float DeltaTime);
	bool SeqEquip(const float DeltaTime);

	//�V�[�N�G���X���Ƃ̕`��֐�
	void DrawWaitSequence();
	void DrawFirstMenuSequence();
	void DrawStatusSequence();
	void DrawInventorySequence();
	void DrawEquipSequence();

	bool createChipRight = false;

};