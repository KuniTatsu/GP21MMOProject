#pragma	comment(lib,"Ws2_32.lib")//winsock�̃����N
#include <winsock.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

WSADATA WinSockDataStrage = { 0 };//WinSock�̏����i�[����\����
SOCKADDR_IN ServerInfo = { 0 };//�T�[�o�[�̏����i�[����\���� 
SOCKADDR_IN ClientInfo = { 0 };//�N���C�A���g�̏����i�[����

//SYN���󂯎�邽�߂����̃\�P�b�g
SOCKET ListenSocket;//�N���C�A���g�̐ڑ���҂��󂯂�\�P�b�g(��t,�q�������Ƃ͊J������)
//�p�P�b�g������肷��\�P�b�g
SOCKET CommunicationSocket;//����g���\�P�b�g

char ClientDataBuffer[1024];//�ǂݍ��񂾃f�[�^���i�[���邽�߂̔z��

int trueNum = 0;
char DataBuffer1[50];
string bufTest;

vector<string>receiveData;

string GetReceiveData();

int main(void) {

	//WinSock�g�p����
	//��������WORD�^->unsigned short�^=2byte�̐����^
	//MAKEWORD�Ōv�Z���ăr�b�g���Z�����đ���@�����ł����g���
	//��������WSADATA�\���̂ւ̃A�h���X�w��
	WSAStartup(MAKEWORD(1, 1), &WinSockDataStrage);

	//AF_INET�͐�����2��\��
	//�g�p����l�b�g���[�N�̎�ނ����߂鐔��
	//AF_INET��TCP/UDP���g�p����ۂɎg��
	ServerInfo.sin_family = AF_INET;


	//2byte�ȏ�̃f�[�^�̓l�b�g���[�N�o�C�g�I�[�_�[�ւ̕ϊ����K�v
	//htons�֐���unsigined shor�^�̃l�b�g���[�N�o�C�g�I�[�_�[�ɂ֕ϊ�����
	//�N���C�A���g���̓|�[�g�ԍ����l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ����ĒT�����߁A
	//�I�����ϊ����Ă����K�v������B
	//����������͕�����ł���肷��̂Ŏg�����Ƃ͂Ȃ�����
	ServerInfo.sin_port = htons(54924);//�T�[�o�[�Ɏg���|�[�g�ԍ��̎w��

	//�I��IP�A�h���X���w�肷��
	//���̓��[�J�������O���[�o��IP������΃l�b�g���[�N�Ɍ��J�ł���
	//inet_addr�֐���1byte����.�ŋ�؂�ꂽ��������󂯎����IP�A�h���X�Ƃ��ĉ��߂���֐�
	//�����Ƀl�b�g���[�N�o�C�g�I�[�_�[�ւ̕ϊ����s��
	ServerInfo.sin_addr.S_un.S_addr = inet_addr("192.168.44.1");


	//�������̓A�h���X�t�@�~���̎w��
	//�������͒ʐM�v���g�R��:TCP�Ȃ�SOCK_STREAM���g��
	//����͂��̃\�P�b�g���A�v���P�[�V������őҋ@�����đ�����̃p�P�b�g���L���b�`����
	ListenSocket = socket(AF_INET, SOCK_STREAM, 0);//���b�X���p�\�P�b�g�̍쐬

	//bind�֐��Ń\�P�b�g�ƎI�̏���R�Â���
	//�������͎I�̏����w�肷��B
	//���傫���\���̂ł���SOCKADDR�^�ɃL���X�g���邱�ƂŃf�[�^�����킸��
	//bind�֐����g�����߂̏���������
	//��O�����ɂ�SOCKADDR_IN�\���̂̑傫����n���B
	bind(ListenSocket, (SOCKADDR*)&ServerInfo, sizeof(ServerInfo));

	//printf("\n��������\n");
	auto end = "\n��������\n";
	cout << end << endl;

	//----------��������----------//

	//�\�P�b�g��ڑ��\��Ԃ֕ω������邾���̊֐�
	//�ڑ��ۗ�������p�P�b�g�̌����w�肷��
	//�قړ����Ƀ\�P�b�g�Ƀp�P�b�g�������Ƃ��A�v���O�����̒����ɂ���Ă͑҂����Ȃ���΂����Ȃ�
	//�����0�Ȃ̂ŘA�����ăp�P�b�g���͂����Ƃ��ɂ��Ƃ��痈���p�P�b�g�͔j�����邱�ƂɂȂ�\��������
	//�ʏ��4��5���w�肷��
	listen(ListenSocket, 0);

	//���Ŏg���֐��̈������ϐ��̃A�h���X�����i�[�ł��Ȃ����߂̈ꎞ�ϐ�
	int ClientInfoLEN = static_cast <int>(sizeof(ClientInfo));

	//�ڑ����󂯓�����Ԃőҋ@����
	//accept�֐��̓\�t�g�E�F�A���u���b�L���O����B
	//accept�ȊO�̂��ׂĂ̏�����������~���Aaccept�ȉ��̓��e�͏������Ȃ��B
	//�N���C�A���g�����SYN��҂��󂯂邽�߂Ƀv���O�������~����
	//�������͑҂��󂯂�\�P�b�g
	//�������̓N���C�A���g���̊i�[��\���̂̃A�h���X
	//��O�����͂��̑傫��
	CommunicationSocket = accept(ListenSocket, (SOCKADDR*)&ClientInfo, &ClientInfoLEN);

	//accept�͎󂯕t�����\�P�b�g���x�[�X�ɐV�����\�P�b�g��ԋp����
	//���̃\�P�b�g���g���Ď��ۂ̃p�P�b�g�̂������s��

	//�g���I������\�P�b�g�͕���
	closesocket(ListenSocket);

	/*

	int recvReturn = 0;//�ǂݍ��񂾕�����

	//�󂯎�����f�[�^�̓ǂݏo��
	//�\�P�b�g�o�b�t�@�Ɋi�[���ꂽ�p�P�b�g��ǂݏo��
	//����͕�����𑗐M���ꂽ�Ƒz�肵�Ă���
	//�������̓p�P�b�g���󂯎�����\�P�b�g
	//�������̓p�P�b�g��ǂ݂ꂽ�Ƃ��Ɋi�[����̈�̃A�h���X���w��
	//�z�񖼂͔z��̐擪�A�h���X��\���ł���
	//��O�����̓p�P�b�g�̓ǂݏo���̐[��
	//null�������؂�̂Ă��邽�ߎ蓮��null������t������
	//����čŌォ����O�܂ł͓ǂݍ���ŗǂ��Ƃ���->-1
	//��l������0�ł���
	recvReturn = recv(CommunicationSocket, ClientDataBuffer, sizeof(ClientDataBuffer) - 1, 0);
	//null�����̑}��
	ClientDataBuffer[recvReturn] = '\0';

	*/

	//-----��������N���C�A���g���瑗���Ă������e��ǂݏo�������B��񂾂��ł���
	int recvSize = 0;

	recvSize = recv(CommunicationSocket, ClientDataBuffer, sizeof(ClientDataBuffer) - 1, 0);
	ClientDataBuffer[recvSize] = '\0';

	//---------------------------------

	//-----"|"������܂ł���̕�����Ƃ��ēǂݎ�邽�߂̏���-------------------------
	//
	string hoge=GetReceiveData();
	receiveData.emplace_back(hoge);

	bufTest = "";
	trueNum += 1;

	//-----�����܂ň�Z�b�g------------------------------------------------------------

	string hoge2 = GetReceiveData();
	receiveData.emplace_back(hoge2);

	bufTest = "";
	trueNum += 1;

	

	//----------------�����Ɏ󂯎���������g���������L�q����---------------------------//


	//������o��
	//printf("%s", ClientDataBuffer);
	for (auto data : receiveData) {
		cout << data << endl;
	}




	//-----------------------------------------------------------------------------------//

	//��Еt��
	//�\�P�b�g����ăf�[�^���󂯕t���Ȃ�����
	//0�Ȃ�p�P�b�g�󂯎����I��
	//1�Ȃ�p�P�b�g�̑��M���I��
	//2�Ȃ�ǂ�����I��
	shutdown(CommunicationSocket, 2);
	//�\�P�b�g�Ɋi�[���Ă����̈�̊J��
	closesocket(CommunicationSocket);
	//winsock�̎g�p�̏I�� �����ŏ��߂ē����̃������̈���J������
	WSACleanup();


	return 0;
}


string GetReceiveData() {

	for (; ClientDataBuffer[trueNum] != '|'; ++trueNum) {
		//DataBuffer1[trueNum] = ClientDataBuffer[trueNum];
		bufTest += ClientDataBuffer[trueNum];
	}
	//DataBuffer1[trueNum] = '\0';
	bufTest += '\0';

	//return ClientDataBuffer;
	//return DataBuffer1;
	return bufTest;

}