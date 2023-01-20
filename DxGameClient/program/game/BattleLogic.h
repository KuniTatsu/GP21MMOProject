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
	float CalcDefaultDamage(float attack, float defence, int level, float coreDamage = 50.0f, float fixRatio = 1.0f);

	//�L���ȍU�����ǂ������肷��֐�
	bool isSuccessAttack(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData);

	
	

public:


private:

	BattleLogic();
	~BattleLogic();

	//�L�����v�Z
	float calcSuccessRatio(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData);

private:
	static BattleLogic* instance;


};

