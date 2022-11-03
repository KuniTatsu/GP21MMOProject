#include"CreateMap.h"
#include"../Actor/Camera.h"
#include"Map.h"

CreateMap::CreateMap(tnl::Vector3 start)
{
	for (int i = 1; i < 10; ++i) {
		//map.emplace_back(new Map(start,i));
	}
}

void CreateMap::Update(float deltatime)
{

}
void CreateMap::Draw(Camera* camera)
{
	/*for (auto ma : map) {
		ma->Draw(camera);
	}*/
}
