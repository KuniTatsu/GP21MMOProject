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
	//チャットメッセージの送信
	void SendClientMessage(std::string sendMessage);
	//チャットメッセージの受信
	const std::string GetServerMessage();

	//ユーザー登録関数
	void EntryServer(std::string playerName);

	//ユーザー登録情報取得関数
	void GetEntryUserId();

	


private:

	//サーバーのIPアドレス
	//std::string host = "127.0.0.1";
	//std::string host = "192.168.80.129";
	std::string host = "10.76.13.220";
	

	//ポート
	const std::string  port = "9001"; //80


	std::string	myLastMessage = "";


	GameManager* gManager = nullptr;

};

