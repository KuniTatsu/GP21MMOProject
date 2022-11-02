#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"CreateMap.h"


void Scene_Map::initialzie()
{
	player = new Player(200, 200);
	map.emplace_back(new CreateMap(player->GetPos()));
}

void Scene_Map::update(float delta_time)
{
	/*PlayerëÄçÏ*/
	player->Update();

	/*ÉJÉÅÉâëÄçÏ*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

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
	/*Mapï`âÊ*/
	for (auto ma : map) {
		ma->Draw(&camera);
	}

	/*PlayerÇÃï`âÊ*/
	player->Draw(&camera);
	
	/*Ç«Ç±ÇÃÉVÅ[ÉìÇ≈Ç†ÇÈÇ©*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}
