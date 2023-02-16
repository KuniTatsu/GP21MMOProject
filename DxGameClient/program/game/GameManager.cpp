#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"Actor/Player.h"
#include"Actor/DummyPlayer.h"
#include"scene/Map.h"
#include"Actor/Enemy.h"
#include<algorithm>

#include"ChatBase.h"
#include"Connect.h"

#include<math.h>
#include"UI/UIEditor.h"
#include<random>
#include"../json11.hpp"
#include"UI/UIManager.h"
#include"Actor/ActorData.h"
#include"Actor/ActorDrawManager.h"
#include"Actor/NPC/NPCManager.h"
#include"DebugDef.h"
#include"InventoryManager.h"
#include"Item/ItemManager.h"



GameManager* GameManager::instance = nullptr;
volatile bool isEnd = false;

//-----------------------------------------------------------------------------------------
// �R���X�g���N�^
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);

}

//-----------------------------------------------------------------------------------------
// �f�X�g���N�^
GameManager::~GameManager()
{
	delete chat;
}

volatile int num1 = 0;

void GameManager::Accept()
{
#ifdef DEBUG_OFF
	while (isEnd == false)
	{
		auto get = connect->GetServerMessage();
		if (get == "")continue;
		chat->SetGetMessage(get);
	}
#endif
}

void GameManager::Send(const std::string sendMessage)
{
	//�����̃��b�Z�[�W��connect->SendServerMessage�ő���
	connect->SendClientMessage(sendMessage);

}
//���镶�͂������ɓ����BSJIS�ł���
void GameManager::CreateSendThread(const std::string sendMessage)
{

	std::thread sendThread = std::thread([&] {GameManager::Send(sendMessage); });

	//����I������X���b�h�����
	sendThread.join();

}


