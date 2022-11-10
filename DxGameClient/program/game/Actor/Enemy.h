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

	/*�����_��*/
	int random = 0;

	
	int randomRange(int minRange, int maxRange);
	
	const int FIXDIS[4] = { -512,512,512,-512 };

	/*Enemy�X�|�[��*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);
};