#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
}

void Actor::SetActorData(double attackRange, float attack, float defence, float moveSpeed)
{
	myData->SetAllStatus(attackRange, attack, defence, moveSpeed);
}

void Actor::Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed)
{
	if (--actWait <= 0) {
		actIndex++;
		actWait = Speed;
		actIndex %= MaxIndex;
	}
	drawGh = DrawGhs[actIndex + MaxIndex * static_cast<uint32_t>(myExDir)];

	if (drawGh == -1) {
		int hoge = 0;
	}
}

void Actor::MoveUp()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {0, -1, 0};
}

void Actor::MoveRight()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {1, 0, 0};
}

void Actor::MoveDown()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {0, 1, 0};
}

void Actor::MoveLeft()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {-1, 0, 0};
}
//�w����W����w�苗�����ꂽ�ꏊ�̍��W���擾����֐� �����蔻��̒Z�`�̊e�_���W�����߂�̂Ɏg��
tnl::Vector3 Actor::GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance)
{
	//�����Ă�������ɂ�鋗���̏C��
	tnl::Vector3 thisOffset = VECOFFSET[static_cast<uint32_t>(myDir)];
	//��Ȃ�y���}�C�i�X,���Ȃ�x���}�C�i�X�ɕ␳
	tnl::Vector3 fixDistance = distance * thisOffset;

	return myPos + fixDistance;
}
uint32_t Actor::GetExDir(float x, float y)
{
	//�㉺���E�̏ꍇ
	//�㉺
	if (x == 0.0f) {
		if (y > 0)return static_cast<uint32_t>(EXDIR::BOTTOM);
		else if (y < 0)return static_cast<uint32_t>(EXDIR::TOP);
	}
	//���E
	if (y == 0.0f) {
		if (x > 0)return static_cast<uint32_t>(EXDIR::RIGHT);
		else if (x < 0)return static_cast<uint32_t>(EXDIR::LEFT);
	}

	//�΂ߕ����̈ړ�
	//�E����
	if (x > 0) {
		if(y>0)return static_cast<uint32_t>(EXDIR::RIGHTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::RIGHTTOP);
	}
	//������
	else {
		if (y > 0)return static_cast<uint32_t>(EXDIR::LEFTBOTTOM);
		else return static_cast<uint32_t>(EXDIR::LEFTTOP);
	}
	return 0;
}
void Actor::SetExDir(float x, float y)
{
	//�㉺���E�̏ꍇ
	//�㉺
	if (x == 0.0f) {
		if (y > 0)myExDir=EXDIR::BOTTOM;
		else if (y < 0)myExDir = EXDIR::TOP;
		return;
	}
	//���E
	if (y == 0.0f) {
		if (x > 0)myExDir = EXDIR::RIGHT;
		else if (x < 0)myExDir = EXDIR::LEFT;
		return;
	}

	//�΂ߕ����̈ړ�
	//�E����
	if (x > 0) {
		if (y > 0)myExDir = EXDIR::RIGHTBOTTOM;
		else myExDir = EXDIR::RIGHTTOP;
		return;
	}
	//������
	else {
		if (y > 0)myExDir = EXDIR::LEFTBOTTOM;
		else myExDir = EXDIR::LEFTTOP;
		return;
	}
}
//�ʏ�U���֐�
void Actor::DefaultAttack()
{
	//�g�����{�l�̍U���͈͂��擾����
	double myRange = myData->GetAttackRange();
	//�U���^�C�v���擾����ɂ���Ĕ�������U����ω�������
	if (myType == ATTACKTYPE::MELEE) {
		//�U���͈͂��v���C���[�̐��ʕ����Ɍ����ēガ����
		//����͌������č����̃v���C���[�t��

		tnl::Vector3 distance;

		if (myDir == DIR::UP) {
			distance = tnl::Vector3(-(width / 2), height / 2, 0);
		}
		else if (myDir == DIR::RIGHT) {
			distance = tnl::Vector3(width / 2, -(height / 2), 0);
		}
		else if (myDir == DIR::DOWN) {
			distance = tnl::Vector3(width / 2, height / 2, 0);
		}
		else if (myDir == DIR::LEFT) {

		}


		//tnl::Vector3 leftTop = GetPositionToVector(drawPos, )

	}
	else if (myType == ATTACKTYPE::RANGE) {

	}



}