//-----------------------------------------------------------------------------------------
// �V���O���g���̃C���X�^���X�擾
GameManager* GameManager::GetInstance() {
	if (!instance) {
		instance = new GameManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// �j��
void GameManager::Destroy() {

	isEnd = true;
	//acceptThread->join();

	ActorDrawManager::GetInstance()->RemoveDrawActorList(player);

#ifndef DEBUG_ON

	//�T�[�o�[�ɑގ���ʒm

	connect->SendExitServer()
	acceptThread.join();
#endif

	//�V���O���g���̔j��
	UIManager::GetInstance()->Destroy();
	NPCManager::GetInstance()->Destroy();

	InitGraph();

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

void GameManager::LoadDivGraphEx(const std::string gh, const int allNum, const int widthNum, const int heightNum, int xSize, int ySize, std::vector<int>& ghVector)
{
	int* buf = new int[allNum];
	LoadDivGraph(gh.c_str(), allNum, widthNum, heightNum, xSize, ySize, buf);

	for (int i = 0; i < allNum; ++i) {
		ghVector.emplace_back(buf[i]);
	}
	delete[] buf;

}

std::shared_ptr<Player> GameManager::CreatePlayer(int ghNum)
{
	player = std::make_shared<Player>(10, 10, ghNum);
	ActorDrawManager::GetInstance()->AddDrawActorList(player);
	return player;
}

std::shared_ptr<Player> GameManager::CreatePlayerFromServer(int posX, int posY, double HP, int ghNum, std::string name)
{
	player = std::make_shared<Player>(posX, posY, HP, ghNum);
	player->SetName(name);
	ActorDrawManager::GetInstance()->AddDrawActorList(player);
	return player;
}

bool GameManager::CreateMap()
{
	int hoge = 0;
	if (Maps.empty()) {
		/*�t�@�[�X�g�}�b�v(��)*/
		auto firstMap = std::make_shared<Map>(tnl::Vector3(0, 0, 0), static_cast<uint32_t>(Map::MAPTYPE::VILLAGE));
		firstMap->test = hoge;

		hoge++;
		Maps.emplace_back(firstMap);

		std::vector<std::shared_ptr<Map>>nearMap = firstMap->GetNearMaps();
		for (int i = 0; i < 8; ++i) {
			if (nearMap[i] != nullptr)continue;

			//null�������ꍇ�̏���
			//Map��V������������
			tnl::Vector3 createMapCenter = firstMap->GetMapCenterPos() + MAPPOSOFFSET[i];
			auto newMap = std::make_shared<Map>(createMapCenter, static_cast<uint32_t>(Map::MAPTYPE::GRASS));
			newMap->test = hoge;
			hoge++;

			Maps.emplace_back(newMap);
			firstMap->SetNearMap(i, newMap);
		}
		//�e�}�b�v�̎��͂̃}�b�v��o�^����
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
	//Player��������}�b�v���擾
	std::shared_ptr<Map>nowMap = GetPlayerOnMap();

	std::vector<std::shared_ptr<Map>>nearMap = nowMap->GetNearMaps();
	for (int i = 0; i < 8; ++i) {
		if (nearMap[i] != nullptr)continue;

		//null�������ꍇ�̏���
		//Map��V������������
		tnl::Vector3 createMapCenter = nowMap->GetMapCenterPos() + MAPPOSOFFSET[i];
		auto newMap = std::make_shared<Map>(createMapCenter, static_cast<uint32_t>(Map::MAPTYPE::GRASS));
		newMap->test = hoge;
		hoge++;

		Maps.emplace_back(newMap);
		nowMap->SetNearMap(i, newMap);

		//�e�}�b�v�̎��͂̃}�b�v��o�^����
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
	//Unicode�֕ϊ���̕����񒷂𓾂�
	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);

	//�K�v�ȕ�����Unicode������̃o�b�t�@���m��
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//ShiftJIS����Unicode�֕ϊ�
	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);


	//UTF8�֕ϊ���̕����񒷂𓾂�
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//�K�v�ȕ�����UTF8������̃o�b�t�@���m��
	char* bufUTF8 = new char[lengthUTF8];

	memset(bufUTF8, 0, sizeof(char) * lengthUTF8);

	//Unicode����UTF8�֕ϊ�
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode - 1, bufUTF8, lengthUTF8, NULL, NULL);


	std::string strUTF8(bufUTF8);

	delete[] bufUnicode;
	delete[] bufUTF8;

	return strUTF8;
}

std::string GameManager::UTF8toSjis(std::string srcUTF8)
{
	//Unicode�֕ϊ���̕����񒷂𓾂�
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, NULL, 0);

	//�K�v�ȕ�����Unicode������̃o�b�t�@���m��
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//UTF8����Unicode�֕ϊ�
	MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, bufUnicode, lenghtUnicode);

	//ShiftJIS�֕ϊ���̕����񒷂𓾂�
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//�K�v�ȕ�����ShiftJIS������̃o�b�t�@���m��
	char* bufShiftJis = new char[lengthSJis];

	memset(bufShiftJis, 0, sizeof(char) * lengthSJis);

	//Unicode����ShiftJIS�֕ϊ�
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);

	std::string strSJis(bufShiftJis);

	delete[] bufUnicode;
	delete[] bufShiftJis;

	return strSJis;
}

//�Z�`���m�̓����蔻��
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
//�_���W�̃A�t�B���ϊ�
tnl::Vector3 GameManager::RotatePoint(tnl::Vector3& rotatePos, int dir, tnl::Vector3 centerPos)
{
	//��]����p�x�����߂�
	float rotateDegree = ROTATEDEGREE[dir];
	//��]�ɗp���郉�W�A���p�����߂�
	float radianX = std::cos(tnl::ToRadian(rotateDegree));
	float radianY = std::sin(tnl::ToRadian(rotateDegree));

	//���S��]�̏ꍇ�̕␳
	float xFacter = centerPos.x - (centerPos.x * radianX) + (centerPos.y * radianY);
	float yFacter = centerPos.y - (centerPos.x * radianY) - (centerPos.y * radianX);

	float testX = radianX * rotatePos.x - radianY * rotatePos.y + xFacter;
	float testY = radianY * rotatePos.x + radianX * rotatePos.y + yFacter;
	return tnl::Vector3(testX, testY, 0);
}

