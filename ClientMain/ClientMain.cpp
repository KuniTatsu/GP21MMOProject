#pragma comment(lib,"Ws2_32.lib")
#include<winsock.h>

WSADATA WinSockDataStorage = { 0 };
SOCKET ConnectSocket;//相手に接続要求を出し、そのままパケット通信をするソケット

SOCKADDR_IN ServerInfo = { 0 };//鯖情報を格納する構造体


int main(void) {

	WSAStartup(MAKEWORD(1, 1), &WinSockDataStorage);
	ServerInfo.sin_family = AF_INET;
	ServerInfo.sin_port = htons(54924);
	ServerInfo.sin_addr.s_addr = inet_addr("192.168.44.1");
	ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);

	//クライアント側のみの関数
	//鯖にSYNを送る
	//失敗したらプログラムを終了する
	int ret=connect(ConnectSocket, (SOCKADDR*)&ServerInfo, sizeof(ServerInfo));
	//if (ret != 0)return 0;

	//鯖にパケットを送る
	//第二引数に送信する文字列
	//第三引数に文字列の長さ
	//第四引数はほぼ0でいい
	send(ConnectSocket, "ButtonA|", 8, 0);
	send(ConnectSocket, "ButtonB|", 8, 0);


	shutdown(ConnectSocket, 2);
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}