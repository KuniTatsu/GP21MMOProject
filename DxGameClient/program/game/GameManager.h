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

class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	std::shared_ptr<Player> player = nullptr;

	//std::shared_ptr<Connect> connect = nullptr;

	std::thread acceptThread ;

	//�}���`�X���b�h�œ�������M�p�֐�
	void Accept();

	//�}���`�X���b�h�œ��������M�p�֐�
	void Send(const std::string sendMessage);


	//ChatBase* chat = nullptr;

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;
	//�e�`�����N�̃}�b�v�|�C���^�����z��
	std::list<std::shared_ptr<Map>>Maps;

	//player������}�b�v�̃|�C���^
	std::shared_ptr<Map>lastStayMap = nullptr;

	std::list<std::shared_ptr<Enemy>> Enemys;

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��
public:
	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	//��`�����N�̈�ӂ̃`�b�v��
	const int MAPSIZE = 5.0;
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
		45.0f,//����
		90.0f,//��
		135.0f,//����
		180.0f,//��
		225.0f,//�E��
		270.0f,//�E
		315.0f,//�E��
		360.0f//��
	};



public:
	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);
	// �j��
	void Destroy();

	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {
		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);
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
	//���W�̉�]
	tnl::Vector3 RotatePoint(tnl::Vector3& centerPos, tnl::Vector3& rotatePos);


	//Player(���̃N���C�A���g��)����
	std::shared_ptr<Player> CreatePlayer();

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

	//void CreateEnemy(tnl::Vector3& Pos,int type);
	bool CheckCanCreateEnemy(tnl::Vector3& Pos);

	//�}�b�v���X�g�̎擾
	std::list<std::shared_ptr<Map>> GetMapList();
	//�G�l�~�[���X�g�̎擾
	/*std::list<std::shared_ptr<Enemy>> Enemys;*/
	//std::list<std::shared_ptr<Enemy>>&GetEnemyList();
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return Enemys;
	}


	//���M�p�X���b�h���쐬����֐�
	void CreateSendThread(const std::string sendMessage);

inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
	Enemys.emplace_back(enemy);
}
//void CreateEnemy();


	tnl::Vector3 GetVectorToPlayer(tnl::Vector3& enemyPos);
	
};