#include "scene_play.h"
#include"../GameManager.h"

void Scene_Play::initialzie()
{

}

void Scene_Play::update(float delta_time)
{

}

void Scene_Play::render()
{
	DrawStringEx(50, 50, -1, "Scene_Play");
}

void Scene_Play::mapChip()
{
	std::vector<std::vector<std::string>>map_csv;
	//map_csv = tnl::LoadCsv
}
