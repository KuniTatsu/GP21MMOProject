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

			/*SpawnEnemy関数*/
	//生成回数
	int createCount = 0;
	//生成制限
	int spawnLimit = 5;
	//インターバルのカウント開始Flag
	bool spawntiming = false;
	//生成するまでのインターバルをカウント
	int intervalCount = 0;
	//インターバルの制限時間
	const int intervalLimit = 1;

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

		
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

	/*エネミーリスト*/
	std::list<std::shared_ptr<Enemy>> EnemyList;
	
	//Enemyデータ取得
	std::shared_ptr<ActorData> GetEnemyData(int type);
	
	//エネミーリストの取得
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return EnemyList;
	}
	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		EnemyList.emplace_back(enemy);
	}

	//Enemyスポーン範囲検索
	void SpawnEnemy(tnl::Vector3& PlayerPos);

	/*エネミー生成関数*/
	void CreateEnemy(int type, tnl::Vector3& posEnemy);

	void Update(float deltatime);
	void Draw(Camera* camera);
};