#pragma once
#include<string>
#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class Connect;

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

	//�󂯎����string�f�[�^���p�[�X���Ċi�[����֐�
	void ParseMessage(const std::string message);

	//�󂯎����string�������chat��vector�Ɋi�[����֐�
	void InsertStringToChatVector(const std::string chat);

	//�T�[�o�[����󂯎�������b�Z�[�W��o�^����֐�
	inline void SetGetMessage(const std::string serverMessage) {
		getMessage = serverMessage;
	}

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

	//�Ō�Ɏ������������`���b�g���b�Z�[�W
	std::string	myLastMessage = "";

	//�e�X�g�p
	std::vector<std::string>hoge;

	//�T�[�o�[����󂯎����������
	std::string getMessage = "";


	//�`���b�g��
	int chatArea = 0;;

	char buffer[100] = {};

	bool init = false;


	tnl::Sequence<ChatBase> sequence =
		tnl::Sequence<ChatBase>(this, &ChatBase::SeqWait);

	bool SeqDrawMessage(const float deltatime);
	bool SeqWait(const float deltatime);

	void CreateKeyInput();


	GameManager* gManager = nullptr;

	std::shared_ptr<Connect> connect = nullptr;

};
