#pragma once
#include"NPC.h"


class DisassemblyNPC :public NPC
{
public:
	DisassemblyNPC(float x, float y, int ghNum = 0, float distance = 64.0f);
	~DisassemblyNPC();

	void Update()override;
	void Draw(Camera* camera)override;
	void Init() override;
private:
	//メニューのページ番号
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//メニューの1ページに描画する最大数
	const int MAXDRAWNUM = 3;

	//エモーションのアニメ関連

	std::vector<std::vector<int>>emotions = {};

	int emoteActIndex = 0;

	int emoteActWait = 0;

	const int emoteActSpeed = 30;

	int emoteDrawGh = 0;

	int returnKey = 0;

	int escKey = 0;


};

