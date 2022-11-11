#pragma once
#include"Actor.h"

class Camera;

class Enemy : public Actor {
public:

	Enemy();
	~Enemy();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

private:
	
};