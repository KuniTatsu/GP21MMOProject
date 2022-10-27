#pragma once
#include"../Actor/Camera.h"
class CreateMapBase {
public:
	CreateMapBase();
	virtual ~CreateMapBase() {}

	virtual void UpdateMap(float deltatime){}
	virtual void DrawMap(Camera* camera){}
};