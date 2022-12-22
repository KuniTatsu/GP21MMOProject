#pragma once
#include"Actor.h"


class Talent;
class Player :public Actor
{
public:
	Player(int startX, int startY);
	~Player();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	//�˔\�̎c�胉���N�����擾����֐�
	inline int GetRemainRankNum() {
		return remainRankNum;
	}
	//�˔\�̎c�胉���N�������炷�֐�
	inline void MinusRemainRank(int minusNum) {
		remainRankNum -= minusNum;
	}

	inline bool GetIsCreatedDummy() {
		return isCreatedDummy;
	}
	inline void	SetIsCreatedDummy() {
		isCreatedDummy = true;
	}

	void SetTalent();

private:

	void Move();

	//���L�[�̔z��
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//�L�[�擾
	inline tnl::Input::eKeys GetKeys(int KeyNum) {
		return arrowKeys[KeyNum];
	}

	//�ꎞ�ۊǗpX�ړ���
	float moveX = 0.0f;
	//�ꎞ�ۊǗpY�ړ���
	float moveY = 0.0f;

	//�ړ��X�s�[�h
	const int SPEED = 5;

	//�ړ��L�[���������Ƃ��̈ړ���
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };


	//�˔\�̍ő僉���N���v��
	const int maxTalentRank = 20;

	//�˔\�̌��݂̎c�胉���N��
	int remainRankNum = maxTalentRank;

	//�v���C���[�������Ă���^�����g�̔z��
	std::vector<std::shared_ptr<Talent>>myTalents;

	//���ł�Dummy������Ă��邩
	bool isCreatedDummy = false;


};

