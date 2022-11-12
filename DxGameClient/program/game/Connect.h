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
	void GetServerMessage(std::vector<std::string>& Save);

	//ユーザー登録関数
	void EntryServer(std::string playerName);

	//ユーザー登録情報取得関数
	void GetEntryUserId();

	const std::string GetServerMessage();


private:

	//サーバーのIPアドレス
	//std::string host = "127.0.0.1";
	std::string host = "192.168.80.129";

	//ポート
	const std::string  port = "9001"; //80


	std::string	myLastMessage = "";


	GameManager* gManager = nullptr;

};

