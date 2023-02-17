#pragma once
#include"Actor.h"


class Talent;
class Job;
class Inventory;
class EquipItem;

class Player :public Actor
{
public:
	//初回ログイン時のプレイヤー作成コンストラクタ
	Player(int startX, int startY, int type);
	//再ログイン時はこっち
	Player(int startX, int startY, double HP, int ghNum);
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

	//才能一覧を取得する関数
	inline const std::vector<std::shared_ptr<Talent>>& GetMyTalents() {
		return myTalents;
	}

	//職一覧を取得する関数
	inline std::vector<std::shared_ptr<Job>>& GetmyJobs() {
		return myJobs;
	}

	inline bool GetIsCreatedDummy() {
		return isCreatedDummy;
	}
	inline void	SetIsCreatedDummy() {
		isCreatedDummy = true;
	}

	void SetAttributeFromServer(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	void SetTalent();

	void SetPlayerJob(std::shared_ptr<Job>job);


	// 職のデータを取得する関数
	void SetPlayerInitJob();
	//Menuを開ける状況かどうか
	inline bool GetCanOpenMenu() {
		return canOpenMenu;
	}
	inline void SetCanOpenMenu(bool swich) {
		if (canOpenMenu == swich)return;
		canOpenMenu = swich;
	}

	//装備アイテムの一覧を取得する関数
	inline std::vector<std::shared_ptr<EquipItem>>& GetEquipItems() {
		return myEquipItem;
	}

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

	//才能の最大ランク合計数
	const int maxTalentRank = 20;

	//才能の現在の残りランク数
	int remainRankNum = maxTalentRank;

	//プレイヤーが持っているタレントの配列
	std::vector<std::shared_ptr<Talent>>myTalents;

	//	プレイヤーが持っている職の配列
	std::vector<std::shared_ptr<Job>>myJobs;

	//すでにDummyが作られているか
	bool isCreatedDummy = false;
	//menuが開けるか
	bool canOpenMenu = true;

	std::vector<std::shared_ptr<EquipItem>>myEquipItem;
};

