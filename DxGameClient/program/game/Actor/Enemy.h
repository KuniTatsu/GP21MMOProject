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

	Enemy(tnl::Vector3 SpawnPos, std::shared_ptr<ActorData>& data, std::vector<int>& ghs, int type);

	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	void SetCircleSize(tnl::Vector3& size);

	inline float GetCircleSize() {
		return circleSize;
	}

private:
	int img_Ghost = 0;
	bool onFollowToPlayer = false;

	std::vector<int>myAnimationGh;

	/*移動スピード*/
	float SPEED = 0;

	unsigned int ChangedColor();

	GameManager* gManager = nullptr;

	//当たり判定用の半径
	float circleSize = 0.0f;

private:
	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	void EnemyMove();

};