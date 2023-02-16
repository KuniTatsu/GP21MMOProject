#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"
#include"../Actor/DummyPlayer.h"
#include"../UI/UIManager.h"
#include"../ResourceManager.h"

Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
	rManager = ResourceManager::GetInstance();
	eManager = EnemyManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
	//�v���C���[�̐���
	player = gManager->CreatePlayer();
	//�}�b�v�̐���
	gManager->CreateMap();
	//�G�l�~�[�̐���
	eManager->GetInstance();

	//player�̏����}�b�v��o�^
	gManager->SetStayMap();

	///*Player�̐���*/
	//player->Draw(&camera);

}

void Scene_Map::update(float delta_time)
{
	/*Player����*/
	player->Update();

	/*Enemy����*/
	eManager->SpawnEnemy(player->GetPos());
	/*Enemy����*/
	eManager->Update(delta_time);
	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	/*�G�l�~�[�̕`��*/
	if (eManager != nullptr) {
		eManager->Update(gManager->deltaTime);
	}


	auto uiManager = UIManager::GetInstance();
	//���j���[�`��؂�ւ� //����̓V�[�N�G���X�ɂ��Ĉ�ԍŏ��̃V�[�N�G���X�ł̂ݕύX�\�ɂ���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		uiManager->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU));
	}
	//debug
	if (uiManager->GetCanDraw()) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 0);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 1);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_3)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 2);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_4)) {
			uiManager->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), 3);
		}
	}



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

	/*�ǂ��̃V�[���ł��邩*///debugMessage
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");

#ifdef DEBUG_OFF
	/*���̃v���C���[�̕`��*/
	auto& others = gManager->GetOtherPlayersList();
	if (!others.empty()) {
		for (auto& dummy : others) {
			dummy->Draw(&camera);
		}
	}


	
#endif

	UIManager::GetInstance()->Draw();
}
