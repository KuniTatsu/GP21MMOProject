#include <time.h>
#include "main.h"
#include "GameManager.h"

void gameMain(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();
	mgr->Update(delta_time);
}

void gameEnd() {
	GameManager* mgr = GameManager::GetInstance();
	mgr->Destroy();
}
