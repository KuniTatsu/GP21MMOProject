#pragma once
#include"../../library/tnl_vector.h"

class Camera;
class GameManager;

class Map {
public:
	Map(tnl::Vector3 start , int Chanknum);

	void Update(const float deltatime);
	void Draw(Camera* camera);
private:
	tnl::Vector3 PlayerPos;
	GameManager* gManager = nullptr;

	/*�摜�n���h��*/
	int img_mapchip_grass = 0;
	int img_mapchip_grass_line = 0;
	int img_mapchip_sea = 0;

	/*�`�b�v�T�C�Y�A�z�u��*/
	const int MAPCHIP_SIZE = 32;
	const int ChipMax = 5;
	const int Margin = 2;
	int chanknum = 0;

	int ChipStartX = 0;
	int ChipStartY = 0;


	void MapChipCreate(Camera* camera,int i);
};