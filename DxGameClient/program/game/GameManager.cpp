#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"Actor/Player.h"
#include"scene/Map.h"
#include<algorithm>
#include"ChatBase.h"


GameManager* GameManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
}

//-----------------------------------------------------------------------------------------
// デストラクタ
GameManager::~GameManager()
{
	delete chat;
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
	int hoge = 0;
	if (Maps.empty()) {
		auto firstMap = std::make_shared<Map>(tnl::Vector3(0, 0, 0));
		firstMap->test = hoge;
		hoge++;
		Maps.emplace_back(firstMap);

		std::vector<std::shared_ptr<Map>>nearMap = firstMap->GetNearMaps();
		for (int i = 0; i < 8; ++i) {
			if (nearMap[i] != nullptr)continue;

			//nullだった場合の処理
			//Mapを新しく生成する
			tnl::Vector3 createMapCenter = firstMap->GetMapCenterPos() + MAPPOSOFFSET[i];
			auto newMap = std::make_shared<Map>(createMapCenter);
			newMap->test = hoge;
			hoge++;

			Maps.emplace_back(newMap);
			firstMap->SetNearMap(i, newMap);
		}
		//各マップの周囲のマップを登録する
		for (auto map : Maps) {
			auto nearMap = map->GetNearMaps();
			for (int i = 0; i < 8; ++i) {
				
				if (nearMap[i] == nullptr) {
					tnl::Vector3 mapCenter = map->GetMapCenterPos() + MAPPOSOFFSET[i];

					auto selectMap = GetMapOnPoint(mapCenter);
					if (selectMap != nullptr) {
						map->SetNearMap(i, selectMap);
					}
				}
			}
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
		newMap->test = hoge;
		hoge++;

		Maps.emplace_back(newMap);
		nowMap->SetNearMap(i, newMap);

		//各マップの周囲のマップを登録する
		for (auto map : Maps) {
			auto nearMap = map->GetNearMaps();
			for (int i = 0; i < 8; ++i) {

				if (nearMap[i] == nullptr) {
					tnl::Vector3 mapCenter = map->GetMapCenterPos() + MAPPOSOFFSET[i];

					auto selectMap = GetMapOnPoint(mapCenter);
					if (selectMap != nullptr) {
						map->SetNearMap(i, selectMap);
					}
				}
			}
		}
		
		isSuccess = true;
	}
	return isSuccess;
}

bool GameManager::IsOnMap()
{
	return false;
}

void GameManager::SetStayMap()
{
	lastStayMap = GetPlayerOnMap();
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

std::shared_ptr<Map> GameManager::GetMapOnPoint(tnl::Vector3& Point)
{
	for (auto map : Maps) {

		auto leftTop = map->GetMapLeftTopPos();
		auto rightBottom = map->GetMapRightBottomPos();

		if (Point.x<leftTop.x || Point.x>rightBottom.x || Point.y<leftTop.y || Point.y>rightBottom.y)continue;
		return map;
	}
	return nullptr;
}

bool GameManager::IsOverChunk()
{
	auto stayMap = GetPlayerOnMap();
	if (stayMap == lastStayMap)return false;
	return true;
}

float GameManager::GetMapToPlayerDistance(std::shared_ptr<Map> map)
{
	tnl::Vector3 playerPos = player->GetPos();
	tnl::Vector3 mapPos = map->GetMapCenterPos();

	float distance = std::sqrt((mapPos.x - playerPos.x) * (mapPos.x - playerPos.x) +
		(mapPos.y - playerPos.y) * (mapPos.y - playerPos.y));

	return distance;
}

std::list<std::shared_ptr<Map>> GameManager::GetMapList()
{
	//プレイヤーに近い順でソート
	GetPlayerOnMap();
	std::list<std::shared_ptr<Map>>nearMap;

	auto itr = Maps.begin();

	for (int i = 0; i < 9; ++i) {
		nearMap.emplace_back((*itr));
		itr++;
	}

	return nearMap;
}



//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {


	if (!init) {
		sManager = SceneManager::GetInstance();
		init = true;
	}
if (chat == nullptr) {
	chat = new ChatBase();
}


deltaTime = delta_time;

	sManager->Update(delta_time);
	sManager->Draw();

	chat->Update();
	chat->Draw();

}










