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
	//基礎ダメージ=(((職レベル合計*2/5+2)*基礎攻撃力*p攻撃力/e防御力y)/50+2)*その他最終補正

	float damage = ((((((level * 2.0 / 5.0) + 2.0) * coreDamage * attack) / defence) / 50.0) + 2.0) * fixRatio;

	//小数第三位を四捨五入
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
