#pragma once
#include"Actor.h"
class Enemy : public Actor {
public:

	Enemy();
	~Enemy();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;
	
private:
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	int random = 0;

	void SpawnEnemy(tnl::Vector3& PlayerPos);
};