tnl::Vector3 GameManager::RotatePoint(tnl::Vector3& rotatePos, float degree, tnl::Vector3 centerPos)
{
	//��]�ɗp���郉�W�A���p�����߂�
	float radianX = std::cos(tnl::ToRadian(degree));
	float radianY = std::sin(tnl::ToRadian(degree));


	//���S��]�̏ꍇ�̕␳
	float xFacter = centerPos.x - (centerPos.x * radianX) + (centerPos.y * radianY);
	float yFacter = centerPos.y - (centerPos.x * radianY) - (centerPos.y * radianX);

	float testX = radianX * rotatePos.x - radianY * rotatePos.y + xFacter;
	float testY = radianY * rotatePos.x + radianX * rotatePos.y + yFacter;
	return tnl::Vector3(testX, testY, 0);
}
//�����蔻�� ��]�̂Ɠ_���W args1:�����蔻��͈͂̒��_���W4�� ����,�E��,����,�E���̏��œ���邱��,args2:���肷��_���W
bool GameManager::isHitRotateBox(std::vector<tnl::Vector3>& hitBoxPoint, tnl::Vector3& hitPoint)
{
	bool ret = true;

	//���_���W4�̃x�N�g�����쐬(�E��])
	tnl::Vector3 vec1 = { hitBoxPoint[1].x - hitBoxPoint[0].x,hitBoxPoint[1].y - hitBoxPoint[0].y,0 };
	tnl::Vector3 vec2 = { hitBoxPoint[3].x - hitBoxPoint[1].x,hitBoxPoint[3].y - hitBoxPoint[1].y,0 };
	tnl::Vector3 vec3 = { hitBoxPoint[2].x - hitBoxPoint[3].x,hitBoxPoint[2].y - hitBoxPoint[3].y,0 };
	tnl::Vector3 vec4 = { hitBoxPoint[0].x - hitBoxPoint[2].x,hitBoxPoint[0].y - hitBoxPoint[2].y,0 };

	std::vector<tnl::Vector3> boxVecs;
	boxVecs.emplace_back(vec1);
	boxVecs.emplace_back(vec2);
	boxVecs.emplace_back(vec3);
	boxVecs.emplace_back(vec4);

	//�e���_����̃x�N�g�����쐬
	tnl::Vector3 pVec1 = { hitPoint.x - hitBoxPoint[0].x,hitPoint.y - hitBoxPoint[0].y,0 };
	tnl::Vector3 pVec2 = { hitPoint.x - hitBoxPoint[1].x,hitPoint.y - hitBoxPoint[1].y,0 };
	tnl::Vector3 pVec3 = { hitPoint.x - hitBoxPoint[3].x,hitPoint.y - hitBoxPoint[3].y,0 };
	tnl::Vector3 pVec4 = { hitPoint.x - hitBoxPoint[2].x,hitPoint.y - hitBoxPoint[2].y,0 };

	std::vector<tnl::Vector3> pointVecs;
	pointVecs.emplace_back(pVec1);
	pointVecs.emplace_back(pVec2);
	pointVecs.emplace_back(pVec3);
	pointVecs.emplace_back(pVec4);

	//���_�ւ̃x�N�g���Ɠ_�ւ̃x�N�g���̊O�ς��Ƃ�
	for (int i = 0; i < 4; ++i) {
		float cross = GetCross(boxVecs[i], pointVecs[i]);
		//��ł����̐�������Γ_�͓����ɂȂ�=�������ĂȂ�
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

tnl::Vector3 GameManager::GetNearestPointLine(const tnl::Vector3& point, const tnl::Vector3& linePointA, const tnl::Vector3& linePointB) {
	tnl::Vector3 ab = linePointB - linePointA;
	tnl::Vector3 ba = linePointA - linePointB;

	tnl::Vector3 ap = point - linePointA;
	tnl::Vector3 bp = point - linePointB;


	float t = tnl::Vector3::Dot(ap, ab);
	if (t <= 0.0f) {
		return linePointA;
	}
	else {
		if (tnl::Vector3::Dot(bp, ba) < 0)return linePointB;

		////||AB||
		//auto abNorm = sqrt((linePointB.x - linePointA.x) * (linePointB.x - linePointA.x) + (linePointB.y - linePointA.y) * (linePointB.y - linePointA.y));

		//tnl::Vector3 nearPoint = linePointA + ((ab / abNorm) * (t / abNorm));

		float denom = tnl::Vector3::Dot(ab, ab);
		if (t >= denom) {
			return linePointB;
		}
		else {
			t /= denom;

			auto aaaaa = linePointA + (ab * t);;
			return linePointA + (ab * t);
		}
	}
}


//------------------------------------------------------------------------------------------------
//Map
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
	return Maps.front();
}

std::shared_ptr<Map> GameManager::GetEnemyOnMap()
{
	Maps.sort([&](std::shared_ptr<Map>map1, std::shared_ptr<Map>map2) {
		float distanceMapA = GetMaptoEnemyDistance(map1);
		float distanceMapB = GetMaptoEnemyDistance(map2);

		if (distanceMapA < distanceMapB) {
			return true;
		}
		else {
			return false;
		}
		});
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

float GameManager::GetMaptoEnemyDistance(std::shared_ptr<Map> map)
{
	for (auto enm : Enemys) {
		tnl::Vector3 enemyPos = enm->GetPos();
		tnl::Vector3 mapPos = map->GetMapCenterPos();

		float distance = std::sqrt((mapPos.x - enemyPos.x) * (mapPos.x - enemyPos.x) +
			(mapPos.y - enemyPos.y) * (mapPos.y - enemyPos.y));
		return distance;
	}

	//return 0.0f;
}

std::list<std::shared_ptr<Map>> GameManager::GetMapList()
{
	//�v���C���[�ɋ߂����Ń\�[�g
	GetPlayerOnMap();
	std::list<std::shared_ptr<Map>>nearMap;

	auto itr = Maps.begin();

	for (int i = 0; i < 9; ++i) {
		nearMap.emplace_back((*itr));
		itr++;
	}

	return nearMap;
}
//------------------------------------------------------------------------------------------------
//�v���C���[�ւ̕����x�N�g���̎擾
tnl::Vector3 GameManager::GetVectorToPlayer(tnl::Vector3& enemyPos)
{
	auto vectorToPlayer = player->GetPos() - enemyPos;

	return GetFixVector(vectorToPlayer.x, vectorToPlayer.y);
}

int GameManager::GetRandBetweenNum(int num1, int num2)
{
	auto buf = std::abs(num2 - num1);
	auto ret = GetRand(buf);

	if (num1 < num2)return ret + num1;

	return ret + num2;
}


int GameManager::GerRandomNumInWeight(const std::vector<int>& WeightList)
{
	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	//�����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���A���e�B�����肷��
	int totalWeight = 0;
	int selected = 0;

	//totalWeight�����߂�
	for (int i = 0; i < WeightList.size(); ++i) {
		totalWeight += WeightList[i];
	}
	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, totalWeight);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	//--------��������E�F�C�g��p�������I--------//
	//���I
	for (int i = 0; i < WeightList.size(); i++) {
		if (rand < WeightList[i]) {
			//����
			selected = i;
			break;
		}

		// ���̑Ώۂ𒲂ׂ�
		rand -= WeightList[i];
	}
	return selected;
}

bool GameManager::CheckRandomNumberInOdds(const float maxOdds)
{
	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	//�����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, 100);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	if (static_cast<float>(rand) <= maxOdds)return true;

	return false;
}

void GameManager::ConnectServer()
{
	connect->ConnectServer();
}

void GameManager::CreateChat()
{
	if (chat == nullptr) {
		chat = new ChatBase();

		chat->Init();
	}
}

void GameManager::CreateThread()
{
	acceptThread = std::thread([this] {GameManager::Accept(); });
}

void GameManager::GetServerEnemyInfo()
{
	//enemy���₢����
	connect->GetServerEnemyInfo();
}

bool GameManager::CreateDummyPlayer(std::string json)
{
	if (json == "")return false;

	//���b�Z�[�W����M
	//const std::string getMessage = connect->GetServerMessage();

	//�����R�[�h�ϊ�
	auto fixMessage = UTF8toSjis(json);

	std::string err;
	//Json���p�[�X
	auto pJson = json11::Json::parse(fixMessage, err);

	//�e��X�e�[�^�X�̓��ꕨ��p��
	float posX = 0.0f;
	float posY = 0.0f;
	int dir = 0;
	float HP = 0.0f;
	int ghNum = 0;
	std::string UUID = "";

	//���g����
	posX = static_cast<float>(pJson["PlayerposX"].number_value());
	posY = static_cast<float>(pJson["PlayerposY"].number_value());
	dir = pJson["dir"].int_value();
	HP = static_cast<float>(pJson["HP"].number_value());

	ghNum = pJson["gh"].int_value();
	UUID = pJson["UUID"].string_value();

	//���łɑ��݂��Ȃ����`�F�b�N
	if (CheckIsThereInUUID(UUID))return false;

	auto dummy = std::make_shared<DummyPlayer>(posX, posY, UUID, dir, HP, ghNum);

	//Dummy�v���C���[��������
	if (dummy != nullptr) {
		otherPlayers.emplace_back(dummy);

		ActorDrawManager::GetInstance()->AddDrawActorList(dummy);
		return true;
	}
	//Dummy�v���C���[�������s
	return false;
}
bool GameManager::CreateDummyPlayer(float posX, float posY, std::string UUID, int dir, float HP, int ghNum)
{
	//���łɑ��݂��Ȃ����`�F�b�N
	if (CheckIsThereInUUID(UUID))return false;

	auto dummy = std::make_shared<DummyPlayer>(posX, posY, UUID, dir, HP, ghNum);

	//Dummy�v���C���[��������
	if (dummy != nullptr) {
		otherPlayers.emplace_back(dummy);

		ActorDrawManager::GetInstance()->AddDrawActorList(dummy);
		return true;
	}
	//Dummy�v���C���[�������s
	return false;
}
//bool GameManager::CreateDummyPlayer(json11::Json::object obj)
//{
//	//auto hogehoge = test["UUID"].string_value();
//
//
//	return false;
//}
bool GameManager::CheckIsThereInUUID(std::string UUID)
{
	bool ret = false;
	for (auto& other : otherPlayers) {

		auto bufUUID = other->GetUUID();
		if (UUID == bufUUID) {
			ret = true;
			break;
		}
	}
	return ret;
}
void GameManager::MoveDummyInUUID(float x, float y, int dir, std::string UUID)
{
	for (auto& other : otherPlayers) {

		auto bufUUID = other->GetUUID();
		if (UUID == bufUUID) {
			other->UpdatePosition(x, y, dir);
			break;
		}
	}
}
void GameManager::UpdateDummyHP(std::string UUID, float moveHP)
{
	for (auto& other : otherPlayers) {

		auto bufUUID = other->GetUUID();
		if (UUID == bufUUID) {
			auto data = other->GetActorData();
			data->UpdateHp(moveHP);
			break;
		}
	}
}
void GameManager::SendPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	connect->SendClientPlayerAttribute(STR, VIT, INT, MID, SPD, DEX);
}
void GameManager::SetPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	player->SetAttributeFromServer(STR, VIT, INT, MID, SPD, DEX);

}
void GameManager::GetPlayerAttribute()
{
	connect->GetClientCharactorAttribute();
}
void GameManager::GetPlayerInfo(std::string UUID)
{
	connect->GetClientCharactorInfo(UUID);
}
void GameManager::EntryServer()
{
	if (playerName == "")return;
	connect->EntryServer(playerName);
}
void GameManager::GetMyUUID()
{
	connect->GetEntryUserId();
}
//���v���C���[�̃��X�g����̍폜
void GameManager::PopOtherPlayerInUUID(std::string UUID)
{
	auto itr = otherPlayers.begin();
	for (auto& other : otherPlayers) {

		auto thisUUID = other->GetUUID();
		if (UUID == thisUUID) {
			//�_�~�[���X�g����폜
			otherPlayers.erase(itr);
			//�`�悷��A�N�^�[���X�g����폜
			ActorDrawManager::GetInstance()->RemoveDrawActorList((*itr));
		}
		itr++;
	}
}

