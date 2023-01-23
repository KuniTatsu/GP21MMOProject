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

	//アイテムのフィールドへのドロップ状況を共有する関数
	void SendClientFieldItemInfo(float x, float y, int itemId);

	//クライアントキャラクターの位置座標と画像ハンドル番号を送る関数
	void SendClientPlayerInfo(float x, float y, int dir,float HP, int isCreated = 0, int ghNum = 0, int isDebug = 0);
	
	//クライアントキャラクターの初期ステータスのサーバー登録
	void SendClientPlayerInitInfo(float x, float y, float HP,int ghNum);

	//クライアントキャラクターのステータス変動の共有
	void SendClientPlayerStatus(float moveHP);

	//クライアントキャラクターの死亡状況の共有
	void SendClientPlayerIsDead(int idDead = 1);

	//クライアントキャラクターが発動した攻撃のエフェクトの座標とエフェクト番号を送る関数
	void SendClientAttackEffectInfo(float x, float y, int effectNum, int dir = 0);

	//エネミーの位置座標の共有
	void SendClientEnemyInfo(float x, float y, int dir, int identificationNum,int type);

	//エネミーのステータス変動の共有
	void SendClientEnemyStatus(int identificationNum,float moveHP);

	//エネミーの死亡状況の共有
	void SendClientEnemyIsDead(int identificationNum, int isDead = 1);


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

