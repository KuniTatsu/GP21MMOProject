#pragma once
#include"../library/tnl_vector.h"

class Camera;
class GameManager;

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
		SLIME,
		GOBLIN,
		MAX
	};

	/*ランダム変数*/
	int random = 0;
	/*範囲指定のランダム関数*/
	int randomRange(int minRange, int maxRange);

	const int FIXDIS[4] = { -512,512,512,-512 };

	/*Enemyスポーン*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);

public:
	//インスタンスの取得
	static EnemyManager* GetInstance();

	void Destory();

	void CreateEnemy(tnl::Vector3 posEnemy);
	
	void Update();
	void Draw(Camera* camera);
};