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
	//Šî‘bƒ_ƒ[ƒW=(((EƒŒƒxƒ‹‡Œv*2/5+2)*Šî‘bUŒ‚—Í*pUŒ‚—Í/e–hŒä—Íy)/50+2)*‚»‚Ì‘¼ÅI•â³

	float damage = ((((((level * 2.0 / 5.0) + 2.0) * coreDamage * attack) / defence) / 50.0) + 2.0) * fixRatio;

	//¬”‘æOˆÊ‚ğlÌŒÜ“ü
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
