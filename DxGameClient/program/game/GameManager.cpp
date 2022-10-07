#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"

GameManager* GameManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// �R���X�g���N�^
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
}

//-----------------------------------------------------------------------------------------
// �f�X�g���N�^
GameManager::~GameManager() {

}


//-----------------------------------------------------------------------------------------
// �V���O���g���̃C���X�^���X�擾
GameManager* GameManager::GetInstance() {
	if (!instance) {
		instance = new GameManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// �j��
void GameManager::Destroy() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

int GameManager::LoadGraphEx(std::string Gh)
{
	auto it = ghmap.find(Gh);
	if (it != ghmap.end()) {
		return ghmap[Gh];
	}

	else {
		int loadgh = LoadGraph(Gh.c_str());
		ghmap.insert(std::make_pair(Gh, loadgh));
	}


	return ghmap[Gh];
}

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {

	if (!init) {
		sManager = SceneManager::GetInstance();
		init = true;
	}

	sManager->Update(delta_time);
	sManager->Draw();
}










