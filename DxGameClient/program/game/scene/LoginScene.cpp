#include "LoginScene.h"
#include<fstream>
#include"../GameManager.h"
#include"../ResourceManager.h"
#include"../SceneManager.h"
#include"../scene/scene_map.h"
#include"../Actor/Player.h"
#include"../Actor/ActorData.h"

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
}

void LoginScene::initialzie()
{
	// キー入力ハンドルを作る(キャンセルあり全角文字有り数値入力なし)
	g_InputHandle = MakeKeyInput(30, true, false, false);
	// 作成したキー入力ハンドルをアクティブにする
	SetActiveKeyInput(g_InputHandle);

	charaIcon = ResourceManager::GetInstance()->GetGraphicVector(static_cast<int>(ResourceManager::RESOUCETYPE::CHARAICON));
}

void LoginScene::update(float delta_time)
{
	mainSequence.update(delta_time);
	if (canChangeScene)SceneManager::GetInstance()->chengeScene(new Scene_Map());
}

void LoginScene::render()
{
}

void LoginScene::ChangeSequence(int sequence)
{
	if (sequence >= static_cast<int>(SEQUENCE::MAX))return;

	switch (sequence)
	{
	case static_cast<int>(SEQUENCE::CHECKUUID):
		mainSequence.change(&LoginScene::SeqCheckHaveUUID);
		break;
	case static_cast<int>(SEQUENCE::INPUTNAME):
		mainSequence.change(&LoginScene::SeqInputCharaName);
		break;
	case static_cast<int>(SEQUENCE::CHECKNAME):
		mainSequence.change(&LoginScene::SeqCheckNameSelect);
		break;
	case static_cast<int>(SEQUENCE::SELECTGRAPHIC):
		mainSequence.change(&LoginScene::SeqSelectGraphic);
		break;
	case static_cast<int>(SEQUENCE::CHECKGRAPHIC):
		mainSequence.change(&LoginScene::SeqCheckGraphic);
		break;
	case static_cast<int>(SEQUENCE::WAITCHANGESCENE):
		mainSequence.change(&LoginScene::SeqWaitChangeScene);
		break;
	default:
		break;
	}
}

bool LoginScene::SeqCheckHaveUUID(const float deltatime)
{
	//サーバーへ接続
	GameManager::GetInstance()->ConnectServer();

	if (mainSequence.isStart()) {
		//サーバー通信取得用スレッドの作成
		GameManager::GetInstance()->CreateThread();
	}

	//ofstream型の変数 開いたファイルが展開される
	std::ifstream loadfile;
	//相対パス
	std::string filename = "save/myUUID.txt";

	std::string UUID = "";


	//パスから入力設定でファイルを開く
	loadfile.open(filename, std::ios::in);

	if (loadfile) {
		loadfile >> UUID;

		//開いたファイルの開放
		loadfile.close();
	}

	//UUIDを読み込めたら
	if (UUID != "") {

		auto gManager = GameManager::GetInstance();

		//サーバーからUUIDを使ってステータスを取得,帰ってきた情報でPlayerを生成
		gManager->GetPlayerInfo(UUID);

		//UUIDを登録
		gManager->SetClientUUID(UUID);




		ChangeSequence(static_cast<int>(SEQUENCE::WAITCHANGESCENE));
	}
	//初めてのログインだったら
	else {
		//アカウント作成シークエンスに移る
		ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
	}

	return true;
}

bool LoginScene::SeqInputCharaName(const float deltatime)
{
	if (mainSequence.isStart()) {
		// 入力文字列を初期化する
		SetKeyInputString("", g_InputHandle);
	}

	//画面に描画するメッセージ
	SetFontSize(25);
	DrawStringEx(400, 200, -1, "名前を入力してください");
	SetFontSize(16);

	int hoge = CheckKeyInput(g_InputHandle);

	if (hoge != 0) {

		//正常終了時のみメッセージを保存、送信する
		if (hoge == 1) {
			//入力された文字列を保存する
			GetKeyInputString(buffer, g_InputHandle);

			std::string buf = buffer;

			if (buf != "") {
				GameManager::GetInstance()->SetPlayerName(buf);
				checkNameInput = true;
			}
		}
		ChangeSequence(static_cast<int>(SEQUENCE::CHECKNAME));
	}
	else {
		DrawWritingMessage();
	}

	return true;
}


