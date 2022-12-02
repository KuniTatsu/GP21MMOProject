#include "SkillManager.h"
#include"Skill.h"
#include"SpecialSkillEffect.h"

SkillManager* SkillManager::instance = nullptr;
SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

SkillManager* SkillManager::GetInstance()
{
	if (!instance) {
		instance = new SkillManager();
	}
	return instance;
}

void SkillManager::LoadSkillMaster()
{
}

std::shared_ptr<SpecialSkillEffect> SkillManager::SetSpecialSkillEffect(int skillId)
{
	return std::make_shared<SpecialSkillEffect>(skillId);
}

