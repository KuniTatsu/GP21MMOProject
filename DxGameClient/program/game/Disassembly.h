#pragma once
//���[�A�C�e������f�ރA�C�e���𐶐�����@�\�N���X

#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<unordered_map>

class MaterialConverter;

class Disassembly
{
public:

	// �C���X�^���X�̎擾
	static Disassembly* GetInstance();

	//���[Id���󂯎��A�����̃C���x���g���ɑf�ރA�C�e����ǉ�����֐� --�A�C�e���Ɏ��[ID�Ƃ����f�[�^�����邱�Ƃ�O��
	void DisassemblyDeadBody(int deadId);


private:
	Disassembly();
	~Disassembly();



private:
	static Disassembly* instance;

	//���[ID�Ə������킹���I�u�W�F�N�g�̓��ꕨ
	std::vector<std::shared_ptr<MaterialConverter>> convertMaster;

};


