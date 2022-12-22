#pragma once
#include"Actor.h"


class Talent;
class Player :public Actor
{
public:
	Player(int startX, int startY);
	~Player();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	//才能の残りランク数を取得する関数
	inline int GetRemainRankNum() {
		return remainRankNum;
	}
	//才能の残りランク数を減らす関数
	inline void MinusRemainRank(int minusNum) {
		remainRankNum -= minusNum;
	}

	inline bool GetIsCreatedDummy() {
		return isCreatedDummy;
	}
	inline void	SetIsCreatedDummy() {
		isCreatedDummy = true;
	}

	void SetTalent();

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


	//才能の最大ランク合計数
	const int maxTalentRank = 20;

	//才能の現在の残りランク数
	int remainRankNum = maxTalentRank;

	//プレイヤーが持っているタレントの配列
	std::vector<std::shared_ptr<Talent>>myTalents;

	//すでにDummyが作られているか
	bool isCreatedDummy = false;


};

