#pragma once
#include<vector>
#include"../dxlib_ext/dxlib_ext.h"

class Camera;

class Effect
{
public:
	Effect(std::vector<int>& Anim, tnl::Vector3& Pos,int Id, int MaxIndex, float ActSpeed = 3.0f);

	//master用コンストラクタ//int id,int MaxIndex, float ActSpeed = 3.0f
	Effect(int Id, int MaxIndex, float ActSpeed = 3.0f);
	~Effect();

	void Update();

	void Draw(Camera* camera);

	inline int GetId() {
		return id;
	}

	inline int GetMaxIndex() {
		return maxMotionIndex;
	}

	inline float GetActSpeed() {
		return actSpeed;
	}

	inline bool GetIsLive() {
		return isAlive;
	}

private:

	int id = 0;

	std::vector<int>animGh = {};

	//描画座標
	tnl::Vector3 pos;
	//コマ更新フレーム数
	float actSpeed = 0;
	//コマ最大数
	int maxMotionIndex = 0;
	//現在のフレームカウント
	float actWait = actSpeed;

	//選択中の画像インデックス
	int actIndex = 0;
	//描画する画像
	int drawGh = 0;

	bool isAlive = true;
};

