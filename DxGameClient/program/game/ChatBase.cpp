#include "ChatBase.h"
#include"GameManager.h"
#include<stdio.h>
/*
	�K�v�v��
	�E�����̓��͂��ł���
	�E��ʓ��ɓ��͒��̕����񂪕\�������
	�EEnter�L�[�����������_�ŕ\������Ă��镶���񂪔z��ɓ���A�ۊǂ����
*/


ChatBase::ChatBase()
{
	gManager = GameManager::GetInstance();

	// �L�[���̓n���h�������(�L�����Z������S�p�����L�萔�l���͂Ȃ�)
	CreateKeyInput();
	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(g_InputHandle);
}

ChatBase::~ChatBase()
{
	DeleteKeyInput(g_InputHandle);
}

void ChatBase::DrawWritingMessage()
{
	//DrawStringEx(400, 500, -1, bufMessage.c_str());
	// ���̓��[�h��`��
	DrawKeyInputModeString(640, 480);

	// ���͓r���̕������`��
	DrawKeyInputString(0, 0, g_InputHandle);
}

void ChatBase::Write()
{

}

void ChatBase::DrawAllMessage()
{
	for (int i = 0; i < savedMessage.size(); ++i) {
		DrawStringEx(100, 100 + i * 20, -1, savedMessage[i].c_str());
	}
}

void ChatBase::Update()
{
	sequence.update(gManager->deltaTime);
}

void ChatBase::Draw()
{
	DrawAllMessage();

}

bool ChatBase::SeqDrawMessage(const float deltatime)
{
	if (sequence.isStart()) {
		ClearInputCharBuf();
	}


	//Write();
	int hoge = CheckKeyInput(g_InputHandle);

	if (hoge != 0) {
		GetKeyInputString(buffer,g_InputHandle);

		std::string buf = buffer;
		savedMessage.emplace_back(buf);

		// ���͕����������������
		SetKeyInputString("", g_InputHandle);

		// �ēx�C���v�b�g�n���h�����A�N�e�B�u�ɂ���
		SetActiveKeyInput(g_InputHandle);

		//�V�[�N�G���X���ړ�����
		sequence.change(&ChatBase::SeqWait);
	}
	else {
		DrawWritingMessage();
	}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

	//	//�������o�^
	//	savedMessage.emplace_back(bufMessage);
	//	bufMessage = "";
	//	//�V�[�N�G���X���ړ�����
	//	sequence.change(&ChatBase::SeqWait);
	//}
	return true;
}

bool ChatBase::SeqWait(const float deltatime)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {		
		//�V�[�N�G���X���ړ�����
		sequence.change(&ChatBase::SeqDrawMessage);
	}

	return true;
}

void ChatBase::CreateKeyInput()
{
	if (g_InputHandle != 0)return;
	// �L�[���̓n���h�������(�L�����Z������S�p�����L�萔�l���͂Ȃ�)
	g_InputHandle = MakeKeyInput(30, true, false, false);
}
