#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"ChatBase.h"

GameManager* GameManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// �R���X�g���N�^
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
	sManager = SceneManager::GetInstance();
}

//-----------------------------------------------------------------------------------------
// �f�X�g���N�^
GameManager::~GameManager()
{
	delete chat;
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

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {

	if (chat == nullptr) {
		chat = new ChatBase();
	}


	deltaTime = delta_time;
	sManager->Update(delta_time);
	sManager->Draw();

	chat->Update();
	chat->Draw();

}










