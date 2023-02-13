#include "Actor.h"
#include"ActorData.h"
#include"../GameManager.h"
#include"Camera.h"
#include"../EnemyManager.h"
#include"Enemy.h"
#include"Player.h"
#include"../BattleLogic.h"
#include"../EffectManager.h"
#include<math.h>

#include"../scene/Map.h"

Actor::Actor()
{
	gManager = GameManager::GetInstance();
	myData = std::make_shared<ActorData>();
	SetDefaultAttackOffset();
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

void Actor::SetActorData(float attack, float defence, float moveSpeed)
{
	myData->SetAllStatus(attack, defence, moveSpeed);
}

void Actor::SetActorAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX)
{
	myData->SetAttribute(STR, VIT, INT, MID, SPD, DEX);
}

void Actor::SetCircleSize(tnl::Vector3& size)
{
	if (size.x >= size.y)circleSize = size.x / 2;
	else circleSize = size.y / 2;
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

bool Actor::HitMaptoCharacter(tnl::Vector3& pos)
{
	/*auto& player = GameManager::GetInstance()->GetPlayer();
	tnl::Vector3& characterPos = player->GetPos();*/

	auto map = GameManager::GetInstance()->GetPlayerOnMap();

	auto& hitMap = map->GetHitMap();

	auto x = std::floor(pos.x / 32);
	auto y = std::floor(pos.y / 32);

	tnl::Vector3 localPos = (tnl::Vector3(x+1, y+1, 0));

	if (hitMap[localPos.y+17][localPos.x+17] == 65)return false;
	return true;
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
tnl::Vector3 Actor::GetNearestPoint(tnl::Vector3& Pos, std::vector<tnl::Vector3>& boxPos)
{
	std::vector<tnl::Vector3> nearPoses;

	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[0], boxPos[1]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[1], boxPos[2]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[2], boxPos[3]));
	nearPoses.emplace_back(gManager->GetNearestPointLine(Pos, boxPos[3], boxPos[0]));

	std::vector<float>distances;

	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[0]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[1]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[2]));
	distances.emplace_back(gManager->GetLengthFromTwoPoint(Pos, nearPoses[3]));

	int mostNearNum = 0;

	for (int i = 1; i < 4; ++i) {
		if (distances[mostNearNum] > distances[i]) {
			mostNearNum = i;
		}
	}
	return nearPoses[mostNearNum];
}
void Actor::SetDefaultAttackOffset()
{
	auto range = myData->GetAttackRange();

	EFFECTOFFSET[static_cast<int>(EXDIR::LEFTTOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(225)), (range / 2) * std::sin(tnl::ToRadian(225)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::LEFT)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(180)), (range / 2) * std::sin(tnl::ToRadian(180)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::LEFTBOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(135)), (range / 2) * std::sin(tnl::ToRadian(135)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::BOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(90)), (range / 2) * std::sin(tnl::ToRadian(90)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHTBOTTOM)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(45)), (range / 2) * std::sin(tnl::ToRadian(45)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHT)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(0)), (range / 2) * std::sin(tnl::ToRadian(0)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::RIGHTTOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(315)), (range / 2) * std::sin(tnl::ToRadian(315)), 0);
	EFFECTOFFSET[static_cast<int>(EXDIR::TOP)] = tnl::Vector3((range / 2) * std::cos(tnl::ToRadian(270)), (range / 2) * std::sin(tnl::ToRadian(270)), 0);

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
void Actor::SetExDirFromInt(int dir)
{
	switch (dir)
	{
	case 0:
		myExDir = EXDIR::LEFTTOP;
		break;
	case 1:
		myExDir = EXDIR::LEFT;
		break;
	case 2:
		myExDir = EXDIR::LEFTBOTTOM;
		break;
	case 3:
		myExDir = EXDIR::BOTTOM;
		break;
	case 4:
		myExDir = EXDIR::RIGHTBOTTOM;
		break;
	case 5:
		myExDir = EXDIR::RIGHT;
		break;
	case 6:
		myExDir = EXDIR::RIGHTTOP;
		break;
	case 7:
		myExDir = EXDIR::TOP;
		break;
	default:
		break;
	}
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
void Actor::SetExDir(int dir)
{
	switch (dir)
	{
	case 0:
		myExDir = EXDIR::LEFTTOP;
		break;
	case 1:
		myExDir = EXDIR::LEFT;
		break;
	case 2:
		myExDir = EXDIR::LEFTBOTTOM;
		break;
	case 3:
		myExDir = EXDIR::BOTTOM;
		break;
	case 4:
		myExDir = EXDIR::RIGHTBOTTOM;
		break;
	case 5:
		myExDir = EXDIR::RIGHT;
		break;
	case 6:
		myExDir = EXDIR::RIGHTTOP;
		break;
	case 7:
		myExDir = EXDIR::TOP;
		break;
	default:
		break;
	}
}
//�ʏ�U���֐�
void Actor::DefaultAttack()
{
	//�U����������Ȃ�s�����s��Ȃ�
	if (attackInterval > 0.0f)return;

	//�U����
	std::shared_ptr<Actor> attackActor = shared_from_this();
	//�h�q��
	std::vector<std::shared_ptr<Actor>> defendActor;
	defendActor.clear();

	//�U���^�C�v���擾����ɂ���Ĕ�������U����ω�������
	if (myType == ATTACKTYPE::MELEE) {
		//�U���͈͂��v���C���[�̐��ʕ����Ɍ����ēガ����
		//����, �E��, ����, �E���̏��Ŋi�[(��]�ς݂̓����蔻����W)
		auto boxPos = GetMeleeAttackBox();


		//auto animPos = tnl::Vector3(50, 50, 0);

		//�U���A�j���[�V�����̐���

		auto animPos = drawPos + EFFECTOFFSET[static_cast<int>(myExDir)];
		EffectManager::GetInstance()->CreateEffect(static_cast<int>(EffectManager::EFFECTTYPE::NORMAL), animPos);

		//�C���^�[�o���Z�b�g
		attackInterval = canAttackTime;

		bool isHit = false;

		//�U���҂��v���C���[�̏ꍇ
		if (actorType == 0) {

			//�G�̃��X�g�̃\�[�g�@�v���C���[�ɋ߂���
			auto eManager = EnemyManager::GetInstance();
			eManager->SortEnemyList(drawPos);

			auto& list = eManager->GetEnemyList();

			for (auto& enemy : list) {
				//�G�̍��W
				auto& pos = enemy->GetPos();
				//����p�̈�ԋ߂��_�����߂�
				tnl::Vector3 mostNear = GetNearestPoint(pos, boxPos);

				//��ԋ߂��_�ƓG�̓����蔻��̉~�̒��S�Ƃ̋��������߂�
				float pointToCircleCenter = gManager->GetLengthFromTwoPoint(mostNear, pos);
				//���̋������G�̓����蔻��̔��a��菬�����Ȃ瓖�����Ă���
				if (enemy->GetCircleSize() > pointToCircleCenter)isHit = true;
				else {
					//����Ă���ꍇ�̔���
					if (gManager->isHitRotateBox(boxPos, pos))isHit = true;
				}

				//�������Ă���ꍇ�_���[�W����Ώۂɓ����
				if (isHit) {
					defendActor.emplace_back(enemy);
					isHit = false;
					continue;
					//bool successAttack = BattleLogic::GetInstance()->IsSuccessAttack();
				}
				//�������Ă��Ȃ��L�����������炻��ȍ~���������Ă��Ȃ��̂ł�߂�
				break;
			}
		}
		//enemy���U���҂̏ꍇ
		else {
			auto& player = GameManager::GetInstance()->GetPlayer();
			auto& pos = player->GetPos();

			//����p�̈�ԋ߂��_�����߂�
			tnl::Vector3 mostNear = GetNearestPoint(pos, boxPos);

			//��ԋ߂��_�ƓG�̓����蔻��̉~�̒��S�Ƃ̋��������߂�
			float pointToCircleCenter = gManager->GetLengthFromTwoPoint(mostNear, pos);
			//���̋������G�̓����蔻��̔��a��菬�����Ȃ瓖�����Ă���
			if (player->GetCircleSize() > pointToCircleCenter)isHit = true;

			//����Ă���ꍇ�̔���
			if (gManager->isHitRotateBox(boxPos, pos))isHit = true;
			//�������Ă���ꍇ�_���[�W����Ώۂɓ����
			if (isHit)defendActor.emplace_back(player);

			//bool successAttack = BattleLogic::GetInstance()->IsSuccessAttack();
		}
	}
	else if (myType == ATTACKTYPE::RANGE) {

	}

	auto attackData = attackActor->GetActorData();

	for (auto& defender : defendActor) {
		auto defendData = defender->GetActorData();

		auto battleLogic = BattleLogic::GetInstance();

		//�_���[�W����
		bool successAttack = battleLogic->IsSuccessAttack(attackData, defendData, static_cast<int>(myType));

		double damage = battleLogic->CalcDefaultDamage(attackData->GetAttack(), defendData->GetDefence(), attackData->GetLevel(), successAttack);
		if (defendData->UpdateHp((damage * (-1)))) {
			//true�ŋA���Ă����玀��ł�̂ŁAislive��ς���
			defender->SetIsLive(false);
		}
	}
}
void Actor::UpdateAttackInterval(const float deltatime)
{
	//�C���^�[�o����0�ȉ��Ȃ猸�炳�Ȃ�
	if (attackInterval <= 0.0f) return;

	//�C���^�[�o���X�V
	attackInterval -= deltatime;
	//�}�C�i�X�ɂȂ��Ă�����0�ɂ���
	if (attackInterval < 0.0f) attackInterval = 0.0f;
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
