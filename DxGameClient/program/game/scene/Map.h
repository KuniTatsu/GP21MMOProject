#pragma once
#include"../../library/tnl_vector.h"
#include<memory>
#include<vector>

class Camera;
class GameManager;
class Map;

class Map {
public:

	Map(tnl::Vector3 centerPos,int type);

	int test = 0;

	inline tnl::Vector3& GetMapCenterPos() {
		return mapCenterPos;
	}
	inline const std::vector<std::shared_ptr<Map>>& GetNearMaps() {
		return nearMaps;
	}

	inline tnl::Vector3& GetMapLeftTopPos() {
		return mapLeftTopPos;
	}
	inline tnl::Vector3& GetMapRightBottomPos() {
		return mapRightBottomPos;
	}
	
	/*���̓����蔻����W*/
	inline tnl::Vector3& GetMapHitPos() {
		return mapHitPos;
	}
	inline int GetMapHitArray() {
		return hitarray;
	}

	inline std::vector<std::vector<int>>& GetHitMap() {
		return mapChipsVillageHit;
	}

	/*���C���[�����AFALSE�Ȃ����ATRUE�Ȃ�O��*/
	inline bool SetIsFront(bool isFront) {
		return isDrawFront = isFront;
	}

	enum class MAPTYPE : uint32_t {
		VILLAGE,
		GRASS,
		MAX
	};

	void Update(const float deltatime);
	void Draw(Camera* camera);

	void SetNearMap(int dirNum,std::shared_ptr<Map>map);
private:
	tnl::Vector3 PlayerPos;
	GameManager* gManager = nullptr;

	//�}�b�v�`�b�v�̔z��
	//��
	std::vector<std::vector<int>>mapChipsVillageHit;
	std::vector<std::vector<int>>mapChipsVillageGround;
	std::vector<std::vector<int>>mapChipsVillageBack;
	std::vector<std::vector<int>>mapChipsVillageMiddle;
	std::vector<std::vector<int>>mapChipsVillageFront;
	//����
	std::vector<std::vector<int>> mapChips;

	//�}�b�v�̒��S���W
	tnl::Vector3 mapCenterPos;
	//�}�b�v�̍���̍��W
	tnl::Vector3 mapLeftTopPos;
	//�}�b�v�̉E���̍��W
	tnl::Vector3 mapRightBottomPos;

	/*�}�b�v�̓����蔻��*/
	tnl::Vector3 mapHitPos;
	int hitarray = 0;
	//std::vector<tnl::Vector3>mapHitPos;

	//���͂�8�}�b�v
	std::vector<std::shared_ptr<Map>>nearMaps;

	/*�摜�n���h��*/
	int img_mapchip_grass = 0;
	int img_mapchip_grass_line = 0;
	int img_mapchip_sea = 0;
	std::vector<int> img_mapchip_localmap;

	/*�`�b�v�T�C�Y�A�z�u��*/
	int chanknum = 0;

	/*�}�b�v�̎��*/
	int mapType = 0;

	/*�ŏ��̏����������[�h����}�b�v�t���O*/
	bool isLoadLocalMap = false;
	/*���C���[�����AFALSE�Ȃ����ATRUE�Ȃ�O��*/
	bool isDrawFront = false;
	/*�}�b�v�̃��[�h*/
	void LoadMap();

	/*���C���[�K�w�֐��i�J�����A���C���[�O������t���O�A�}�b�v�^�C�v�A�`�����N�̒��S���W�j*/
	void DrawLayer(Camera* camera, bool isFront, int maptype);
};