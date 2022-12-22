#include "Graphic.h"
#include"../GameManager.h"

Graphic::Graphic(tnl::Vector3 Pos, int Gh,int Width,int Height)
{
	pos = Pos;
	gh = Gh;
	width = Width;
	height = Height;
}

Graphic::Graphic(tnl::Vector3 Pos, std::string Pass, int Width, int Height)
{
	gManager = GameManager::GetInstance();

	pos = Pos;
	filePass = Pass;
	gh = gManager->LoadGraphEx(Pass);
	width = Width;
	height = Height;
}

