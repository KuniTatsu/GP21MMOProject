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
	std::shared_ptr<EnemySpawnManager> eSpawn = nullptr;
	bool hoge = false;

	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	/*�����_���ϐ�*/
	//int random = 0;
	/*�͈͎w��̃����_���֐�*/
	//int randomRange(int minRange, int maxRange);

	/*�G�l�~�[������*/
	int createCount = 0;
	int spawnLimit = 5;

	//const int FIXDIS[4] = { -512,512,512,-512 };
	const int FIXDIS[4] = { -100,100,100,-100 };

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	///*Enemy�X�|�[��*/
	//void SpawnEnemy(tnl::Vector3& PlayerPos);

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

	bool spawntiming = false;
	/*�G�l�~�[���X�g*/
	std::list<std::shared_ptr<Enemy>> EnemyList;
	//Enemy�f�[�^�擾
	std::shared_ptr<ActorData> GetEnemyData(int type);
	//Enemy�X�|�[���͈͌���
	void SpawnEnemy(tnl::Vector3& PlayerPos);
	//�G�l�~�[���X�g�̎擾
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return EnemyList;
	}
	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		EnemyList.emplace_back(enemy);
	}
	void CreateEnemy(int type, tnl::Vector3& posEnemy);

	void Update(float deltatime);
	void Draw(Camera* camera);
};