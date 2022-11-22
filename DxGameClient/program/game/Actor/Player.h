#pragma once
#include"Actor.h"


class Player :public Actor
{
public:
	Player(int startX,int startY);
	~Player();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

private:

	void Move();

	//矢印キーの配列
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//キー取得
	inline tnl::Input::eKeys GetKeys(int KeyNum) {
		return arrowKeys[KeyNum];
	}

	//一時保管用X移動量
	float moveX = 0.0f;
	//一時保管用Y移動量
	float moveY = 0.0f;

	//移動スピード
	const int SPEED = 5;

	//移動キーを押したときの移動量
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };


	int testGh = 0;

};

