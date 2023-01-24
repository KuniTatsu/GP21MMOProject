/*
�N���C�A���g�ɕ\�����鑼�v���C���[�̃N���X
�ʒu���̍X�V�֐��ƕ`��֐�������

*/

#pragma once
#include "Actor.h"
#include<vector>
#include<string>

class Camera;

class DummyPlayer :public Actor
{
public:
	DummyPlayer(float posX, float posY, std::string UUID, int dir, float HP, int ghNum = 0);
	~DummyPlayer();

	void Update()override;
	void Draw(Camera* camera)override;
	void Init()override;

	void SetGh(std::string ghPass);

	//���v���C���[�̕`����W���T�[�o�[����󂯎��X�V����֐�
	void UpdatePosition(float posX, float posYint, int dir);
	//UUID�擾
	const inline std::string GetUUID() {
		return myUUID;
	}

private:
	////�`�悷��gh
	//int gh = 0;


	std::string myUUID = "";


};

