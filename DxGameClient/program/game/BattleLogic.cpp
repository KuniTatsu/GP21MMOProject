#include "BattleLogic.h"
#include"GameManager.h"
#include<math.h>


BattleLogic* BattleLogic::instance = nullptr;


BattleLogic* BattleLogic::GetInstance()
{
	if (!instance) {
		instance = new BattleLogic();
	}
	return instance;
}

float BattleLogic::CalcDefaultDamage(float attack, float defence, int level, bool isSuccess, float coreDamage, float fixRatio)
{
	//基礎ダメージ=(((職レベル合計*2/5+2)*基礎攻撃力*p攻撃力/e防御力y)/50+2)*その他最終補正

	float damage = ((((((level * 2.0 / 5.0) + 2.0) * coreDamage * attack) / defence) / 50.0) + 2.0) * fixRatio;

	if (!isSuccess)damage /= 10;

	//小数第三位を四捨五入
	float fixDamage = std::round(damage * 100) / 100;

	return fixDamage;
}

bool BattleLogic::IsSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType)
{
	//強制有効ヒットかどうか判定
	if (IsForceSuccessAttack(AttackerData, DefenderData, attackType)) return true;

	//強制ヒットじゃなかった場合はそれぞれのattributeから成否を求める
	float successRatio = CalcSuccessRatio(AttackerData, DefenderData);
	//成功率が100%を上回っていたら成功
	if (successRatio >= 1.0f)return true;

	//0~100で数字を抽選し、successRatioより低ければ(0~successRatioなら)成功
	return GameManager::GetInstance()->CheckRandomNumberInOdds(successRatio);
}

BattleLogic::BattleLogic()
{
}

BattleLogic::~BattleLogic()
{
}

float BattleLogic::CalcSuccessRatio(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData)
{
	//有効率
	float successRatio = 0.0f;

	//attackerAttribute
	const auto& attackerAttribute = AttackerData->GetAttribute();
	//defenderAttrinbute
	const auto& defenderAttribute = DefenderData->GetAttribute();

	//attackerDEX
	const auto& attackDEX = attackerAttribute[static_cast<int>(ActorData::ATTRIBUTE::DEX)];
	//defenderDEX
	const auto& defendDEX = defenderAttribute[static_cast<int>(ActorData::ATTRIBUTE::DEX)];
	//attackerSPD
	const auto& attackSPD = attackerAttribute[static_cast<int>(ActorData::ATTRIBUTE::SPD)];
	//defenderSPD
	const auto& defendSPD = defenderAttribute[static_cast<int>(ActorData::ATTRIBUTE::SPD)];

	//第一段階 DEXの値とSPDの比から有効率の基礎値を求める
	float buf = static_cast<float>((attackDEX / defendSPD));

	//四捨五入を小数点6桁目で行い、計算誤差を消す
	successRatio = std::round(buf / 100000.0f) * 100000.0f;
	//この時点で100を超えていたら成功なのでその数値を返す
	if (successRatio >= 100.0f)return successRatio;

	//第二段階 SPDの比を加える
	float affectSPD = defendSPD / attackSPD;

	//1.0より小さいか大きいかで補正
	if (affectSPD <= 1.0f)affectSPD *= 10.0f;
	else affectSPD *= (-10.0f);

	//spdでの補正を加える
	successRatio += affectSPD;

	return successRatio;
}

bool BattleLogic::IsForceSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType)
{
	bool ret = false;

	//defendVIT*2<attackSTRなら無条件で成功(2倍以上なら確定で当たる)
	//物理攻撃ならVITとSTRを比べる
	if (attackType == static_cast<int>(ATTACKTYPE::MELEE)) {
		const auto& defendVIT = DefenderData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::VIT)];
		const auto& attackSTR = AttackerData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::STR)];

		if (defendVIT * 2.0 <= attackSTR)ret = true;
	}
	//魔法攻撃ならMIDとINTを比べる
	else {
		const auto& defendMID = DefenderData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::MID)];
		const auto& attackINT = AttackerData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::INT)];

		if (defendMID * 2.0 <= attackINT)ret = true;
	}
	return ret;
}
