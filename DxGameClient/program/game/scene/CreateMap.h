#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class Camera;
class Map;

class CreateMap  {
public:
	CreateMap(tnl::Vector3 start);

	std::list<Map*> map;
	
	void Update(float deltatime);
	void Draw(Camera* camera);

};