#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"


Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
	eManager = EnemyManager::GetInstance();
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
	//�G�l�~�[�̐���
	eManager->GetInstance();
	//eManager->SpawnEnemy(player->GetPos());
	
	//player�̏����}�b�v��o�^
	gManager->SetStayMap();

	///*Player�̐���*/
	//player->Draw(&camera);
	
	/*�ǂ��̃V�[���ł��邩*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
	SetFontSize(16);

}

void Scene_Map::update(float delta_time)
{
	/*Player����*/
	player->Update();

	//list�̒���enemy���ׂĂɑ΂��āAplayer�Ƃ̋��������ȉ��Ȃ�player�̕��Ɉړ�������
	gManager->enemyMove();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		eManager->SpawnEnemy(player->GetPos());
	}

	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	int test = static_cast<int>(player->GetPos().x);
	if ((test % 64) == 0) {
		createChipRight = true;
	}

}
void Scene_Map::render()
{
	/*�}�b�v�̕`��*/
	for (auto map : gManager->GetMapList()) {
		map->Draw(&camera);
	}

	/*�G�l�~�[�̕`��*/
	if (eManager != nullptr) {
		eManager->Draw(&camera);
	}
	
	/*Player�̕`��*/
	player->Draw(&camera);

	/*�ǂ��̃V�[���ł��邩*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}
