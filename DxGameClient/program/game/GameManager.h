#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>

class SceneBase;
class SceneManager;

class ChatBase;
class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	ChatBase* chat = nullptr;

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

public :


	// インスタンスの取得
	static GameManager* GetInstance();

	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	void Update(float delta_time);

	void Destroy();
	float deltaTime = 0.0f;

public :

	// ゲーム全体で参照したい変数はここで用意
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

};




