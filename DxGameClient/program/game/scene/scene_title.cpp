#include "../GameManager.h"
#include "scene_title.h"


void SceneTitle::initialzie() {
}

void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	mgr->chengeScene( new ScenePlay() );
	}
}

void SceneTitle::render()
{
	DrawStringEx(50, 50, -1, "scene title");
}
