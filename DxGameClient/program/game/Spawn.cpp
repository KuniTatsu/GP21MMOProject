#include "Spawn.h"

Spawn::Spawn()
{

}

Spawn::~Spawn()
{

}

/*�V���O���g��*/
Spawn* Spawn::GetInstance()
{
	if (!instance) {
		instance = new Spawn();
	}
	return instance;
}
