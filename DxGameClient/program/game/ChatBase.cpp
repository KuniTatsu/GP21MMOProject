#include "ChatBase.h"
#include"GameManager.h"
#include"Connect.h"
#include<stdio.h>
/*
	�K�v�v��
	�E�����̓��͂��ł���
	�E��ʓ��ɓ��͒��̕����񂪕\�������
	�EEnter�L�[�����������_�ŕ\������Ă��镶���񂪔z��ɓ���A�ۊǂ����
*/

using namespace std;
/*
std::string SjistoUTF8(std::string srcSjis)
{
	//Unicode�֕ϊ���̕����񒷂𓾂�
	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);

	//�K�v�ȕ�����Unicode������̃o�b�t�@���m��
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//ShiftJIS����Unicode�֕ϊ�
	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);


	//UTF8�֕ϊ���̕����񒷂𓾂�
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//�K�v�ȕ�����UTF8������̃o�b�t�@���m��
	char* bufUTF8 = new char[lengthUTF8];

	memset(bufUTF8, 0, sizeof(char) * lengthUTF8);

	//Unicode����UTF8�֕ϊ�
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode - 1, bufUTF8, lengthUTF8, NULL, NULL);


	std::string strUTF8(bufUTF8);

	delete[] bufUnicode;
	delete[] bufUTF8;

	return strUTF8;
}
*/

ChatBase::ChatBase()
{
	gManager = GameManager::GetInstance();

	connect = new Connect();

	////�T�[�o�[�ɐڑ�
	//int result = connect->ConnectServer();

	//if (result == 0) {
	//	tnl::DebugTrace("����");
	//}
	//else {
	//	tnl::DebugTrace("���s");
	//}
	//tnl::DebugTrace("\n");


	if (!init) {

		//string name = SjistoUTF8("�v���C���[1");

		connect->EntryServer("�v���C���[1");

		connect->GetEntryUserId();

		init = true;
	}


	string test = "����ɂ���";

	string utf = gManager->SjistoUTF8(test);

	//���b�Z�[�W�𑗐M
	connect->SendClientMessage(utf);

	connect->GetServerMessage(hoge);



	//�`���b�g���̃X�N���[���𐶐�
	chatArea = MakeScreen(340, 400, TRUE);

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
	//�`���b�g��`�悷��G���A�����肷��
	SetDrawScreen(chatArea);
	SetBackgroundColor(32, 32, 32, 180);
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);

	//�ۑ����ꂽ���b�Z�[�W����ŐV��10�݂̂�`�悷��
	//�󂶂�Ȃ�������
	if (!savedMessage.empty()) {
		//auto hoge = savedMessage.end();

		int arrayNum = savedMessage.size();
		for (int i = 0; i < 10; ++i) {

			if (i + 1 > arrayNum)break;

			auto hoge = std::to_string(i) + "�Ԗڂ̃��b�Z�[�W��`�悵����";
			tnl::DebugTrace(hoge.c_str());
			tnl::DebugTrace("\n");

			if (arrayNum < 10) {
				DrawStringEx(20, 10 + (i * 20), -1, savedMessage[i].c_str());
			}
			else {
				int messageNum = i + (arrayNum - 10);

				DrawStringEx(20, 10 + (i * 20), -1, savedMessage[messageNum].c_str());
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	/*for (int i = 0; i < savedMessage.size(); ++i) {
		DrawStringEx(20, 10 + i * 20, -1, savedMessage[i].c_str());
	}*/

	//���̉�ʂւ̏o�͂ɐ؂�ւ�
	SetDrawScreen(DX_SCREEN_BACK);
	//�`���b�g��`�悷��G���A���ꖇ�G�Ƃ��ĕ`�悷��
	DrawGraph(10, 300, chatArea, true);

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
		// ���͕����������������
		SetKeyInputString("", g_InputHandle);
	}

	//Write();
	int hoge = CheckKeyInput(g_InputHandle);

	if (hoge != 0) {

		//����I�����̂݃��b�Z�[�W��ۑ��A���M����
		if (hoge == 1) {
			//���͂��ꂽ�������ۑ�����
			GetKeyInputString(buffer, g_InputHandle);

			std::string buf = buffer;

			tnl::DebugTrace("-------------------");
			tnl::DebugTrace("\n");

			//�󔒕����Ȃ�o�^���Ȃ�
			if (buf != "") {
				savedMessage.emplace_back(buf);
				//�T�[�o�[��buf�𑗂�
				//connect->SendClientMessage(buf);
			}

		}

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
