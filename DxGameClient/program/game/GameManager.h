#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>
#include<memory>
#include<list>
#include<thread>

class SceneBase;
class SceneManager;
class ChatBase;
class Map;
class Enemy;
class Player;
class Connect;
class DummyPlayer;
class UIEditor;

class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::shared_ptr<Connect> connect = nullptr;

	std::thread acceptThread;

	//�}���`�X���b�h�œ�������M�p�֐�
	void Accept();

	//�}���`�X���b�h�œ��������M�p�֐�
	void Send(const std::string sendMessage);


	ChatBase* chat = nullptr;
	//UIEditor* editor = nullptr;
	std::shared_ptr<UIEditor> uiEditor = nullptr;

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;
	//�e�`�����N�̃}�b�v�|�C���^�����z��
	std::list<std::shared_ptr<Map>>Maps;

	//player������}�b�v�̃|�C���^
	std::shared_ptr<Map>lastStayMap = nullptr;

	std::list<std::shared_ptr<Enemy>> Enemys;
	std::list<std::shared_ptr<DummyPlayer>>otherPlayers;

	std::string clientUUID = "";

	std::string playerName = "";


	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��
public:
	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	//��`�����N�̈�ӂ̃`�b�v��
	const int MAPSIZE = 35;
	//��`�b�v�̑傫��
	const int CHIPWIDTH = 32;
	const int CHIPHEIGHT = 32;

	float deltaTime = 0.0f;

	const tnl::Vector3 MAPPOSOFFSET[8] = {
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//����
		tnl::Vector3(0,-MAPSIZE * CHIPHEIGHT,0),//��
		tnl::Vector3(MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//�E��
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,0,0),//��
		tnl::Vector3(MAPSIZE * CHIPWIDTH,0,0),//�E
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0),//����
		tnl::Vector3(0,MAPSIZE * CHIPHEIGHT,0),//��
		tnl::Vector3(MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0)//�E�� 

	};
	//��]�p�̕���
	enum class ROTATEDIR :uint32_t {
		LEFTTOP,
		LEFT,
		LEFTBOTTOM,
		BOTTOM,
		RIGHTBOTTOM,
		RIGHT,
		RIGHTTOP,
		TOP,
		MAX
	};

	//���W��]���Ɏg�p�����]�p�̔z��(�p�x) �������0�x�Ƃ���B(����+90�x�Ƃ���)
	const float ROTATEDEGREE[static_cast<uint32_t>(ROTATEDIR::MAX)] = {
		-45.0f,//����
		-90.0f,//��
		-135.0f,//����
		-180.0f,//��
		-225.0f,//�E��
		-270.0f,//�E
		-315.0f,//�E��
		-360.0f//��
	};
	//�}�E�X���W
	int mousePosX = 0;
	int mousePosY = 0;

	//UI����ׂ����
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};


