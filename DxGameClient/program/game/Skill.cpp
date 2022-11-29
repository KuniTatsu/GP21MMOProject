#include "Skill.h"
#include"SpecialSkillEffect.h"
#include"SkillManager.h"

Skill::Skill()
{
}

Skill::~Skill()
{
}

void Skill::UseSkill(float preDealDamage, float preTakeDamage)
{
}

void Skill::SetSkillData(int skillId, int type, float time, float addDamage, float substractDamage,
	float increaseDamage, float decreaseDamage, float subtractDamage, float divideDamage, bool isSpecial, int specialId)
{
	id = skillId;

	skillType = type;

	affectedTime = time;

	
	defaultAddDamage = addDamage;
	
	defaultSubtractDamage = substractDamage;

	defaultIncreaseDamageRate = increaseDamage;

	defaultDecreaseDamageRate = decreaseDamage;

	subtractTakeDamage = subtractDamage;

	divideTakeDamage = divideDamage;

	if (isSpecial) {

		spEffect = SkillManager::GetInstance()->SetSpecialSkillEffect(specialId);
	}


}
