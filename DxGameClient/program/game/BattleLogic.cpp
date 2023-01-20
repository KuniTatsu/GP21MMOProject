#include "BattleLogic.h"


BattleLogic* BattleLogic::instance = nullptr;


BattleLogic* BattleLogic::GetInstance()
{
	if (!instance) {
		instance = new BattleLogic();
	}
	return instance;
}

float BattleLogic::CalcDefaultDamage(float attack, float defence, int level, float coreDamage, float fixRatio)
{
	//��b�_���[�W=(((�E���x�����v*2/5+2)*��b�U����*p�U����/e�h���y)/50+2)*���̑��ŏI�␳

	float damage = ((((((level * 2.0 / 5.0) + 2.0) * coreDamage * attack) / defence) / 50.0) + 2.0) * fixRatio;

	//������O�ʂ��l�̌ܓ�
	float fixDamage = std::round(damage * 100) / 100;

	return fixDamage;
}

bool BattleLogic::isSuccessAttack(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData)
{
	bool isSuccess = false;

	

	


	float successRatio = calcSuccessRatio(AttackerData, defenderData);

	return false;
}

BattleLogic::BattleLogic()
{
}

BattleLogic::~BattleLogic()
{
}

float BattleLogic::calcSuccessRatio(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData)
{



	return 0.0f;
}
