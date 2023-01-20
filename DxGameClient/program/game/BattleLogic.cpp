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
	//��b�_���[�W=(((�E���x�����v*2/5+2)*��b�U����*p�U����/e�h���y)/50+2)*���̑��ŏI�␳

	float damage = ((((((level * 2.0 / 5.0) + 2.0) * coreDamage * attack) / defence) / 50.0) + 2.0) * fixRatio;

	if (!isSuccess)damage /= 10;

	//������O�ʂ��l�̌ܓ�
	float fixDamage = std::round(damage * 100) / 100;

	return fixDamage;
}

bool BattleLogic::IsSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType)
{
	//�����L���q�b�g���ǂ�������
	if (IsForceSuccessAttack(AttackerData, DefenderData, attackType)) return true;

	//�����q�b�g����Ȃ������ꍇ�͂��ꂼ���attribute���琬�ۂ����߂�
	float successRatio = CalcSuccessRatio(AttackerData, DefenderData);
	//��������100%�������Ă����琬��
	if (successRatio >= 1.0f)return true;

	//0~100�Ő����𒊑I���AsuccessRatio���Ⴏ���(0~successRatio�Ȃ�)����
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
	//�L����
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

	//���i�K DEX�̒l��SPD�̔䂩��L�����̊�b�l�����߂�
	float buf = static_cast<float>((attackDEX / defendSPD));

	//�l�̌ܓ��������_6���ڂōs���A�v�Z�덷������
	successRatio = std::round(buf / 100000.0f) * 100000.0f;
	//���̎��_��100�𒴂��Ă����琬���Ȃ̂ł��̐��l��Ԃ�
	if (successRatio >= 100.0f)return successRatio;

	//���i�K SPD�̔��������
	float affectSPD = defendSPD / attackSPD;

	//1.0��菬�������傫�����ŕ␳
	if (affectSPD <= 1.0f)affectSPD *= 10.0f;
	else affectSPD *= (-10.0f);

	//spd�ł̕␳��������
	successRatio += affectSPD;

	return successRatio;
}

bool BattleLogic::IsForceSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType)
{
	bool ret = false;

	//defendVIT*2<attackSTR�Ȃ疳�����Ő���(2�{�ȏ�Ȃ�m��œ�����)
	//�����U���Ȃ�VIT��STR���ׂ�
	if (attackType == static_cast<int>(ATTACKTYPE::MELEE)) {
		const auto& defendVIT = DefenderData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::VIT)];
		const auto& attackSTR = AttackerData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::STR)];

		if (defendVIT * 2.0 <= attackSTR)ret = true;
	}
	//���@�U���Ȃ�MID��INT���ׂ�
	else {
		const auto& defendMID = DefenderData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::MID)];
		const auto& attackINT = AttackerData->GetAttribute()[static_cast<int>(ActorData::ATTRIBUTE::INT)];

		if (defendMID * 2.0 <= attackINT)ret = true;
	}
	return ret;
}
