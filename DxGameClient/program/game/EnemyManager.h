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
	const int SPAWNLIMIT = 20;

	int spawnLimit = 5;

	//インターバルのカウント開始Flag
	bool spawntiming = false;
	//生成するまでのインターバルをカウント
	int intervalCount = 0;
	//インターバルの制限時間
	const int intervalLimit = 1;

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	std::vector<bool>isUseEnemyIdentNum;

	//private関数群
private:
	void LoadEnemyMaster();

public:
	//インスタンスの取得
	static EnemyManager* GetInstance();
	void Destory();

	/*エネミー種類*/
	enum class EnemyType : uint32_t {
		GHOST,
		SLIME,
		GOBLIN,
		MAX
	};

	/*エネミーリスト*/
	std::list<std::shared_ptr<Enemy>> EnemyList;

	const int MAXRECENTDEAD = 10;

	//直近で死んだエネミーのリスト(蘇り処理のため一次保存) 最大10体
	std::list<std::shared_ptr<Enemy>> recentDeadEnemyList;

	//エネミースポーンウェイト
	std::vector<int>EnemySpawnWeight;

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
	//敵の識別番号で開いている番号を調べ、返す関数
	int SearchBlankEnemyNum();

	//Enemyの位置座標の同期
	void ShareEnemyPosFromServer(int identId, float x, float y, int dir, int type);

	//Enemyのステータス変更の同期
	void ShareEnemyStatusFromServer(int identId, float moveHP);

	//Enemyの死亡状況の同期 args1:識別番号 args2:0->生きてる,1->死んでる
	//基本的には敵が死んだときに共有するために使う
	//敵が生き返る系の実装があるかもしれないので0で生き返るように実装する余地を残す
	void ShareEnemyDead(int identId, int isDead = 1);

	void SortEnemyList(tnl::Vector3& playerPos);

	/*エネミー生成関数*/
	void CreateEnemy(int type, tnl::Vector3& posEnemy);
	//サーバーからの情報でのエネミー生成関数
	void CreateEnemyFromServer(int type, int identId, tnl::Vector3& spawnPos);

	void Update(float deltatime);
	void Draw(Camera* camera);
};