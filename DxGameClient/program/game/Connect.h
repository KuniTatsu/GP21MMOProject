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

	//クライアントキャラクターの位置座標と画像ハンドル番号を送る関数
	void SendClientPlayerInfo(float x, float y, int dir, int isCreated = 0, int ghNum = 0, int isDebug = 0);

	//クライアントキャラクターの位置座標


	//自分がサーバーから抜けることを知らせる関数
	void SendExitServer();

private:

	//サーバーのIPアドレス
	//std::string host = "127.0.0.1";
	//std::string host = "192.168.80.129";
	std::string host = "10.76.14.195";

	//ポート
	const std::string  port = "9001"; //80


	std::string	myLastMessage = "";


	GameManager* gManager = nullptr;

};

