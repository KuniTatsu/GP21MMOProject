/*
����ȓ�����s���X�L���̏�������������N���X
Skill�N���X�Ƀ|�C���^�ϐ��Ƃ��Ď�������
SkillManager����o�^����
�C���X�^���X�������Ɏg�p����֐���I������
*/

//������ƍ�肪�����Ȃ̂ő����Ⴄ���@�Ŏ�������Ǝv��

#pragma once
#include<functional>
#include<unordered_map>
#include<vector>
#include<string>
#include "../dxlib_ext/dxlib_ext.h"
#include<memory>

class SpecialSkillEffect
{
public:
	SpecialSkillEffect(int skillID);
	~SpecialSkillEffect();

	inline void SetSkillName(std::string name) {
		skillName = name;
	}

	//key�ň����Ԃ�l�Ȃ��̊֐����������A���s����֐�
	std::function<void()> DoEvent(std::string key);
	//key�ň���,�Ԃ�ltnl::Vector3�̊֐����������A���s����֐�
	std::function<tnl::Vector3(tnl::Vector3)> DoPosEvent(std::string key);

private:
	//----------���s�n----------//

	//�e����ꏈ���̌��ʂ����s����֐�����ꂽmap(�����Ԃ�l�Ȃ�)
	std::unordered_map<std::string, std::function<void()>> exEffects;

	//�e����ꏈ���̌��ʂ����s����֐�����ꂽmap(����,�Ԃ�l tnl::vector3)
	std::unordered_map<std::string, std::function<tnl::Vector3(tnl::Vector3)>> exPosEffect;

	//�o�^
	void SetMap(std::string key, void func());
	void SetPosMap(std::string key, tnl::Vector3 func(tnl::Vector3));


	//----------�e��X�L���̏����֐�----------//
	tnl::Vector3 MoveForward(tnl::Vector3 pos);



private:
	//���ۂɔ�������X�L���̖��O �����p�̃L�[�ɂȂ邽�ߗv����
	std::string skillName = "";
};

