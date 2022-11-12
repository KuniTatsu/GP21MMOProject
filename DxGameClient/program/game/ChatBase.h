#pragma once
#include<string>
#include<vector>
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


	std::string	myLastMessage = "";

	//テスト用
	std::vector<std::string>hoge;

	//チャット欄
	int chatArea = 0;;

	char buffer[100] = {};

	tnl::Sequence<ChatBase> sequence =
		tnl::Sequence<ChatBase>(this, &ChatBase::SeqWait);

	bool SeqDrawMessage(const float deltatime);
	bool SeqWait(const float deltatime);

	void CreateKeyInput();


	GameManager* gManager = nullptr;

	Connect* connect = nullptr;

};
