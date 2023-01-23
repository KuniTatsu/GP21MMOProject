#pragma once
#include<string>
#include<vector>


class GameManager;
class Connect
{
public:
	Connect();
	~Connect();


	int ConnectServer();
	//�`���b�g���b�Z�[�W�̑��M
	void SendClientMessage(std::string sendMessage);
	//�`���b�g���b�Z�[�W�̎�M
	const std::string GetServerMessage();

	//���[�U�[�o�^�֐�
	void EntryServer(std::string playerName);

	//���[�U�[�o�^���擾�֐�
	void GetEntryUserId();

	//�N���C�A���g�L�����N�^�[�̈ʒu���W�Ɖ摜�n���h���ԍ��𑗂�֐�
	void SendClientPlayerInfo(float x, float y, int dir, int isCreated = 0, int ghNum = 0, int isDebug = 0);

	//�N���C�A���g�L�����N�^�[�̈ʒu���W


	//�������T�[�o�[���甲���邱�Ƃ�m�点��֐�
	void SendExitServer();

private:

	//�T�[�o�[��IP�A�h���X
	//std::string host = "127.0.0.1";
	//std::string host = "192.168.80.129";
	std::string host = "10.76.14.195";

	//�|�[�g
	const std::string  port = "9001"; //80


	std::string	myLastMessage = "";


	GameManager* gManager = nullptr;

};

