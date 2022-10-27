#include "scene_map.h"
#include"../Actor/Player.h"
#include"CreateMap.h"
#include"CreateMapBase.h"
#include"../GameManager.h"

void Scene_Map::initialzie()
{
	player = new Player(200, 200);
	//new CreateMapBase();
	new CreateMap(player->GetPos());
}

void Scene_Map::update(float delta_time)
{
	///aaaaaaa
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

	//for (auto ma : map) {
	//	ma->Draw(&camera);
	//}
	
	/*for (auto mab : mapBase) {
		mab->DrawMap(&camera);
	}*/

	map->Draw(&camera);

	/*PlayerÇÃï`âÊ*/
	player->Draw(&camera);
	
	/*Ç«Ç±ÇÃÉVÅ[ÉìÇ≈Ç†ÇÈÇ©*/
	SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");
}