bool GameManager::isClickedRect(int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	bool ret = false;
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (mousePosX<RectLeft || mousePosX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	//�l�p�`�̓��������N���b�N���Ă�����
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		ret = true;
	}
	return ret;
}


bool GameManager::isClickedRect(tnl::Vector3& CenterPos, int halfSize)
{
	int left = CenterPos.x - halfSize;
	int top = CenterPos.y - halfSize;
	int right = CenterPos.x + halfSize;
	int bottom = CenterPos.y + halfSize;
	return isClickedRect(left, top, right, bottom);
}
#ifndef DEBUG_ON

void GameManager::SendPlayerInfoToServer(bool isReLogin)
{

	const auto& pos = player->GetPos();
	auto dir = player->GetDir();

	auto& data = player->GetActorData();

	auto type = player->GetActorType();

	if (player->GetIsCreatedDummy()) {
		//���Ƀ_�~�[������Ă���Ȃ�_�~�[�̏��X�V�̂��߂̒ʐM�Ȃ̂ň�����1�ɂ���:Player�̈ړ����炱���ɗ����Ƃ��̏���
		connect->SendClientPlayerInfo(pos.x, pos.y, dir, data->GetHP(), 1);
	}
	else {
		//���̃v���C���[��Dummy����邽�߂̏���
		connect->SendClientPlayerInfo(pos.x, pos.y, dir, data->GetHP());

		//�ă��O�C�����Ȃ�f�[�^�x�[�X�ւ̓o�^�͍s��Ȃ�
		if (isReLogin) {
			//�����ȊO�̃v���C���[�����񂹂�
			connect->GetServerOtherUser();
			return;
		}
		//�����O�C�����̃f�[�^�x�[�X�o�^����
		connect->SendClientPlayerInitInfo(pos.x, pos.y, data->GetHP(), type);
	}

}
#endif

