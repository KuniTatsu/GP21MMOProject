#pragma once
#include"NPC.h"


class DisassemblyNPC :NPC
{
public:
	DisassemblyNPC(float x, float y, int ghNum = 0, float distance = 64.0f);
	~DisassemblyNPC();

private:
	//���j���[�̃y�[�W�ԍ�
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//���j���[��1�y�[�W�ɕ`�悷��ő吔
	const int MAXDRAWNUM = 3;
};

