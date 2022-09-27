#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"

GameManager* GameManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
	sManager = SceneManager::GetInstance();
}

//-----------------------------------------------------------------------------------------
// デストラクタ
GameManager::~GameManager() {

}


//-----------------------------------------------------------------------------------------
// シングルトンのインスタンス取得
GameManager* GameManager::GetInstance() {
	if (!instance) {
		instance = new GameManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// 破棄
void GameManager::Destroy() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {
	sManager->Update(delta_time);
	sManager->Draw();
}










