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

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;
	//各チャンクのマップポインタを持つ配列
	std::list<std::shared_ptr<Map>>Maps;
	
	//playerがいるマップのポインタ
	std::shared_ptr<Map>lastStayMap = nullptr;

	// ゲーム全体で参照したい変数はここで用意
public:
	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	//一チャンクの一辺のチップ数
	const int MAPSIZE = 5.0;
	//一チップの大きさ
	const int CHIPWIDTH = 32;
	const int CHIPHEIGHT = 32;

	float deltaTime = 0.0f;

	const tnl::Vector3 MAPPOSOFFSET[8] = { 
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//左上
		tnl::Vector3(0,-MAPSIZE * CHIPHEIGHT,0),//上
		tnl::Vector3(MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//右上
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,0,0),//左
		tnl::Vector3(MAPSIZE * CHIPWIDTH,0,0),//右
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0),//左下
		tnl::Vector3(0,MAPSIZE * CHIPHEIGHT,0),//下
		tnl::Vector3(MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0)//右下 
	};

public:
	// インスタンスの取得
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

	// 
	//単位ベクトル取得関数
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}

	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string Gh);

	//string型の文字コード変換
	std::string SjistoUTF8(std::string srcSjis);
	std::string UTF8toSjis(std::string srcUTF8);

	//当たり判定 短形同士
	bool isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2);
	//Player(このクライアントの)生成
	std::shared_ptr<Player> CreatePlayer();

	//Map新規生成
	bool CreateMap();

	//そのマップにこのクライアントのPlayerがいるかどうか
	bool IsOnMap();

	//Playerのいるマップの登録
	void SetStayMap();
	//Player(このクライアントの)がいるマップポインタを取得する関数
	std::shared_ptr<Map>GetPlayerOnMap();

	//指定座標からマップを取得する関数
	std::shared_ptr<Map>GetMapOnPoint(tnl::Vector3& Point);

	//Playerが越境したかどうか確かめる関数
	bool IsOverChunk();

	//Mapポインタの中心座標からPlayerの中心座標への距離を求める関数
	float GetMapToPlayerDistance(std::shared_ptr<Map> map);

	//チャンク中心からチャンク中心への距離を求める関数
	inline float GetChunkDistance() {
		return static_cast<float>(MAPSIZE * CHIPHEIGHT);
	}
	
	void CrateEnemy(tnl::Vector3 Pos);

	//マップリストの取得
	std::list<std::shared_ptr<Map>> GetMapList();
	//エネミーリストの取得
	std::list<std::shared_ptr<Enemy>> Enemy();
	//std::list<std::shared_ptr<Enemy>> GetEnemyList();

};