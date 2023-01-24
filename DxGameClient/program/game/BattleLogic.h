#pragma once
#include"../dxlib_ext/dxlib_ext.h"
#include"Actor/ActorData.h"
#include<memory>


class BattleLogic
{
public:
	// �C���X�^���X�̎擾
	static BattleLogic* GetInstance();


	//�_���[�W�v�Z args1:�U���� args2:�h��� args3:�E���x�����v args4:��b�_���[�W �f�t�H���g�͒ʏ�U���̒l args5:�ŏI�␳
	double CalcDefaultDamage(float attack, float defence, int level, bool isSuccess, float coreDamage = 50.0f, float fixRatio = 1.0f);

	//�L���ȍU�����ǂ������肷��֐�
	bool IsSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType);




public:
	enum class ATTACKTYPE :uint32_t {
		MELEE,
		RANGE,
		MAX
	};

private:

	BattleLogic();
	~BattleLogic();

	//�L�����v�Z
	float CalcSuccessRatio(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData);

	//�U��������������
	bool IsForceSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType);


private:
	static BattleLogic* instance;


};

