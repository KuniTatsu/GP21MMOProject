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

	//�A�C�e���̃t�B�[���h�ւ̃h���b�v�󋵂����L����֐�
	void SendClientFieldItemInfo(float x, float y, int itemId);

	//�N���C�A���g�L�����N�^�[�̈ʒu���W�Ɖ摜�n���h���ԍ��𑗂�֐�
	void SendClientPlayerInfo(float x, float y, int dir,float HP, int isCreated = 0, int ghNum = 0, int isDebug = 0);
	
	//�N���C�A���g�L�����N�^�[�̏����X�e�[�^�X�̃T�[�o�[�o�^
	void SendClientPlayerInitInfo(float x, float y, float HP,int ghNum);

	//�N���C�A���g�L�����N�^�[�̃X�e�[�^�X�ϓ��̋��L
	void SendClientPlayerStatus(float moveHP);

	//�N���C�A���g�L�����N�^�[�̎��S�󋵂̋��L
	void SendClientPlayerIsDead(int idDead = 1);

	//�N���C�A���g�L�����N�^�[�����������U���̃G�t�F�N�g�̍��W�ƃG�t�F�N�g�ԍ��𑗂�֐�
	void SendClientAttackEffectInfo(float x, float y, int effectNum, int dir = 0);

	//�G�l�~�[�̈ʒu���W�̋��L
	void SendClientEnemyInfo(float x, float y, int dir, int identificationNum,int type);

	//�G�l�~�[�̃X�e�[�^�X�ϓ��̋��L
	void SendClientEnemyStatus(int identificationNum,float moveHP);

	//�G�l�~�[�̎��S�󋵂̋��L
	void SendClientEnemyIsDead(int identificationNum, int isDead = 1);


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

