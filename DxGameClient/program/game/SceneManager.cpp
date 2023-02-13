#include"SceneManager.h"
#include "scene/scene_base.h"
#include"scene/scene_title.h"
#include"scene/scene_map.h"

/*デバック用*/
//#define DEBUG_ON

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (!instance) {
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::Destroy()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void SceneManager::Update(float delta_time)
{
	sequence.update(delta_time);
	nowScene->render();

	//そのうちどっかに移したい
	col = static_cast<int>(255.0f * sceneTransitionAlpha);
}

void SceneManager::Draw()
{
	if (0 >= col) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, col);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, imgBlack, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void SceneManager::chengeScene(SceneBase* next)
{
	nextScene = next;
	sequence.change(&SceneManager::SeqSceneOutTransition);
}

SceneManager::SceneManager()
{
	//imgBlack = LoadGraph("graphics/black.bmp");
#ifndef DEBUG_ON
	nowScene = new SceneTitle();
#endif
	nowScene = new Scene_Map();

	nowScene->initialzie();
}

SceneManager::~SceneManager()
{
	if (nowScene) delete nowScene;
	if (nextScene) delete nextScene;
}

bool SceneManager::SeqSceneInTransition(const float delta_time)
{
	if (sequence.isStart()) {
		sceneTransitionTime = 0;
	}
	sceneTransitionTime += delta_time;

	sceneTransitionAlpha = 1.0f - (sceneTransitionTime / SCENE_TRANSITION_FIX_TIME);

	if (sceneTransitionTime > SCENE_TRANSITION_FIX_TIME) {
		sequence.change(&SceneManager::SeqUpdate);
	}
	return true;
}

bool SceneManager::SeqUpdate(const float delta_time)
{
	nowScene->update(delta_time);
	return true;
}

bool SceneManager::SeqSceneOutTransition(const float delta_time)
{
	if (sequence.isStart()) {
		sceneTransitionTime = 0;
	}
	sceneTransitionTime += delta_time;
	sceneTransitionAlpha = (sceneTransitionTime / SCENE_TRANSITION_FIX_TIME);

	if (sceneTransitionTime > SCENE_TRANSITION_FIX_TIME) {
		delete nowScene;
		nowScene = nextScene;
		nowScene->initialzie();
		nextScene = nullptr;
		sequence.change(&SceneManager::SeqSceneInTransition);
	}
	return true;
}