void GameManager::GetServerOtherUser()
{
	connect->GetServerOtherUser();
}


void GameManager::SendInitEnemyInfoToServer(float x, float y, int dir, int identNum, int type)
{
#ifdef DEBUG_OFF
	connect->SendClientEnemyInitInfo(x, y, dir, identNum, type);
#endif
}



void GameManager::SendEnemyInfoToServer(float x, float y, int dir, int identNum, int type)
{
#ifdef DEBUG_OFF
	connect->SendClientEnemyInfo(x, y, dir, identNum, type);
#endif
}


void GameManager::SendEnemyMoveHPInfoToServer(int identNum, float moveHP, bool isPlus)
{
#ifdef DEBUG_OFF
	//HP������������
	if (!isPlus) {
		float decreaseHP = moveHP * -1;
		connect->SendClientEnemyStatus(identNum, decreaseHP);
		return;
	}
	connect->SendClientEnemyStatus(identNum, moveHP);
#endif
}


bool GameManager::OnMouseRect(int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (mousePosX<RectLeft || mousePosX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	return true;
}

tnl::Vector3 GameManager::GetMousePos()
{
	GetMousePoint(&mousePosX, &mousePosY);
	return tnl::Vector3(mousePosX, mousePosY, 0);
}

void GameManager::UpdatePlayerHP(double moveHp)
{
	auto& data = player->GetActorData();

	data->UpdateHp(moveHp);
}

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {


	if (!init) {
		sManager = SceneManager::GetInstance();
		ItemManager::GetInstance()->Init();
		InventoryManager::GetInstance()->Init();
		//connect = std::make_shared<Connect>();
#ifndef DEBUG_ON
		connect = std::make_shared<Connect>();
#endif
		uiEditor = std::make_shared<UIEditor>();

		uiEditor->Init();

		init = true;
	}

	GetMousePoint(&mousePosX, &mousePosY);


	deltaTime = delta_time;

	sManager->Update(delta_time);
	sManager->Draw();

#ifndef DEBUG_ON
	if (chat) {
		chat->Update();
		chat->Draw();
	}
#endif



	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
		uiEditor->ChangeEnable();
	}

	uiEditor->Update();
	uiEditor->Draw();


}










