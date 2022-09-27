#include "Actor.h"
#include"../GameManager.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
}

void Actor::MoveUp()
{
	//ローカルポジションの移動
	localPos += {0, -1, 0};
}

void Actor::MoveRight()
{
	//ローカルポジションの移動
	localPos += {1, 0, 0};
}

void Actor::MoveDown()
{
	//ローカルポジションの移動
	localPos += {0, 1, 0};
}

void Actor::MoveLeft()
{
	//ローカルポジションの移動
	localPos += {-1, 0, 0};
}
