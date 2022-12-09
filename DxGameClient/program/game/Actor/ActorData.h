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
	inline float GetAttackRange() {
		return attackRange;
	}
	inline void SetAttackRange(float setRange) {
		if (setRange < 0.0)return;
		attackRange = setRange;
	}
	//������getter,setter
	inline double GetAttackWidth() {
		return attackWidth;
	}
	inline void SetAttackRange(double setWidth) {
		if (setWidth < 0.0)return;
		attackWidth = setWidth;
	}


private:

	//�ʏ�U���̓����鋗��(�����W)��{�l
	float attackRange = 100.0f;

	//�ʏ�U���̓����鉡��  �f�t�H���g�̓L�����摜�Ɠ�����
	float attackWidth = 32.0f;


};

