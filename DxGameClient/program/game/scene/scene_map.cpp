#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"


Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
	//�v���C���[�̐���
	player=gManager->CreatePlayer();
	//�}�b�v�̐���
	gManager->CreateMap();
	//player�̏����}�b�v��o�^
	gManager->SetStayMap();


}

void Scene_Map::update(float delta_time)
{
	/*Player����*/
	player->Update();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		gManager->CreateMap();
	}

	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	int test = static_cast<int>(player->GetPos().x);
	if ((test % 64) == 0) {
		createChipRight = true;
	}

	/*std::list<CreateMap*>::iterator it = map.begin();
	while (it != map.end()) {
		if (!(*it)->is_alive) {
			delete(*it);
			it = map.erase(it);
			continue;
		}
		it++;
	}*/
}
void Scene_Map::render()
{
	for (auto map : gManager->GetMapList()) {
		map->Draw(&camera);
	}

	/*Player�̕`��*/
	player->Draw(&camera);

	/*�ǂ��̃V�[���ł��邩*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}
