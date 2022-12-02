#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class GameManager;
class EnemyManager;

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();

	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;

public:

	/*Enemy種類選択*/
	void SelectEnemy(tnl::Vector3 posEnemy);
	/*Enemyスポーン範囲検索*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);

private:

	//エネミー同士がかぶっていないかチェック
	bool CheckCanCreateEnemy(tnl::Vector3& Pos);

	/*ランダム変数*/
	int random = 0;
	/*範囲指定のランダム関数*/
	int randomRange(int minRange, int maxRange);

};