public:
	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);
	// �j��
	void Destroy();

	inline void SetPlayerName(std::string name) {
		playerName = name;
	}
	inline std::string GetPlayerName() {
		return playerName;
	}

	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {
		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);
	}


	//�O�ς��擾����֐�
	float GetCross(tnl::Vector3& vec1, tnl::Vector3& vec2) {
		return vec1.x * vec2.y - vec2.x * vec1.y;
	}

	//2�̍��W�Ԃ̋��������߂�֐�
	inline float GetLengthFromTwoPoint(tnl::Vector3& pos1, tnl::Vector3& pos2) {
		tnl::Vector3 vec = pos2 - pos1;
		return vec.length();
	}

	//4�_�̒����̍��W�����߂�֐�
	inline tnl::Vector3 GetCenterPosRect(std::vector<tnl::Vector3>& rectPos) {

		auto x = rectPos[1].x - rectPos[0].x;
		auto y = rectPos[3].y - rectPos[0].y;
		return tnl::Vector3(x, y, 0);
	}

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//�������̘A�Ȃ����摜��vector�Ɋi�[����֐�
	void LoadDivGraphEx(const std::string pass, const int allNum, const int widthNum, const int heightNum,
		int xSize, int ySize, std::vector<int>& ghVector);

	//string�^�̕����R�[�h�ϊ�
	std::string SjistoUTF8(std::string srcSjis);
	std::string UTF8toSjis(std::string srcUTF8);

	//�����蔻�� �Z�`���m
	bool isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2);
	//���W�̉�]	args:��]�����������W,�����Ă������(ROTATEDIR�ɏ�����),���S���W(�f�t�H���g�ł͌��_)
	tnl::Vector3 RotatePoint(tnl::Vector3& rotatePos, int dir, tnl::Vector3 centerPos = { 0,0,0 });
	tnl::Vector3 RotatePoint(tnl::Vector3& rotatePos, float degree, tnl::Vector3 centerPos = { 0,0,0 });

	//�����蔻�� ��]�̂Ɠ_���W args1:�����蔻��͈͂̒��_���W4�� ����,�E��,����,�E���̏��œ���邱��,args2:���肷��_���W
	bool isHitRotateBox(std::vector<tnl::Vector3>& hitBoxPoint, tnl::Vector3& hitPoint);


	//2�̍��W���璆�S���W�����߂�֐� args1:���W1,args2:���W2
	tnl::Vector3 GetCenterVector(tnl::Vector3& firstPos, tnl::Vector3& secondPos);

	//�_����������̍ŋߓ_�����߂�֐�
	tnl::Vector3 GetNearestPointLine(const tnl::Vector3& point, const tnl::Vector3& linePointA, const tnl::Vector3& linePointB);

	//Player(���̃N���C�A���g��)����
	std::shared_ptr<Player> CreatePlayer();

	//�ă��O�C�����̃v���C���[����
	std::shared_ptr<Player>CreatePlayerFromServer(int posX, int posY, double HP, int ghNum);

	inline std::shared_ptr<Player>& GetPlayer() {
		return player;
	}

	//Map�V�K����
	bool CreateMap();

	//���̃}�b�v�ɂ��̃N���C�A���g��Player�����邩�ǂ���
	bool IsOnMap();

	//Player�̂���}�b�v�̓o�^
	void SetStayMap();
	//Player(���̃N���C�A���g��)������}�b�v�|�C���^���擾����֐�
	std::shared_ptr<Map>GetPlayerOnMap();

	//�w����W����}�b�v���擾����֐�
	std::shared_ptr<Map>GetMapOnPoint(tnl::Vector3& Point);

	//Player���z���������ǂ����m���߂�֐�
	bool IsOverChunk();

	//Map�|�C���^�̒��S���W����Player�̒��S���W�ւ̋��������߂�֐�
	float GetMapToPlayerDistance(std::shared_ptr<Map> map);

	//�`�����N���S����`�����N���S�ւ̋��������߂�֐�
	inline float GetChunkDistance() {
		return static_cast<float>(MAPSIZE * CHIPHEIGHT);
	}

	//���Pos���m�̋������擾����֐�
	inline float GetLength(tnl::Vector3& PosA, tnl::Vector3& PosB) {
		return std::sqrt(((PosA.x - PosB.x) * (PosA.x - PosB.x)) + ((PosA.y - PosB.y) * (PosA.y - PosB.y)));
	}

	//�}�b�v���X�g�̎擾
	std::list<std::shared_ptr<Map>> GetMapList();

	//�G�l�~�[���X�g�̎擾
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return Enemys;
	}

	//���M�p�X���b�h���쐬����֐�
	void CreateSendThread(const std::string sendMessage);

	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		Enemys.emplace_back(enemy);
	}
	tnl::Vector3 GetVectorToPlayer(tnl::Vector3& enemyPos);

	//�����Z���k�E�c�C�X�^�[���̗p�������K���z�����_���֐�(�E�F�C�g���l��)
	int GerRandomNumInWeight(const std::vector<int>& WeightList);
	//�����Z���k�E�c�C�X�^�[���̗p�������K���z�����_���֐�(1~100)
	bool CheckRandomNumberInOdds(const float maxOdds);


	//tnl::Vector3 GetVectorToPlayer(tnl::Vector3& enemyPos);

	//��̐����̊Ԃ̃����_���Ȑ���Ԃ��֐�
	int GetRandBetweenNum(int num1, int num2);

	//���̃N���C�A���g��UUID��o�^����֐�
	inline void SetClientUUID(std::string UUID) {
		clientUUID = UUID;
	}
	//���̃N���C�A���g��UUID���擾����֐�
	inline std::string GetClientUUID() {
		return clientUUID;
	}
	//connect�擾
	inline std::shared_ptr<Connect>GetConnection() {
		if (connect)return connect;
		return nullptr;
	}

	//�T�[�o�[�ɐڑ�����֐�
	void ConnectServer();

	//�`���b�g�쐬
	void CreateChat();

	//�X���b�h�쐬
	void CreateThread();

	//�G�l�~�[�̏����擾����֐�
	void GetServerEnemyInfo();

	//�T�[�o�[���瑗���Ă������̃v���C���[�̏�񂩂�DummyPlayer�𐶐����o�^����֐�
	bool CreateDummyPlayer(std::string json);

	bool CreateDummyPlayer(float posX, float posY, std::string UUID, int dir, float HP, int ghNum);

	//�v���C���[�̏����T�[�o�[�ɑ���֐�
	void SendPlayerInfoToServer();

	//enemy���������ꂽ���ɃT�[�o�[�ɓo�^����֐�
	void SendInitEnemyInfoToServer(float x, float y, int dir, int identNum, int type = -1);

	//enemy�̏����T�[�o�[�ɑ���֐� args1:x���W args2:y���WHP args3:���p(8����) args4:���ʔԍ� args5:�G�̃^�C�v
	void SendEnemyInfoToServer(float x, float y, int dir, int identNum, int type = -1);
	//enemy��HP�ϓ����T�[�o�[�ɑ���֐� args1:���ʔԍ� args2:�ϓ�HP args3:�������ǂ���
	void SendEnemyMoveHPInfoToServer(int identNum, float moveHP, bool isPlus = true);

	//���̃v���C���[�̃��X�g���擾����֐�
	const inline std::list<std::shared_ptr<DummyPlayer>>& GetOtherPlayersList() {
		return otherPlayers;
	}
	//UUID�ƍ��v����DummyPlayer�����X�g�����������֐�
	void PopOtherPlayerInUUID(std::string UUID);

	//UUID�ƍ��v����DummyPlayer�����邩�ǂ����m���߂�֐�
	bool CheckIsThereInUUID(std::string UUID);

	//UUID�ƍ��v����DummyPlayer�𓮂����֐�
	void MoveDummyInUUID(float x, float y, int dir, std::string UUID);

	//UUID�ƍ��v����DummyPlayer��HP��ϓ�������֐�
	void UpdateDummyHP(std::string UUID, float moveHP);

	//�T�[�o�[��Attribute�̃f�[�^�𑗐M����֐�
	void SendPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);
	//�T�[�o�[���痈��Attribute�̃f�[�^���Z�b�g����֐�
	void SetPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	//�T�[�o�[��attribute��v������֐�
	void GetPlayerAttribute();
	//�T�[�o�[��Player�f�[�^��v������֐�
	void GetPlayerInfo(std::string UUID);

	//�T�[�o�[�ɖ��O�𑗂�֐�
	void EntryServer();
	//�T�[�o�[����UUID���擾����֐�
	void GetMyUUID();



	//�l�p�`�̃}�E�X�N���b�N���m
	bool isClickedRect(int RectLeft, int RectTop, int RectRight, int RectBottom);
	bool isClickedRect(tnl::Vector3& CenterPos, int halfSize = 16);

	//�l�p�`�̃}�E�X�͈͓����m
	bool OnMouseRect(int RectLeft, int RectTop, int RectRight, int RectBottom);

	//�}�E�X���W�̎擾
	tnl::Vector3 GetMousePos();


};