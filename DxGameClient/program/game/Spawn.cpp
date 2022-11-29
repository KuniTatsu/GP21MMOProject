#include "Spawn.h"

Spawn::Spawn()
{

}

Spawn::~Spawn()
{

}

/*ƒVƒ“ƒOƒ‹ƒgƒ“*/
Spawn* Spawn::GetInstance()
{
	if (!instance) {
		instance = new Spawn();
	}
	return instance;
}
