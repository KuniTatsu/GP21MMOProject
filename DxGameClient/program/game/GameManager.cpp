#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"Actor/Player.h"
#include"scene/Map.h"
#include<algorithm>

GameManager* GameManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
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

int GameManager::LoadGraphEx(std::string Gh)
{
	auto it = ghmap.find(Gh);
	if (it != ghmap.end()) {
		return ghmap[Gh];
	}

	else {
		int loadgh = LoadGraph(Gh.c_str());
		ghmap.insert(std::make_pair(Gh, loadgh));
	}
	return ghmap[Gh];
}

std::shared_ptr<Player> GameManager::CreatePlayer()
{
	player = std::make_shared<Player>(0, 0);
	return player;
}

bool GameManager::CreateMap()
{
	if (Maps.empty()) {
		auto newMap = std::make_shared<Map>(tnl::Vector3(0,0,0));
		Maps.emplace_back(newMap);

		std::vector<std::shared_ptr<Map>>nearMap = newMap->GetNearMaps();
		for (int i = 0; i < 8; ++i) {
			if (nearMap[i] != nullptr)continue;

			//nullだった場合の処理
			//Mapを新しく生成する
			tnl::Vector3 createMapCenter = newMap->GetMapCenterPos() + MAPPOSOFFSET[i];
			auto newMap = std::make_shared<Map>(createMapCenter);

			Maps.emplace_back(newMap);
			nearMap[i] = newMap;
		}
		return true;
	}

	bool isSuccess = false;
	//Playerが今いるマップを取得
	std::shared_ptr<Map>nowMap = GetPlayerOnMap();

	std::vector<std::shared_ptr<Map>>nearMap = nowMap->GetNearMaps();
	for (int i = 0; i < 8; ++i) {
		if (nearMap[i] != nullptr)continue;

		//nullだった場合の処理
		//Mapを新しく生成する
		tnl::Vector3 createMapCenter = nowMap->GetMapCenterPos() + MAPPOSOFFSET[i];
		auto newMap = std::make_shared<Map>(createMapCenter);

		Maps.emplace_back(newMap);
		nearMap[i] = newMap;
		isSuccess = true;
	}
	return isSuccess;
}

bool GameManager::IsOnMap()
{
	return false;
}

std::shared_ptr<Map> GameManager::GetPlayerOnMap()
{
	Maps.sort([&](std::shared_ptr<Map> map1, std::shared_ptr<Map> map2) {
		float distanceMapA = GetMapToPlayerDistance(map1);
		float distanceMapB = GetMapToPlayerDistance(map2);

		if (distanceMapA < distanceMapB) {
			return true;
		}
		else {
			return false;
		}
		});
	//std::sort(Maps.begin(), Maps.end(), []( auto const& mapA,auto const& mapB) {

	//	return mapA->test < mapB->test;
	//	/*float distanceMapA = GetMapToPlayerDistance(mapA);
	//	float distanceMapB = GetMapToPlayerDistance(mapB);

	//	if (distanceMapA < distanceMapB) {
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}*/

	//	});
	return Maps.front();
}

float GameManager::GetMapToPlayerDistance(std::shared_ptr<Map> map)
{
	tnl::Vector3 playerPos = player->GetPos();
	tnl::Vector3 mapPos = map->GetMapCenterPos();

	float distance = std::sqrt((mapPos.x - playerPos.x) * (mapPos.x - playerPos.x) +
		(mapPos.y - playerPos.y) * (mapPos.y - playerPos.y));

	return distance;
}



//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {

	if (!init) {
		sManager = SceneManager::GetInstance();
		init = true;
	}

	sManager->Update(delta_time);
	sManager->Draw();
}










