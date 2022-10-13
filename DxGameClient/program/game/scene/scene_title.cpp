#include "../GameManager.h"
#include "scene_title.h"
#include"../Actor/Player.h"
#include"scene_map.h"
#include"../SceneManager.h"


SceneTitle::SceneTitle()
{

}

void SceneTitle::initialzie() {

	//sManager = SceneManager::GetInstance();

}

void SceneTitle::update(float delta_time)
{

	if (!init) {
		initialzie();
		init = true;
	}


	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//sManager->chengeScene(new Scene_Map());
	}
}

void SceneTitle::render(Camera* camera)
{
	DrawStringEx(50, 50, -1, "scene title");
}
