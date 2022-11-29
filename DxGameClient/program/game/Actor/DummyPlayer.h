/*
クライアントに表示する他プレイヤーのクラス
位置情報の更新関数と描画関数を持つ

*/

#pragma once
#include "Actor.h"
#include<vector>
#include<string>

class Camera;

class DummyPlayer:public Actor
{
public:
	DummyPlayer(float posX,float posY);
	~DummyPlayer();

	void Draw(Camera* camera)override;

	void SetGh(std::string ghPass);

	//他プレイヤーの描画座標をサーバーから受け取り更新する関数
	void UpdatePosition(float posX, float posY);

private:
	//描画するgh
	int gh = 0;
	//アニメーションするgh 本来はこっちを使う
	std::vector<int>ghs;

};

