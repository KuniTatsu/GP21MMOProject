/*
�����A�C�e���̃N���X
	�A�C�e���N���X���p������
	�����A�C�e���ł��������Ȃ��f�[�^�͂�����Ŏ���
	�e��X�e�[�^�X�Ȃ�
*/


#pragma once
#include"Item.h"
#include<vector>

//intData[0], intData[1], stringData[0], intData[2], intData[3], intData[4],
//stringData[1], intData[5], intData[6], stringData[2], intData[7], intData[8], intData[9], intData[10], 0

class EquipItem:public Item
{
public:
	EquipItem();
	~EquipItem();

private:

public:
	std::vector<int> GetAllIntData();
	bool GetIsEquiped();
	void DrawEquipItemStatus(int x, int y, int GetSubId);
	int GetSubId();
};

