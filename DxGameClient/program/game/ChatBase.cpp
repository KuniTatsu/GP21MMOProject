#include "ChatBase.h"
#include"GameManager.h"
#include<stdio.h>
/*
	必要要件
	・文字の入力ができる
	・画面内に入力中の文字列が表示される
	・Enterキーを押した時点で表示されている文字列が配列に入り、保管される
*/


ChatBase::ChatBase()
{
	gManager = GameManager::GetInstance();

	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力なし)
	CreateKeyInput();
	// 作成したキー入力ハンドルをアクティブにする
	SetActiveKeyInput(g_InputHandle);
}

ChatBase::~ChatBase()
{
	DeleteKeyInput(g_InputHandle);
}

void ChatBase::DrawWritingMessage()
{
	//DrawStringEx(400, 500, -1, bufMessage.c_str());
	// 入力モードを描画
	DrawKeyInputModeString(640, 480);

	// 入力途中の文字列を描画
	DrawKeyInputString(0, 0, g_InputHandle);
}

void ChatBase::Write()
{

}

void ChatBase::DrawAllMessage()
{
	for (int i = 0; i < savedMessage.size(); ++i) {
		DrawStringEx(100, 100 + i * 20, -1, savedMessage[i].c_str());
	}
}

void ChatBase::Update()
{
	sequence.update(gManager->deltaTime);
}

void ChatBase::Draw()
{
	DrawAllMessage();

}

bool ChatBase::SeqDrawMessage(const float deltatime)
{
	if (sequence.isStart()) {
		ClearInputCharBuf();
	}


	//Write();
	int hoge = CheckKeyInput(g_InputHandle);

	if (hoge != 0) {
		GetKeyInputString(buffer,g_InputHandle);

		std::string buf = buffer;
		savedMessage.emplace_back(buf);

		// 入力文字列を初期化する
		SetKeyInputString("", g_InputHandle);

		// 再度インプットハンドルをアクティブにする
		SetActiveKeyInput(g_InputHandle);

		//シークエンスを移動する
		sequence.change(&ChatBase::SeqWait);
	}
	else {
		DrawWritingMessage();
	}

	//if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

	//	//文字列を登録
	//	savedMessage.emplace_back(bufMessage);
	//	bufMessage = "";
	//	//シークエンスを移動する
	//	sequence.change(&ChatBase::SeqWait);
	//}
	return true;
}

bool ChatBase::SeqWait(const float deltatime)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {		
		//シークエンスを移動する
		sequence.change(&ChatBase::SeqDrawMessage);
	}

	return true;
}

void ChatBase::CreateKeyInput()
{
	if (g_InputHandle != 0)return;
	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力なし)
	g_InputHandle = MakeKeyInput(30, true, false, false);
}
