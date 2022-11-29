#include "SpecialSkillEffect.h"

SpecialSkillEffect::SpecialSkillEffect(int skillID)
{

}

SpecialSkillEffect::~SpecialSkillEffect()
{
}

std::function<void()> SpecialSkillEffect::DoEvent(std::string key)
{
	auto it = exEffects.find(key);
	if (it != exEffects.end()) {
		return exEffects[key];
	}
	return std::function<void()>();
}
std::function<tnl::Vector3(tnl::Vector3)> SpecialSkillEffect::DoPosEvent(std::string key)
{
	auto it = exPosEffect.find(key);
	if (it != exPosEffect.end()) {
		return exPosEffect[key];
	}
	return std::function<tnl::Vector3(tnl::Vector3)>();
}

void SpecialSkillEffect::SetMap(std::string key, void func())
{
	//ì‚Á‚½Œø‰Ê‚Ìˆ—ŠÖ”‚ğmap‚Éû”[‚·‚é
	exEffects.insert(std::make_pair(key, func));
}

void SpecialSkillEffect::SetPosMap(std::string key, tnl::Vector3 func(tnl::Vector3))
{
	//ì‚Á‚½Œø‰Ê‚Ìˆ—ŠÖ”‚ğmap‚Éû”[‚·‚é
	exPosEffect.insert(std::make_pair(key, func));

}