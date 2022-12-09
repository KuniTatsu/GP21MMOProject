#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"


Actor::Actor()
{
	gManager = GameManager::GetInstance();
	myData = std::make_shared<ActorData>();
}

std::vector<tnl::Vector3> Actor::GetCharaEdgePos()
{
	std::vector<tnl::Vector3>ret;
	tnl::Vector3 leftTop = drawPos - tnl::Vector3{ width, height, 0 };
	tnl::Vector3 rightTop = drawPos - tnl::Vector3{ -width, height, 0 };

	tnl::Vector3 leftBottom = drawPos - tnl::Vector3{ width, -height, 0 };
	tnl::Vector3 rightBottom = drawPos - tnl::Vector3{ -width, -height, 0 };

	ret.emplace_back(leftTop);
	ret.emplace_back(rightTop);
	ret.emplace_back(leftBottom);
	ret.emplace_back(rightBottom);

	return ret;
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
		if (y > 0)return static_cast<uint32_t>(EXDIR::RIGHTBOTTOM);
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
		if (y > 0)myExDir = EXDIR::BOTTOM;
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
	//�U���^�C�v���擾����ɂ���Ĕ�������U����ω�������
	if (myType == ATTACKTYPE::MELEE) {
		//�U���͈͂��v���C���[�̐��ʕ����Ɍ����ēガ����
		//����, �E��, ����, �E���̏��Ŋi�[(��]�ς݂̓����蔻����W)
		auto boxPos = GetMeleeAttackBox();

		//�����蔻��̒������擾����
		auto boxCenter = gManager->GetCenterVector(boxPos[0], boxPos[3]);

		//���S�����ԋ߂��̓G��4�_�̂�����ԋ߂��_���擾����

		//���̓_�Ɣ͈͂�4�̓_�̃x�N�g���Ƃ̊O�ς����A��ł���������Γ������ĂȂ�

		//��ŋ��߂������Ă�������ւ̎l�p�`�͈̔͂œ����蔻������
		//�����ɍU���A�j���[�V�����𐶐����A�`�悷��
		//�͈͓���enemy�����邩�ǂ������肷��
		//�������ĂȂ��Ȃ珈�����I����

	}
	else if (myType == ATTACKTYPE::RANGE) {

	}



}
//�����Ă�������̓����蔻��̎l�p�`�̎l�_���擾����֐� ����,�E��,����,�E���̏��Ŋi�[����
std::vector<tnl::Vector3> Actor::GetMeleeAttackBox()
{
	//�g�����{�l�̍U���͈͂��擾����
	float myRange = myData->GetAttackRange();

	//�g�����{�l�̍U���̕����擾����
	float myAttackWidth = myData->GetAttackWidth();

	float left = drawPos.x - (myAttackWidth / 2);
	float right = drawPos.x + (myAttackWidth / 2);

	//������̎l�p�`�̍U���͈͂��f�t�H���g�Ƃ��čŏ��ɍ��
	//������̍U���Ƃ��Ă̍����̓_���W
	tnl::Vector3 leftBottom = { left,drawPos.y - (height / 2),0 };
	tnl::Vector3 rightBottom = { right,drawPos.y - (height / 2),0 };

	tnl::Vector3 leftTop = { left ,drawPos.y - (height / 2) - myRange,0 };
	tnl::Vector3 rightTop = { right ,drawPos.y - (height / 2) - myRange,0 };

	//�L�����������Ă�������ɉ�����4�_�̍��W����]������@���S��drawPos
	auto fixLeftBottom = gManager->RotatePoint(leftBottom, static_cast<int>(myExDir), drawPos);
	auto fixRightBottom = gManager->RotatePoint(rightBottom, static_cast<int>(myExDir), drawPos);//�����蔻��ɂ���

	auto fixLeftTop = gManager->RotatePoint(leftTop, static_cast<int>(myExDir), drawPos);//�����蔻��ɂ���
	auto fixRightTop = gManager->RotatePoint(rightTop, static_cast<int>(myExDir), drawPos);

	std::vector<tnl::Vector3> vectors;
	vectors.emplace_back(fixLeftTop);
	vectors.emplace_back(fixRightTop);
	vectors.emplace_back(fixLeftBottom);
	vectors.emplace_back(fixRightBottom);

	//test �����蔻��͈̔͂��摜�ŕ`��
	if (!bufPos.empty()) {
		bufPos.clear();
	}
	bufPos.emplace_back(fixLeftTop);
	bufPos.emplace_back(fixRightTop);
	bufPos.emplace_back(fixLeftBottom);
	bufPos.emplace_back(fixRightBottom);

	return vectors;
}
