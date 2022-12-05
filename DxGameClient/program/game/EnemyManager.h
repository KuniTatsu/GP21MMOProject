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

	/*ランダム変数*/
	//int random = 0;
	/*範囲指定のランダム関数*/
	//int randomRange(int minRange, int maxRange);

	/*エネミー生成回数*/
	int createCount = 0;
	int spawnLimit = 5;

	//const int FIXDIS[4] = { -512,512,512,-512 };
	const int FIXDIS[4] = { -100,100,100,-100 };

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	///*Enemyスポーン*/
	//void SpawnEnemy(tnl::Vector3& PlayerPos);

	//private関数群
private:
	void LoadEnemyMaster();

public:
	//インスタンスの取得
	static EnemyManager* GetInstance();
	void Destory();

	/*エネミー種類*/
	enum class EnemyType {
		GHOST,
		SLIME,
		GOBLIN,
		MAX
	};

	bool spawntiming = false;
	/*エネミーリスト*/
	std::list<std::shared_ptr<Enemy>> EnemyList;
	//Enemyデータ取得
	std::shared_ptr<ActorData> GetEnemyData(int type);
	//Enemyスポーン範囲検索
	void SpawnEnemy(tnl::Vector3& PlayerPos);
	//エネミーリストの取得
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