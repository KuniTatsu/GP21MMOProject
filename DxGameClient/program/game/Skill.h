#pragma once
#include<memory>

class SpecialSkillEffect;

class Skill
{
public:
	Skill();
	~Skill();

	void UseSkill(float preDealDamage = 0.0f, float preTakeDamage = 0.0f);

	void SetSkillData(int skillId, int type, float time, float addDamage, float substractDamage,
		float increaseDamage, float decreaseDamage, float subtractDamage, float divideDamage, bool isSpecial, int specialId = 0);

	static enum class SKILLTYPE {
		DAMAGE,
		BUFF,
		EX,
		MAX
	};

private:
	void UseDealDamageSkill(float preDealDamage);

	void UseDecreaseDamageSkill(float preTakeDamage);
private:
	//�X�L��Id
	int id = 0;

	//�X�L���^�C�v �f�t�H���g�̓_���[�W
	int skillType = static_cast<int>(SKILLTYPE::DAMAGE);

	//���ʎ��� �o�t�n�X�L���̂ݎg�p
	float affectedTime = 0.0f;

	//----------�^����_���[�W�Ɋւ���l----------//

	//�X�L���������ɉ��Z�����b�_���[�W�l
	float defaultAddDamage = 0.0f;
	//�X�L���������Ɍ��Z�����b�_���[�W�l
	float defaultSubtractDamage = 0.0f;

	//�X�L���������ɏ�Z�����b�_���[�W�{��
	float defaultIncreaseDamageRate = 0.0f;
	//�X�L���������ɏ��Z�����b�_���[�W�{��
	float defaultDecreaseDamageRate = 0.0f;

	//----------�󂯂�_���[�W�Ɋւ���l----------//

	//�X�L���������Ɏ󂯂�_���[�W�����Z����l
	float subtractTakeDamage = 0.0f;
	//�X�L���������Ɏ󂯂�_���[�W�����Z����l
	float divideTakeDamage = 0.0f;

	//����ȓ��������X�L���̏ꍇ�ɐ�������N���X�|�C���^
	std::shared_ptr<SpecialSkillEffect> spEffect = nullptr;
};

