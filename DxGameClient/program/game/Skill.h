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
	//スキルId
	int id = 0;

	//スキルタイプ デフォルトはダメージ
	int skillType = static_cast<int>(SKILLTYPE::DAMAGE);

	//効果時間 バフ系スキルのみ使用
	float affectedTime = 0.0f;

	//----------与えるダメージに関する値----------//

	//スキル発動時に加算する基礎ダメージ値
	float defaultAddDamage = 0.0f;
	//スキル発動時に減算する基礎ダメージ値
	float defaultSubtractDamage = 0.0f;

	//スキル発動時に乗算する基礎ダメージ倍率
	float defaultIncreaseDamageRate = 0.0f;
	//スキル発動時に除算する基礎ダメージ倍率
	float defaultDecreaseDamageRate = 0.0f;

	//----------受けるダメージに関する値----------//

	//スキル発動中に受けるダメージを減算する値
	float subtractTakeDamage = 0.0f;
	//スキル発動中に受けるダメージを除算する値
	float divideTakeDamage = 0.0f;

	//特殊な動作をするスキルの場合に生成するクラスポインタ
	std::shared_ptr<SpecialSkillEffect> spEffect = nullptr;
};

