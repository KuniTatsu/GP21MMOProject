#pragma	comment(lib,"Ws2_32.lib")//winsockのリンク
#include <winsock.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

//test

WSADATA WinSockDataStrage = { 0 };//WinSockの情報を格納する構造体
SOCKADDR_IN ServerInfo = { 0 };//サーバーの情報を格納する構造体 
SOCKADDR_IN ClientInfo = { 0 };//クライアントの情報を格納する

//SYNを受け取るためだけのソケット
SOCKET ListenSocket;//クライアントの接続を待ち受けるソケット(受付,繋いだあとは開放する)
//パケットをやり取りするソケット
SOCKET CommunicationSocket;//今後使うソケット

char ClientDataBuffer[1024];//読み込んだデータを格納するための配列

int trueNum = 0;
char DataBuffer1[50];

vector<string>receiveData;

string GetReceiveData();

int main(void) {

	//WinSock使用準備
	//第一引数はWORD型->unsigned short型=2byteの整数型
	//MAKEWORDで計算してビット演算をして代入　ここでしか使わん
	//第二引数はWSADATA構造体へのアドレス指定
	WSAStartup(MAKEWORD(1, 1), &WinSockDataStrage);

	//AF_INETは整数の2を表す
	//使用するネットワークの種類を決める数字
	//AF_INETはTCP/UDPを使用する際に使う
	ServerInfo.sin_family = AF_INET;


	//2byte以上のデータはネットワークバイトオーダーへの変換が必要
	//htons関数はunsigined shor型のネットワークバイトオーダーにへ変換する
	//クライアント側はポート番号をネットワークバイトオーダーに変換して探すため、
	//鯖側も変換しておく必要がある。
	//ただし今後は文字列でやり取りするので使うことはなさそう
	ServerInfo.sin_port = htons(54924);//サーバーに使うポート番号の指定

	//鯖のIPアドレスを指定する
	//今はローカルだがグローバルIPを入れればネットワークに公開できる
	//inet_addr関数は1byte毎に.で区切られた文字列を受け取ってIPアドレスとして解釈する関数
	//同時にネットワークバイトオーダーへの変換も行う
	ServerInfo.sin_addr.S_un.S_addr = inet_addr("192.168.44.1");


	//第一引数はアドレスファミリの指定
	//第二引数は通信プロトコル:TCPならSOCK_STREAMを使う
	//今後はこのソケットをアプリケーション上で待機させて相手方のパケットをキャッチする
	ListenSocket = socket(AF_INET, SOCK_STREAM, 0);//リッスン用ソケットの作成

	//bind関数でソケットと鯖の情報を紐づける
	//第二引数は鯖の情報を指定する。
	//より大きい構造体であるSOCKADDR型にキャストすることでデータを失わずに
	//bind関数を使うための準備をする
	//第三引数にはSOCKADDR_IN構造体の大きさを渡す。
	bind(ListenSocket, (SOCKADDR*)&ServerInfo, sizeof(ServerInfo));

	printf("\n準備完了\n");

	//----------準備完了----------//

	//ソケットを接続可能状態へ変化させるだけの関数
	//接続保留させるパケットの個数を指定する
	//ほぼ同時にソケットにパケットが来たとき、プログラムの長さによっては待たせなければいけない
	//今回は0なので連続してパケットが届いたときにあとから来たパケットは破棄することになる可能性がある
	//通常は4か5を指定する
	listen(ListenSocket, 0);

	//次で使う関数の引数が変数のアドレスしか格納できないための一時変数
	int ClientInfoLEN = static_cast <int>(sizeof(ClientInfo));

	//接続を受け入れる状態で待機する
	//accept関数はソフトウェアをブロッキングする。
	//accept以外のすべての処理が動作を停止し、accept以下の内容は処理しない。
	//クライアントからのSYNを待ち受けるためにプログラムを停止する
	//第一引数は待ち受けるソケット
	//第二引数はクライアント情報の格納先構造体のアドレス
	//第三引数はその大きさ
	CommunicationSocket = accept(ListenSocket, (SOCKADDR*)&ClientInfo, &ClientInfoLEN);

	//acceptは受け付けたソケットをベースに新しいソケットを返却する
	//そのソケットを使って実際のパケットのやり取りを行う

	//使い終わったソケットは閉じる
	closesocket(ListenSocket);

	/*

	int recvReturn = 0;//読み込んだ文字数

	//受け取ったデータの読み出し
	//ソケットバッファに格納されたパケットを読み出す
	//今回は文字列を送信されたと想定している
	//第一引数はパケットを受け取ったソケット
	//第二引数はパケットを読みれたときに格納する領域のアドレスを指定
	//配列名は配列の先頭アドレスを表現できる
	//第三引数はパケットの読み出しの深さ
	//null文字が切り捨てられるため手動でnull文字を付加する
	//よって最後から一つ手前までは読み込んで良いとする->-1
	//第四引数は0でいい
	recvReturn = recv(CommunicationSocket, ClientDataBuffer, sizeof(ClientDataBuffer) - 1, 0);
	//null文字の挿入
	ClientDataBuffer[recvReturn] = '\0';

	*/
	string hoge=GetReceiveData();
	receiveData.emplace_back(hoge);

	

	//----------------ここに受け取った情報を使う部分を記述する---------------------------//


	//文字列出力
	//printf("%s", ClientDataBuffer);
	for (auto data : receiveData) {
		cout << data << endl;
	}




	//-----------------------------------------------------------------------------------//

	//後片付け
	//ソケットを閉じてデータを受け付けなくする
	//0ならパケット受け取りを終了
	//1ならパケットの送信を終了
	//2ならどちらも終了
	shutdown(CommunicationSocket, 2);
	//ソケットに格納していた領域の開放
	closesocket(CommunicationSocket);
	//winsockの使用の終了 ここで初めて内部のメモリ領域を開放する
	WSACleanup();


	return 0;
}


string GetReceiveData() {

	int recvSize = 0;

	recvSize = recv(CommunicationSocket, ClientDataBuffer, sizeof(ClientDataBuffer) - 1, 0);
	ClientDataBuffer[recvSize] = '\0';

	
	for (; ClientDataBuffer[trueNum] != '|'; ++trueNum) {
		DataBuffer1[trueNum] = ClientDataBuffer[trueNum];
	}
	DataBuffer1[trueNum] = '\0';

	//return ClientDataBuffer;
	return DataBuffer1;

}