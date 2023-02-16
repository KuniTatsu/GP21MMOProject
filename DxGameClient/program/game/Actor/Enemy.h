#pragma once
#include"Actor.h"

class Camera;
class GameManager;


//fukushi_develop
//gManager->GetVectorToPlayerをつかってプレイヤーへの方向ベクトルを取得し、自分の持つmoveSpeedを掛けた値が1フレーム内に移動する移動量
//Move関数を新しく作り、その中にその値を取得するコードを実装し、移動させる
//move関数はupdateの中で呼ぶorgameManagerのupdateでリストから呼ぶ
//Enemyのコンストラクタにグラフィックスハンドルint型で引数に持ってくる
//std::vector<int>の参照を引数に持つ

class Enemy : public Actor {
public:

	//自クライアント用コンストラクタ
	Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type);

	//サーバーから情報をもってきて作る時用
	Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type,int IdentId);

	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	inline int GetIdentId() {
		return identId;
	}
	//位置座標の同期
	void MoveEnemyFromServerInfo(float x, float y, int dir);
	//ステータスの同期
	void ChangeStatusFromServerInfo(float moveHP);

private:
	int img_Ghost = 0;
	bool onFollowToPlayer = false;

	std::vector<int>myAnimationGh;

	/*移動スピード*/
	float SPEED = 0;

	int identId = -1;
	
	unsigned int ChangedColor();

	GameManager* gManager = nullptr;

private:
	//void Move();

	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	void EnemyMove();

};