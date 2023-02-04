#pragma once
#include<vector>
#include"../dxlib_ext/dxlib_ext.h"

class Camera;

class Effect
{
public:
	Effect(std::vector<int>& Anim, tnl::Vector3& Pos,int Id, int MaxIndex, float ActSpeed = 3.0f);

	//master�p�R���X�g���N�^//int id,int MaxIndex, float ActSpeed = 3.0f
	Effect(int Id, int MaxIndex, float ActSpeed = 3.0f);
	~Effect();

	void Update();

	void Draw(Camera* camera);

	inline int GetId() {
		return id;
	}

	inline int GetMaxIndex() {
		return maxMotionIndex;
	}

	inline float GetActSpeed() {
		return actSpeed;
	}

	inline bool GetIsLive() {
		return isAlive;
	}

private:

	int id = 0;

	std::vector<int>animGh = {};

	//�`����W
	tnl::Vector3 pos;
	//�R�}�X�V�t���[����
	float actSpeed = 0;
	//�R�}�ő吔
	int maxMotionIndex = 0;
	//���݂̃t���[���J�E���g
	float actWait = actSpeed;

	//�I�𒆂̉摜�C���f�b�N�X
	int actIndex = 0;
	//�`�悷��摜
	int drawGh = 0;

	bool isAlive = true;
};

