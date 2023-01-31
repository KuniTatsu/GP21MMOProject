#pragma once
#include<string>
#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;
class Connect;

class ChatBase
{
public:
	ChatBase();
	~ChatBase();

	//現在入力中の文字列を描画する関数
	void DrawWritingMessage();
	//入力関数
	void Write();

	//入力完了後の文字列を描画する関数
	void DrawAllMessage();

	//受け取ったstringデータをパースして格納する関数
	void ParseMessage(const std::string message);

	//受け取ったstring文字列をchatのvectorに格納する関数
	void InsertStringToChatVector(const std::string chat);

	//サーバーから受け取ったメッセージを登録する関数
	inline void SetGetMessage(const std::string serverMessage) {
		getMessage = serverMessage;
	}

	//更新関数
	void Update();

	//描画関数
	void Draw();

	int g_InputHandle;

	

private:
	//入力が完了したあとの文字列
	std::vector<std::string>savedMessage;
	//入力中の文字列
	std::string bufMessage;

	//最後に自分が送ったチャットメッセージ
	std::string	myLastMessage = "";

	//テスト用
	std::vector<std::string>hoge;

	//サーバーから受け取った文字列
	std::string getMessage = "";


	//チャット欄
	int chatArea = 0;;

	char buffer[100] = {};

	bool init = false;


	tnl::Sequence<ChatBase> sequence =
		tnl::Sequence<ChatBase>(this, &ChatBase::SeqWait);

	bool SeqDrawMessage(const float deltatime);
	bool SeqWait(const float deltatime);

	void CreateKeyInput();


	GameManager* gManager = nullptr;

	std::shared_ptr<Connect> connect = nullptr;

};
