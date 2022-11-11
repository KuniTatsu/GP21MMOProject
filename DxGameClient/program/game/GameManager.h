#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>
#include<memory>
#include<list>

class SceneBase;
class SceneManager;
class ChatBase;
class Map;
class Enemy;
class Player;

class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	std::shared_ptr<Player> player = nullptr;
	ChatBase* chat = nullptr;

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;
	//�e�`�����N�̃}�b�v�|�C���^�����z��
	std::list<std::shared_ptr<Map>>Maps;
	
	//player������}�b�v�̃|�C���^
	std::shared_ptr<Map>lastStayMap = nullptr;

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

public:
	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

	// 
	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//string�^�̕����R�[�h�ϊ�
	std::string SjistoUTF8(std::string srcSjis);
	std::string UTF8toSjis(std::string srcUTF8);

	//�����蔻�� �Z�`���m
	bool isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2);
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
	
	void CrateEnemy(tnl::Vector3 Pos);

	//�}�b�v���X�g�̎擾
	std::list<std::shared_ptr<Map>> GetMapList();
	//�G�l�~�[���X�g�̎擾
	std::list<std::shared_ptr<Enemy>> Enemy();
	//std::list<std::shared_ptr<Enemy>> GetEnemyList();

};