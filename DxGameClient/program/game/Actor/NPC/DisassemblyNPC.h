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
	//���j���[�̃y�[�W�ԍ�
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//���j���[��1�y�[�W�ɕ`�悷��ő吔
	const int MAXDRAWNUM = 3;

	//�G���[�V�����̃A�j���֘A

	std::vector<std::vector<int>>emotions = {};

	int emoteActIndex = 0;

	int emoteActWait = 0;

	const int emoteActSpeed = 30;

	int emoteDrawGh = 0;

	int returnKey = 0;

	int escKey = 0;


};

