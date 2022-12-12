//#include "ChatBase.h"
//#include"GameManager.h"
////#include"Connect.h"
//#include<stdio.h>
//#include"../json11.hpp"
//
//using namespace json11;
///*
//	必要要件
//	・文字の入力ができる
//	・画面内に入力中の文字列が表示される
//	・Enterキーを押した時点で表示されている文字列が配列に入り、保管される
//*/
//
//using namespace std;
///*
//std::string SjistoUTF8(std::string srcSjis)
//{
//	//Unicodeへ変換後の文字列長を得る
//	int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);
//
//	//必要な分だけUnicode文字列のバッファを確保
//	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
//
//	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);
//
//	//ShiftJISからUnicodeへ変換
//	MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);
//
//
//	//UTF8へ変換後の文字列長を得る
//	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
//
//	//必要な分だけUTF8文字列のバッファを確保
//	char* bufUTF8 = new char[lengthUTF8];
//
//	memset(bufUTF8, 0, sizeof(char) * lengthUTF8);
//
//	//UnicodeからUTF8へ変換
//	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode - 1, bufUTF8, lengthUTF8, NULL, NULL);
//
//
//	std::string strUTF8(bufUTF8);
//
//	delete[] bufUnicode;
//	delete[] bufUTF8;
//
//	return strUTF8;
//}
//*/
//
//ChatBase::ChatBase()
//{
//	gManager = GameManager::GetInstance();
//
//	connect = new Connect();
//	//サーバーに接続
//	int result = connect->ConnectServer();
//
//	
//	if (!init) {
//
//		//string name = SjistoUTF8("プレイヤー1");
//
//		connect->EntryServer("プレイヤー1");
//
//		connect->GetEntryUserId();
//
//		init = true;
//	}
//
//
//	const string test = "こんにちは";
//
//	/*Json obj = Json::object({
//		{ "chat", test },
//		});
//
//	std::string hogehoge = obj.dump();*/
//
//	//string utf = gManager->SjistoUTF8(test);
//
//	//メッセージを送信
//	connect->SendClientMessage(test);
//
//	//チャット欄のスクリーンを生成
//	chatArea = MakeScreen(340, 400, TRUE);
//
//	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力なし)
//	CreateKeyInput();
//	// 作成したキー入力ハンドルをアクティブにする
//	SetActiveKeyInput(g_InputHandle);
//}
//
//ChatBase::~ChatBase()
//{
//	DeleteKeyInput(g_InputHandle);
//}
//
//void ChatBase::DrawWritingMessage()
//{
//	//DrawStringEx(400, 500, -1, bufMessage.c_str());
//	// 入力モードを描画
//	DrawKeyInputModeString(640, 480);
//
//	// 入力途中の文字列を描画
//	DrawKeyInputString(0, 0, g_InputHandle);
//}
//
//void ChatBase::Write()
//{
//
//}
//
//void ChatBase::DrawAllMessage()
//{
//	//チャットを描画するエリアを限定する
//	SetDrawScreen(chatArea);
//	SetBackgroundColor(32, 32, 32, 180);
//	ClearDrawScreen();
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
//
//	//保存されたメッセージから最新の10個のみを描画する
//	//空じゃなかったら
//	if (!savedMessage.empty()) {
//		//auto hoge = savedMessage.end();
//
//		int arrayNum = savedMessage.size();
//		for (int i = 0; i < 10; ++i) {
//
//			if (i + 1 > arrayNum)break;
//
//			auto hoge = std::to_string(i) + "番目のメッセージを描画したよ";
//			tnl::DebugTrace(hoge.c_str());
//			tnl::DebugTrace("\n");
//
//			if (arrayNum < 10) {
//				DrawStringEx(20, 10 + (i * 50), -1, savedMessage[i].c_str());
//			}
//			else {
//				int messageNum = i + (arrayNum - 10);
//
//				DrawStringEx(20, 10 + (i * 50), -1, savedMessage[messageNum].c_str());
//			}
//		}
//	}
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//
//	/*for (int i = 0; i < savedMessage.size(); ++i) {
//		DrawStringEx(20, 10 + i * 20, -1, savedMessage[i].c_str());
//	}*/
//
//	//元の画面への出力に切り替え
//	SetDrawScreen(DX_SCREEN_BACK);
//	//チャットを描画するエリアを一枚絵として描画する
//	DrawGraph(10, 300, chatArea, true);
//
//}
////引数で受け取った文字列をパースして登録する関数 チャット用
//void ChatBase::ParseMessage(const std::string message)
//{
//	if (message == "")return;
//
//	//メッセージを受信
//	//const std::string getMessage = connect->GetServerMessage();
//
//
//	auto fixMessage = gManager->UTF8toSjis(message);
//
//	std::string err;
//	auto json = json11::Json::parse(fixMessage, err);
//
//	std::string chat = "";
//
//	//chat = gManager->UTF8toSjis(json["info"].string_value());
//	chat = json["chat"].string_value();
//	auto count = json["count"].int_value();
//
//	if (chat != "") {
//		InsertStringToChatVector(chat);
//	}
//	
//}
//
//void ChatBase::InsertStringToChatVector(const std::string chat)
//{
//	//自分が送ったメッセージだった場合は登録しない
//	if (chat == myLastMessage)return;
//	//vectorに登録
//	//hoge.emplace_back(chat);
//	savedMessage.emplace_back(chat);
//}
//
//void ChatBase::Update()
//{
//	sequence.update(gManager->deltaTime);
//	ParseMessage(getMessage);
//	SetGetMessage("");
//}
//
//void ChatBase::Draw()
//{
//	DrawAllMessage();
//
//}
//
//bool ChatBase::SeqDrawMessage(const float deltatime)
//{
//	if (sequence.isStart()) {
//		// 入力文字列を初期化する
//		SetKeyInputString("", g_InputHandle);
//	}
//
//	//Write();
//	int hoge = CheckKeyInput(g_InputHandle);
//
//	if (hoge != 0) {
//
//		//正常終了時のみメッセージを保存、送信する
//		if (hoge == 1) {
//			//入力された文字列を保存する
//			GetKeyInputString(buffer, g_InputHandle);
//
//			std::string buf = buffer;
//
//			tnl::DebugTrace("-------------------");
//			tnl::DebugTrace("\n");
//
//			//空白文字なら登録しない
//			if (buf != "") {
//				savedMessage.emplace_back(buf);
//				//サーバーにbufを送る
//				//connect->SendClientMessage(buf);
//				gManager->CreateSendThread(buf);
//			}
//
//		}
//
//		// 入力文字列を初期化する
//		SetKeyInputString("", g_InputHandle);
//
//		// 再度インプットハンドルをアクティブにする
//		SetActiveKeyInput(g_InputHandle);
//
//		//シークエンスを移動する
//		sequence.change(&ChatBase::SeqWait);
//	}
//	else {
//		DrawWritingMessage();
//	}
//
//
//	return true;
//}
//
//bool ChatBase::SeqWait(const float deltatime)
//{
//	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_TAB)) {
//		//シークエンスを移動する
//		sequence.change(&ChatBase::SeqDrawMessage);
//	}
//
//	return true;
//}
//
//void ChatBase::CreateKeyInput()
//{
//	if (g_InputHandle != 0)return;
//	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力なし)
//	g_InputHandle = MakeKeyInput(30, true, false, false);
//}
