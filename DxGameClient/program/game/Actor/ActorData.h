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


private:

	//�ʏ�U���̓����鋗��(�����W)��{�l
	double attackRange = 0.0f;



};

