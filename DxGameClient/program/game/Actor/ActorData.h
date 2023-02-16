/*Actor�̊�{�f�[�^���Ǘ�����N���X
	�X�e�[�^�X��摜�Ȃǂ��܂�
	�ʂ̓��ʂȃX�e�[�^�X��������ꍇ�͌p����Ŏ���������j��
*/
#pragma once
#include<vector>
#include<string>

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
		attackWidth = static_cast<float>(setWidth);
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

	void SetAllStatus(float Attack, float Defence, float MoveSpeed);

	void SetAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	inline const std::vector<int>& GetAttribute() {
		return attribute;
	}
	inline int GetLevel() {
		return level;
	}

	inline bool UpdateHp(double moveHp) {
		bool ret = false;
		HP += static_cast<float>(moveHp);
		if (HP < 0) {
			HP = 0;
			ret = true;
		}
		return ret;
	}

	inline void SetHP(float startHP) {
		HP = startHP;
	}

	inline const float GetHP() {
		return HP;
	}
	//HP�ȊO�̃X�e�[�^�X��Ԃ��֐�
	inline const std::vector<float>& GetMainStatus() {
		return mainStatus;
	}

	//�X�e�[�^�X�̖��O��Ԃ��֐�
	inline const std::vector<std::string>& GetStatusName() {
		return STATUSNAME;
	}

	inline void setMoveSpeed(float fixMoveSpeed) {
		moveSpeed = fixMoveSpeed;
	}

	//�U���͂Ȃǂ̊�{�X�e�[�^�X�̌v�Z�Ƒ��
	void CalcMainStatus();

	//HP�ȊO�̃X�e�[�^�X���v�Z���đ��
	void CalcDefaultStatus();

public:
	enum class ATTRIBUTE :uint32_t {
		STR,
		VIT,
		INT,
		MID,
		SPD,
		DEX,
		MAX
	};


private:

private:

	//�ʏ�U���̓����鋗��(�����W)��{�l
	float attackRange = 50.0f;

	//status
	std::vector<float>mainStatus;

	//�U����
	float attack = 0.0f;
	//���@�U����
	float mgAttack = 0.0f;
	//�h���
	float defence = 0.0f;
	//���@�h���
	float mgDefence = 0.0f;
	//�ړ��X�s�[�h
	float moveSpeed = 0.0f;

	float hp = 0.0f;
	//�ʏ�U���̓����鉡��  �f�t�H���g�̓L�����摜�Ɠ�����
	float attackWidth = 32.0f;
	//�b���HP
	float HP = 0.0f;

	//attribute
	std::vector<int>attribute;

	int str = 0;
	int vit = 0;
	int intelligence = 0;
	int mid = 0;
	int spd = 0;
	int dex = 0;

	int level = 100;

	const std::vector<std::string>STATUSNAME = { "�����U��","�����h��","���@�U��","���@���","�ړ��X�s�[�h" };
};

