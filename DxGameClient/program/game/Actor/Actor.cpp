#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
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
