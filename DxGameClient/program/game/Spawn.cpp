#include "Spawn.h"

Spawn::Spawn()
{

}

Spawn::~Spawn()
{

}

/*シングルトン*/
Spawn* Spawn::GetInstance()
{
	if (!instance) {
		instance = new Spawn();
	}
	return instance;
}
