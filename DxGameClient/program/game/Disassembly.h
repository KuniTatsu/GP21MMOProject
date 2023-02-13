#pragma once
//���[�A�C�e������f�ރA�C�e���𐶐�����@�\�N���X

#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<unordered_map>

class Inventory;
class DisassemblyData;

class Disassembly
{
public:

	// �C���X�^���X�̎擾
	static Disassembly* GetInstance();

	//���[Id���󂯎��A�����̃C���x���g���ɑf�ރA�C�e����ǉ�����֐� --�A�C�e���Ɏ��[ID�Ƃ����f�[�^�����邱�Ƃ�O��
	void DisassemblyDeadBody(int deadId, std::shared_ptr<Inventory>inventory);


private:
	Disassembly();
	~Disassembly();

	//���[Id�Ɖ�̌�A�C�e���̃}�X�^�[��Csv����ǂݎ��
	void LoadDisassemblyResult();

private:
	static Disassembly* instance;

	std::vector<std::shared_ptr<DisassemblyData>>disassemblyMaster;

};


class DisassemblyData
{
public:
	DisassemblyData(int id,std::string Name,int id1,int weight1, int id2, int weight2, int id3, int weight3, int id4, int weight4);
	~DisassemblyData();

public:

	//���[Id	���O	��̌�A�C�e��Id1	�E�F�C�g1	��̌�A�C�e��Id2	�E�F�C�g2	��̌�A�C�e��Id3	�E�F�C�g3	��̌�A�C�e��Id4	�E�F�C�g4

	int fromId = 0;
	std::string name;
	std::unordered_map<int, int>disassemblyResult;

};
