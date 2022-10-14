#include "scene_map.h"
#include"../GameManager.h"
#include"../Actor/Player.h"
#include"../Map.h"

void Scene_Map::initialzie()
{
	gManager = GameManager::GetInstance();
	player = new Player(200, 200);
	new Map(player->GetPos());
}

void Scene_Map::update(float delta_time)
{
	///aaaaaaa
	/*Player����*/
	player->Update();

	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;
}

void Scene_Map::render()
{
	/*�}�b�v�`�b�v�̐���*/
	//mapChip(&cAmera);
	for (auto ma : map) {
		ma->Draw(&camera);
	}
	/*Player�̐���*/
	player->Draw(&camera);
	
	/*�ǂ��̃V�[���ł��邩*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}