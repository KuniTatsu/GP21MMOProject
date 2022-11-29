/*
�N���C�A���g�ɕ\�����鑼�v���C���[�̃N���X
�ʒu���̍X�V�֐��ƕ`��֐�������

*/

#pragma once
#include "Actor.h"
#include<vector>
#include<string>

class Camera;

class DummyPlayer:public Actor
{
public:
	DummyPlayer(float posX,float posY);
	~DummyPlayer();

	void Draw(Camera* camera)override;

	void SetGh(std::string ghPass);

	//���v���C���[�̕`����W���T�[�o�[����󂯎��X�V����֐�
	void UpdatePosition(float posX, float posY);

private:
	//�`�悷��gh
	int gh = 0;
	//�A�j���[�V��������gh �{���͂��������g��
	std::vector<int>ghs;

};

