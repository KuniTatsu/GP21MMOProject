#pragma once

#include<vector>
#include<memory>
#include "../dxlib_ext/dxlib_ext.h"

class Camera;
class GameManager;
class EnemySpawnManager;
class Enemy;
class ActorData;

class EnemyManager {
private:
	EnemyManager();
	~EnemyManager();

	static EnemyManager* instance;

	GameManager* gManager = nullptr;
	std::shared_ptr<EnemySpawnManager> eSpawnManager = nullptr;
	bool hoge = false;

	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

			/*SpawnEnemy�֐�*/
	//������
	int createCount = 0;
	//��������
	int spawnLimit = 5;
	//�C���^�[�o���̃J�E���g�J�nFlag
	bool spawntiming = false;
	//��������܂ł̃C���^�[�o�����J�E���g
	int intervalCount = 0;
	//�C���^�[�o���̐�������
	const int intervalLimit = 1;

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

		
//private�֐��Q
private:
	void LoadEnemyMaster();

public:
	//�C���X�^���X�̎擾
	static EnemyManager* GetInstance();
	void Destory();

	/*�G�l�~�[���*/
	enum class EnemyType {
		GHOST,
		SLIME,
		GOBLIN,
		MAX
	};

	/*�G�l�~�[���X�g*/
	std::list<std::shared_ptr<Enemy>> EnemyList;
	
	//Enemy�f�[�^�擾
	std::shared_ptr<ActorData> GetEnemyData(int type);
	
	//�G�l�~�[���X�g�̎擾
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return EnemyList;
	}
	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		EnemyList.emplace_back(enemy);
	}

	//Enemy�X�|�[���͈͌���
	void SpawnEnemy(tnl::Vector3& PlayerPos);

	/*�G�l�~�[�����֐�*/
	void CreateEnemy(int type, tnl::Vector3& posEnemy);

	void Update(float deltatime);
	void Draw(Camera* camera);
};