#pragma comment(lib,"Ws2_32.lib")
#include<winsock.h>

WSADATA WinSockDataStorage = { 0 };
SOCKET ConnectSocket;//����ɐڑ��v�����o���A���̂܂܃p�P�b�g�ʐM������\�P�b�g

SOCKADDR_IN ServerInfo = { 0 };//�I�����i�[����\����


int main(void) {

	WSAStartup(MAKEWORD(1, 1), &WinSockDataStorage);
	ServerInfo.sin_family = AF_INET;
	ServerInfo.sin_port = htons(54924);
	ServerInfo.sin_addr.s_addr = inet_addr("192.168.44.1");
	ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);

	//�N���C�A���g���݂̂̊֐�
	//�I��SYN�𑗂�
	//���s������v���O�������I������
	int ret=connect(ConnectSocket, (SOCKADDR*)&ServerInfo, sizeof(ServerInfo));
	//if (ret != 0)return 0;

	//�I�Ƀp�P�b�g�𑗂�
	//�������ɑ��M���镶����
	//��O�����ɕ�����̒���
	//��l�����͂ق�0�ł���
	send(ConnectSocket, "ButtonA|", 8, 0);
	send(ConnectSocket, "ButtonB|", 8, 0);


	shutdown(ConnectSocket, 2);
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}