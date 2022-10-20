#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include"../Actor/Camera.h"

class Scene_Map;
class GameManager;

class Map {
public:
	/*�}�b�v�̍\��*/
	//�}�b�v�`�b�v�T�C�Y�F32�~32
	//1�`�����N��:35�~35
	//�}�b�v�T�C�Y:1120�~1120
	Map(tnl::Vector3 plapos);
	tnl::Vector3 PlayerPos;

	const int MAPCHIP_SIZE = 32;
	int img_mapchip_grass = 0;
	int img_mapchip_sea = 0;
	int img_mapchip_player = 0;

	/*�}�b�v�`�b�v�̐���*/
	void CreateMapChip(Camera* camera);

	void Update(float deltatime);
	void Draw(Camera* camera);
private:

	int playerX = 0;
	int playerY = 0;

	//Scene_Map* scenemap = nullptr;
	GameManager* gManager = nullptr;

	void mapSearch(Camera* camera, int x, int y, int n);
};