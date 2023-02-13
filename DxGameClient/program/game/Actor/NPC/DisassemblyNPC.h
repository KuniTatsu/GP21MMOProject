#pragma once
#include"NPC.h"


class DisassemblyNPC :NPC
{
public:
	DisassemblyNPC(float x, float y, int ghNum = 0, float distance = 64.0f);
	~DisassemblyNPC();

private:
	//メニューのページ番号
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//メニューの1ページに描画する最大数
	const int MAXDRAWNUM = 3;
};

