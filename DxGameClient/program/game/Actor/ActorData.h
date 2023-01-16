/*Actor�̊�{�f�[�^���Ǘ�����N���X
	�X�e�[�^�X��摜�Ȃǂ��܂�
	�ʂ̓��ʂȃX�e�[�^�X��������ꍇ�͌p����Ŏ���������j��
*/
#pragma once


class ActorData
{
public:
	ActorData();
	~ActorData();

	//�����W��getter,setter
	inline double GetAttackRange() {
		return attackRange;
	}
	inline void SetAttackRange(double setRange) {
		if (setRange < 0.0)return;
		attackRange = setRange;
	}

	inline float GetAttack() {
		return attack;
	}

	inline float GetDefence() {
		return defence;
	}

	inline float GetMoveSpeed() {
		return moveSpeed;
	}

	void SetAllStatus(double AttackRange, float Attack, float Defence, float MoveSpeed);

	void SetHP(float Hp);

private:

	//�ʏ�U���̓����鋗��(�����W)��{�l
	double attackRange = 0.0f;

	//�U����
	float attack = 0.0f;
	//�h���
	float defence = 0.0f;
	//�ړ��X�s�[�h
	float moveSpeed = 0.0f;

	float hp = 0.0f;


};

