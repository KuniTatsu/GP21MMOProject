#pragma once
#include"Actor.h"

class Camera;
class GameManager;

class Enemy : public Actor {
public:

	Enemy(tnl::Vector3 SpawnPos);
	Enemy(tnl::Vector3 SpawnPos, float attack, float deffence, float speed);
	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

private:
	int img_Ghost = 0;
	GameManager* gManager = nullptr;
};