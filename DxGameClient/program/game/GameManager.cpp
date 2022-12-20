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
#include<random>
#include"../json11.hpp"


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
	while (isEnd == false)
	{

		auto get = connect->GetServerMessage();
		if (get == "")continue;
		chat->SetGetMessage(get);

	}
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
	acceptThread.join();

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

std::shared_ptr<Player> GameManager::CreatePlayer()
{
	player = std::make_shared<Player>(10, 10);
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

			//null�������ꍇ�̏���
			//Map��V������������
			tnl::Vector3 createMapCenter = firstMap->GetMapCenterPos() + MAPPOSOFFSET[i];
			auto newMap = std::make_shared<Map>(createMapCenter);
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
		auto newMap = std::make_shared<Map>(createMapCenter);
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

tnl::Vector3 GameManager::RotatePoint(tnl::Vector3& centerPos, tnl::Vector3& rotatePos)
{
	/*
	//����]
	float fixX = vec.x * radianX - vec.y * radianY;
	float fixY = vec.x * radianY + vec.y * radianX;

	//�E��]
	float fixX = vec.x * radianX + vec.y * radianY;
	float fixY = vec.x * radianY*(-1) + vec.y * radianX;
	*/

	return tnl::Vector3();
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


int GameManager::GerRandomNumInWeight(const std::vector<int> WeightList)
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
	float posX = 0;
	float posY = 0;
	int ghNum = 0;
	std::string UUID = "";

	//���g����
	posX = static_cast<float>(pJson["PlayerposX"].number_value());
	posY = static_cast<float>(pJson["PlayerposY"].number_value());

	ghNum = pJson["Playergh"].int_value();
	UUID = pJson["PlayerUUID"].string_value();

	//���łɑ��݂��Ȃ����`�F�b�N
	if (CheckIsThereInUUID(UUID))return false;

	auto dummy = std::make_shared<DummyPlayer>(posX, posY, UUID, ghNum);
	//Dummy�v���C���[��������
	if (dummy != nullptr) {
		otherPlayers.emplace_back(dummy);
		return true;
	}
	//Dummy�v���C���[�������s
	return false;
}
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
void GameManager::MoveDummyInUUID(float x, float y, std::string UUID)
{
	for (auto& other : otherPlayers) {

		auto bufUUID = other->GetUUID();
		if (UUID == bufUUID) {
			other->UpdatePosition(x, y);
			break;
		}
	}

}
//���v���C���[�̃��X�g����̍폜
void GameManager::PopOtherPlayerInUUID(std::string UUID)
{
	auto itr = otherPlayers.begin();
	for (auto& other : otherPlayers) {

		auto thisUUID = other->GetUUID();
		if (UUID == thisUUID) {
			otherPlayers.erase(itr);
		}
		itr++;
	}
}

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {


	if (!init) {
		sManager = SceneManager::GetInstance();

		connect = std::make_shared<Connect>();

		if (chat == nullptr) {
			chat = new ChatBase();
		}

		acceptThread = std::thread([this] {GameManager::Accept(); });


		//���̃v���C���[��Dummy����邽�߂̏���
		const auto& pos = player->GetPos();
		connect->SendClientPlayerInfo(pos.x, pos.y);


		//test�pDummy����
		connect->SendClientPlayerInfo(100, 100,0,1);

		init = true;
	}

	/*tnl::DebugTrace("%d", num1);
	tnl::DebugTrace("\n");*/

	/*if (chat == nullptr) {
		chat = new ChatBase();
	}*/

	deltaTime = delta_time;

	sManager->Update(delta_time);
	sManager->Draw();

	chat->Update();
	chat->Draw();


}










