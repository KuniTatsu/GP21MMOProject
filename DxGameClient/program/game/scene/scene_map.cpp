#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"CreateMap.h"
#include"Map.h"


void Scene_Map::initialzie()
{
	player = new Player(0, 0);
	//createMap = new CreateMap(player->GetPos());
	for (int i = 1; i < 10; ++i) {
		map.emplace_back(new Map(player->GetPos(), i));
	}
}

void Scene_Map::update(float delta_time)
{
	/*PlayerëÄçÏ*/
	player->Update();

	/*ÉJÉÅÉâëÄçÏ*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	int test = static_cast<int>(player->GetPos().x);
	if ((test % 64) == 0) {
		createChipRight = true;
	}

	/*std::list<CreateMap*>::iterator it = map.begin();
	while (it != map.end()) {
		if (!(*it)->is_alive) {
			delete(*it);
			it = map.erase(it);
			continue;
		}
		it++;
	}*/
}
void Scene_Map::render()
{

	DrawStringEx(100, 100, -1, "%1.0f", player->GetPos().x);


	if (createChipRight) {
		map.emplace_back(new Map(player->GetPos(), 6));
		createChipRight = false;
	}

	/*Mapï`âÊ*/
	//createMap->Draw(&camera);
	for (auto ma : map) {
		ma->Draw(&camera);
	}

	/*PlayerÇÃï`âÊ*/
	player->Draw(&camera);
	
	/*Ç«Ç±ÇÃÉVÅ[ÉìÇ≈Ç†ÇÈÇ©*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}
