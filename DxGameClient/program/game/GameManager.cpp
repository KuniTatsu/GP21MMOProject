#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"
#include"Actor/Player.h"
#include"scene/Map.h"
#include"Actor/Enemy.h"
#include<algorithm>
#include"ChatBase.h"
#include"Connect.h"



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
		chat->SetGetMessage(get);
		/*num1++;

		tnl::DebugTrace("�Ă΂ꂽ��%d���", num1);
		tnl::DebugTrace("\n");
		std::string hoge = std::to_string(isEnd);
		tnl::DebugTrace(hoge.c_str());
		tnl::DebugTrace("\n");

		if (num1 > 10000)num1 = 0;*/
	}
	/*tnl::DebugTrace("��������");
	int hoge = 0;
	hoge++;*/
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

//int GameManager::ContSpawn(int count, FUNCCOUNT f)
//{
//
//	return f(count);
//}

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


bool GameManager::CheckCanCreateEnemy(tnl::Vector3& Pos) {

	bool canSpawn = true;
	//�����̓G�̃|�W�V�����Ƃ��Ԃ��Ă��Ȃ����`�F�b�N
	for (auto& enemy : Enemys) {
		auto listEnemyPos = enemy->GetPos();
		if (GetLength(Pos, listEnemyPos) < 32) {
			canSpawn = false;
			break;
		}
	}
	return canSpawn;
	////���Ԃ��Ă����琶�����Ȃ�
	//if (!canSpawn)return;

	//auto enemy = std::make_shared<Enemy>(Pos);
	//Enemys.emplace_back(enemy);
}

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {


	if (!init) {
		sManager = SceneManager::GetInstance();
		//connect = std::make_shared<Connect>();

		/*if (chat == nullptr) {
			chat = new ChatBase();
		}*/
		//�`���b�g�󂯎��p�X���b�h�쐬
		//std::thread hoge(&GameManager::Accept, &instance);
		//acceptThread = std::thread(& GameManager::Accept, & instance);

		//std::thread hoge(&GameManager::Accept,this);


		//std::thread hoge([this] {GameManager::Accept(); });
		//acceptThread = std::move(hoge);
		//acceptThread = std::thread([this] {GameManager::Accept(); });

		//auto id = acceptThread.get_id();

		// std::thread t([this] { do_(); });
		// thread_ = std::move(t);

		init = true;
	}

	tnl::DebugTrace("%d", num1);
	tnl::DebugTrace("\n");

	/*if (chat == nullptr) {
		chat = new ChatBase();
	}*/

	deltaTime = delta_time;

	sManager->Update(delta_time);
	sManager->Draw();

	/*chat->Update();
	chat->Draw();*/

}










