#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"Actor/Player.h"
#include"scene/Map.h"
#include<algorithm>
#include"ChatBase.h"
#include<math.h>


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

std::string GameManager::SjistoUTF8(std::string srcSjis)
{
	//Unicodeへ変換後の文字列長を得る
	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//ShiftJISからUnicodeへ変換
	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);


	//UTF8へ変換後の文字列長を得る
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけUTF8文字列のバッファを確保
	char* bufUTF8 = new char[lengthUTF8];

	memset(bufUTF8, 0, sizeof(char) * lengthUTF8);

	//UnicodeからUTF8へ変換
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode - 1, bufUTF8, lengthUTF8, NULL, NULL);


	std::string strUTF8(bufUTF8);

	delete[] bufUnicode;
	delete[] bufUTF8;

	return strUTF8;
}

std::string GameManager::UTF8toSjis(std::string srcUTF8)
{
	//Unicodeへ変換後の文字列長を得る
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//UTF8からUnicodeへ変換
	MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, bufUnicode, lenghtUnicode);

	//ShiftJISへ変換後の文字列長を得る
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけShiftJIS文字列のバッファを確保
	char* bufShiftJis = new char[lengthSJis];

	memset(bufShiftJis, 0, sizeof(char) * lengthSJis);

	//UnicodeからShiftJISへ変換
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);

	std::string strSJis(bufShiftJis);

	delete[] bufUnicode;
	delete[] bufShiftJis;

	return strSJis;
}

//短形同士の当たり判定
bool GameManager::isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2)
{
	float entity1Left = leftTop1.x;
	float entity1Top = leftTop1.y;
	float entity1Right = rightBottom1.x;
	float entity1Bottom = rightBottom1.y;

	float entity2Left = leftTop2.x;
	float entity2Top = leftTop2.y;
	float entity2Right = rightBottom2.x;
	float entity2Bottom = rightBottom2.y;

	if (entity1Right < entity2Left)return false;
	if (entity1Left > entity2Right) return false;
	if (entity1Top > entity2Bottom) return false;
	if (entity1Bottom < entity2Top) return false;

	return true;
}
//点座標のアフィン変換
tnl::Vector3 GameManager::RotatePoint(tnl::Vector3& rotatePos, int dir, tnl::Vector3 centerPos)
{
	//回転する角度を求める
	float rotateDegree = ROTATEDEGREE[dir];
	//回転に用いるラジアン角を求める
	float radianX = std::cos(tnl::ToRadian(rotateDegree));
	float radianY = std::sin(tnl::ToRadian(rotateDegree));

	//中心回転の場合の補正
	float xFacter = centerPos.x - (centerPos.x * radianX) + (centerPos.y * radianY);
	float yFacter = centerPos.y - (centerPos.x * radianY) - (centerPos.y * radianX);

	float testX = radianX * rotatePos.x - radianY * rotatePos.y + xFacter;
	float testY = radianY * rotatePos.x + radianX * rotatePos.y + yFacter;
	return tnl::Vector3(testX, testY, 0);
}

tnl::Vector3 GameManager::RotatePoint(tnl::Vector3& rotatePos, float degree, tnl::Vector3 centerPos)
{
	//回転に用いるラジアン角を求める
	float radianX = std::cos(tnl::ToRadian(degree));
	float radianY = std::sin(tnl::ToRadian(degree));

	//中心回転の場合の補正
	float xFacter = centerPos.x - (centerPos.x * radianX) + (centerPos.y * radianY);
	float yFacter = centerPos.y - (centerPos.x * radianY) - (centerPos.y * radianX);

	float testX = radianX * rotatePos.x - radianY * rotatePos.y + xFacter;
	float testY = radianY * rotatePos.x + radianX * rotatePos.y + yFacter;
	return tnl::Vector3(testX, testY, 0);
}
//当たり判定 回転体と点座標 args1:当たり判定範囲の頂点座標4つ 左上,右上,左下,右下の順で入れること,args2:判定する点座標
bool GameManager::isHitRotateBox(std::vector<tnl::Vector3>& hitBoxPoint, tnl::Vector3& hitPoint)
{
	bool ret = true;

	//頂点座標4つのベクトルを作成(右回転)
	tnl::Vector3 vec1 = { hitBoxPoint[1].x - hitBoxPoint[0].x,hitBoxPoint[1].y - hitBoxPoint[0].y,0 };
	tnl::Vector3 vec2 = { hitBoxPoint[3].x - hitBoxPoint[1].x,hitBoxPoint[3].y - hitBoxPoint[1].y,0 };
	tnl::Vector3 vec3 = { hitBoxPoint[2].x - hitBoxPoint[3].x,hitBoxPoint[2].y - hitBoxPoint[3].y,0 };
	tnl::Vector3 vec4 = { hitBoxPoint[0].x - hitBoxPoint[2].x,hitBoxPoint[0].y - hitBoxPoint[2].y,0 };

	std::vector<tnl::Vector3> boxVecs;
	boxVecs.emplace_back(vec1);
	boxVecs.emplace_back(vec2);
	boxVecs.emplace_back(vec3);
	boxVecs.emplace_back(vec4);

	//各張点からのベクトルを作成
	tnl::Vector3 pVec1 = { hitPoint.x - hitBoxPoint[0].x,hitPoint.y - hitBoxPoint[0].y,0 };
	tnl::Vector3 pVec2 = { hitPoint.x - hitBoxPoint[1].x,hitPoint.y - hitBoxPoint[1].y,0 };
	tnl::Vector3 pVec3 = { hitPoint.x - hitBoxPoint[3].x,hitPoint.y - hitBoxPoint[3].y,0 };
	tnl::Vector3 pVec4 = { hitPoint.x - hitBoxPoint[2].x,hitPoint.y - hitBoxPoint[2].y,0 };

	std::vector<tnl::Vector3> pointVecs;
	pointVecs.emplace_back(pVec1);
	pointVecs.emplace_back(pVec2);
	pointVecs.emplace_back(pVec3);
	pointVecs.emplace_back(pVec4);

	//頂点へのベクトルと点へのベクトルの外積をとる
	for (int i = 0; i < 4; ++i) {
		float cross = GetCross(boxVecs[i], pointVecs[i]);
		//一つでも負の数があれば点は内部にない=当たってない
		if (cross < 0) {
			ret = false;
			break;
		}
	}
	return ret;
}

tnl::Vector3 GameManager::GetCenterVector(tnl::Vector3& firstPos, tnl::Vector3& secondPos)
{
	return ((firstPos + secondPos) / 2);
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
	/*if (chat == nullptr) {
		chat = new ChatBase();
	}*/


	deltaTime = delta_time;

	sManager->Update(delta_time);
	sManager->Draw();

	/*chat->Update();
	chat->Draw();*/

}










