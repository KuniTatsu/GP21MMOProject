#pragma once

//�菕��NPC
//�q���g�����ꂽ��A�C�e�������ꂽ�肷��

#include"NPC.h"



class SupportNPC :public NPC
{
public:
	SupportNPC(float x, float y, int ghNum = 0, float distance = 64.0f);
	~SupportNPC();

	void Update()override;
	void Draw(Camera* camera)override;
	void Init() override;

	//�߂��Ƀv���C���[�����邩�Ԃ��֐� GameManager��ʂ���player����Ă�
	bool CheckNearNPC(float PlayerX, float PlayerY);

public:


private:
	//NPC���b���q���g��Csv���烍�[�h
	bool loadNPCHint();


	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<SupportNPC> mainSequence =
		tnl::Sequence<SupportNPC>(this, &SupportNPC::SeqWait);

	//�e�V�[�N�G���X��Update�֐�
	bool SeqWait(const float DeltaTime);
	bool SeqFirstMenu(const float DeltaTime);
	bool SeqHint(const float DeltaTime);

	//�V�[�N�G���X���Ƃ̕`��֐�
	void DrawWaitSequence();
	void DrawFirstMenuSequence();
	void DrawHintSequence();

	//���݂̃V�[�N�G���X�̕`��֐�
	const std::function< void(SupportNPC*) > DRAWSEQUENCE[3] = { &SupportNPC::DrawWaitSequence, &SupportNPC::DrawFirstMenuSequence,&SupportNPC::DrawHintSequence };

	//�V�[�N�G���X�ꗗ
	enum class SEQUENCE :uint32_t {
		WAIT,
		FIRSTMENU,
		HINT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::FIRSTMENU;

	//�V�[�N�G���X�ύX�֐�
	bool ChangeSequence(SEQUENCE NextSeq);

private:

	////npc�̍��ڂ��Ƃ̃q���g����
	//std::vector<std::string> hint;

	//����npc�̘b���������鋗��(���a)
	float canHearDistance = 64.0f;//�f�t�H���g�̓L�����Q��

	//�߂���player�����邩�ǂ���
	bool isNearPlayer = false;

	//���j���[�ԍ�
	int cursorNum = 0;

	//���j���[�̃y�[�W�ԍ�
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//���j���[��1�y�[�W�ɕ`�悷��ő吔
	const int MAXDRAWNUM = 3;

};

