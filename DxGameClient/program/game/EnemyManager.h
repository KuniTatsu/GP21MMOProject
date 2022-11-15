#pragma once

#include<vector>
#include<memory>
#include "../dxlib_ext/dxlib_ext.h"

class Camera;
class GameManager;
class Enemy;
class ActorData;

class EnemyManager {
private:
	EnemyManager();
	~EnemyManager();

	static EnemyManager* instance;

	GameManager* gManager = nullptr;

	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	enum class EnemyType {
		GHOST,
		SLIME,
		GOBLIN,
		MAX
	};

	/*ランダム変数*/
	int random = 0;
	/*範囲指定のランダム関数*/
	int randomRange(int minRange, int maxRange);

	//const int FIXDIS[4] = { -512,512,512,-512 };
	const int FIXDIS[4] = { -100,100,100,-100 };

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	///*Enemyスポーン*/
	//void SpawnEnemy(tnl::Vector3& PlayerPos);

	//private関数群
private:
	void LoadEnemyMaster();

	std::shared_ptr<ActorData> GetEnemyData(int type);


public:
	//インスタンスの取得
	static EnemyManager* GetInstance();

	void Destory();

	void SelectEnemy(tnl::Vector3 posEnemy);

	/*Enemyスポーン*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);

	void CreateEnemy(int type, tnl::Vector3& posEnemy);

	void Update(float deltatime);
	void Draw(Camera* camera);
};