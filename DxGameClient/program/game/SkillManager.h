/*
スキルのマスターデータを保持するクラス
データの取得関数を持つ
*/
#pragma once
#include<memory>
#include<vector>
class Skill;
class SpecialSkillEffect;

class SkillManager
{
public:
	
	// インスタンスの取得
	static SkillManager* GetInstance();

	void LoadSkillMaster();

	std::shared_ptr<SpecialSkillEffect> SetSpecialSkillEffect(int skillId);

private:
	SkillManager();
	~SkillManager();

private:

	std::vector<Skill> skillMaster;

	static SkillManager* instance;
};

