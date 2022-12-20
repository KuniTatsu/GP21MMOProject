#pragma once
#include"Actor.h"

class Camera;
class GameManager;


//fukushi_develop
//gManager->GetVectorToPlayerをつかってプレイヤーへの方向ベクトルを取得し、自分の持つmoveSpeedを掛けた値が1フレーム内に移動する移動量
//Move関数を新しく作り、その中にその値を取得するコードを実装し、移動させる
//move関数はupdateの中で呼ぶorgameManagerのupdateでリストから呼ぶ

class Enemy : public Actor {
public:

	//Enemy(tnl::Vector3 SpawnPos);
	Enemy(tnl::Vector3 SpawnPos,double attackRange, float attack, float defence, float speed);
	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

private:
	int img_Ghost = 0;

	unsigned int ChangedColor(bool atack);

	GameManager* gManager = nullptr;
private:
	void SearchCircle(int SpawnPosX,int SpawnPosY, double atackRange);
};