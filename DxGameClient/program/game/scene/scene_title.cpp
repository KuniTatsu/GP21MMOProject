#include "../GameManager.h"
#include "scene_title.h"
#include"../Actor/Player.h"


void SceneTitle::initialzie() {
	player = std::make_shared<Player>(512,384);
}

void SceneTitle::update(float delta_time)
{
	if (!init) {
		initialzie();
		init = true;
	}


	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//	mgr->chengeScene( new ScenePlay() );
	}

	player->Update();
}

void SceneTitle::render()
{
	DrawStringEx(50, 50, -1, "scene title");

	player->Draw();
}