bool LoginScene::SeqCheckNameSelect(const float deltatime)
{
	//もし名前を入力していなかった場合
	if (!checkNameInput) {
		DrawStringEx(400, 300, -1, "名前を入力してください");
		DrawStringEx(400, 400, -1, "Enterで戻る");

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
		}
		return true;
	}
	//本当にこの名前でいいか表示する
	const std::string& name = GameManager::GetInstance()->GetPlayerName();

	SetFontSize(25);

	DrawStringEx(400, 200, -1, "この名前で始めても良いですか? Y:始める N:戻る");
	DrawStringEx(400, 300, -1, name.c_str());

	SetFontSize(16);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Y)) {
		ChangeSequence(static_cast<int>(SEQUENCE::SELECTGRAPHIC));
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_N)) {
		ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
	}
	return true;
}

bool LoginScene::SeqSelectGraphic(const float deltatime)
{
	SetFontSize(25);
	DrawStringEx(400, 200, -1, "あなたの見た目を選んでください");
	SetFontSize(16);

	for (int i = 0; i < charaIcon.size(); ++i) {
		//2段目
		if (i > charaIcon.size() / 2) {
			DrawRotaGraph(100 + 45 * i, 350, 1, 0, charaIcon[i], true);
		}
		else {
			//1段目
			DrawRotaGraph(100 + 45 * (i - 4), 300, 1, 0, charaIcon[i], true);
		}
	}

	for (int i = 0; i < charaIcon.size(); ++i) {
		//各画像の中心座標とからマウスのクリック判定を求める
		tnl::Vector3 centerPos = {};
		if (i > charaIcon.size() / 2) {
			centerPos = tnl::Vector3(100 + 45 * i, 350, 0);
		}
		else {
			centerPos = tnl::Vector3(100 + 45 * i, 300, 0);
		}
		//クリックしていたら
		if (GameManager::GetInstance()->isClickedRect(centerPos)) {
			selectCharaIconNum = i;
			ChangeSequence(static_cast<int>(SEQUENCE::CHECKGRAPHIC));
			return true;
		}
	}

	return true;
}

bool LoginScene::SeqCheckGraphic(const float deltatime)
{

	SetFontSize(25);

	DrawStringEx(400, 200, -1, "この画像で始めても良いですか? Y:始める N:戻る");
	DrawRotaGraph(512, 384, 1, 0, charaIcon[selectCharaIconNum], true);

	SetFontSize(16);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Y)) {

		auto gManager = GameManager::GetInstance();

		//名前をサーバーへ送信
		gManager->EntryServer();
		//UUIDの取得
		gManager->GetMyUUID();

		//playerの生成
		auto player = GameManager::GetInstance()->CreatePlayer(charaIcon[selectCharaIconNum]);

		////Player情報のサーバーへの送信--データベース登録とサーバーの一時データへの保存
		//gManager->SendPlayerInfoToServer();

		auto& data = player->GetActorData();
		auto& attribute = data->GetAttribute();
		gManager->SendPlayerAttribute(attribute[0], attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);


		ChangeSequence(static_cast<int>(SEQUENCE::WAITCHANGESCENE));
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_N)) {
		ChangeSequence(static_cast<int>(SEQUENCE::SELECTGRAPHIC));
	}

	return true;
}

bool LoginScene::SeqWaitChangeScene(const float deltatime)
{

	SetFontSize(25);

	DrawStringEx(300, 384, -1, "LiveWorldへようこそ");
	DrawStringEx(300, 450, -1, "世界へ転送しています");

	SetFontSize(16);

	bufferDeltaTime += deltatime;
	if (BUFFERTIME > bufferDeltaTime)return true;

	auto& player = GameManager::GetInstance()->GetPlayer();

	if (player == nullptr)return false;

	if (!isSend) {
		//Player情報のサーバーへの送信--サーバーの一時データへの保存
		GameManager::GetInstance()->SendPlayerInfoToServer(true);
		player->SetIsCreatedDummy();
		isSend = true;
	}
	canChangeScene = true;

	return true;
}

void LoginScene::DrawWritingMessage()
{
	// 入力モードを描画
	/*DrawKeyInputModeString(640, 480);*/

	// 入力途中の文字列を描画
	DrawKeyInputString(0, 0, g_InputHandle);
}