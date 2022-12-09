/*
�X�L���̃}�X�^�[�f�[�^��ێ�����N���X
�f�[�^�̎擾�֐�������
*/
#pragma once
#include<memory>
#include<vector>
class Skill;
class SpecialSkillEffect;

class SkillManager
{
public:
	
	// �C���X�^���X�̎擾
	static SkillManager* GetInstance();

	void LoadSkillMaster();

	std::shared_ptr<SpecialSkillEffect> SetSpecialSkillEffect(int skillId);

private:
	SkillManager();
	~SkillManager();

private:

	std::vector<std::shared_ptr<Skill>> skillMaster;

	static SkillManager* instance;
};

