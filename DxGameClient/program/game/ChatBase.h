#pragma once
#include<string>
#include<vector>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;

class ChatBase
{
public:
	ChatBase();
	~ChatBase();

	//���ݓ��͒��̕������`�悷��֐�
	void DrawWritingMessage();
	//���͊֐�
	void Write();

	//���͊�����̕������`�悷��֐�
	void DrawAllMessage();

	//�X�V�֐�
	void Update();

	//�`��֐�
	void Draw();

	int g_InputHandle;

	

private:
	//���͂������������Ƃ̕�����
	std::vector<std::string>savedMessage;
	//���͒��̕�����
	std::string bufMessage;

	char buffer[100] = {};

	tnl::Sequence<ChatBase> sequence =
		tnl::Sequence<ChatBase>(this, &ChatBase::SeqWait);

	bool SeqDrawMessage(const float deltatime);
	bool SeqWait(const float deltatime);

	void CreateKeyInput();


	GameManager* gManager = nullptr;

};
