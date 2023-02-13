#pragma once
#include"scene_base.h"
#include"../../dxlib_ext/dxlib_ext.h"

//UUIDをファイルから読み込み、存在するならそのキャラのデータをサーバから受け取って生成し、マップシーンに映る
//無いなら新しくプレイヤーを作るシークエンスに移動する

class LoginScene :public SceneBase
{
public:
	LoginScene();
	~LoginScene();

	void initialzie();
	void update(float delta_time);
	void render();


private:

	int g_InputHandle = 0;

	char buffer[100] = {};

	std::vector<int>charaIcon;

	//名前を入力し終わったか
	bool checkNameInput = false;

	tnl::Sequence<LoginScene>mainSequence = tnl::Sequence<LoginScene>(this, &LoginScene::SeqCheckHaveUUID);

	enum class SEQUENCE :uint32_t {
		CHECKUUID,
		INPUTNAME,
		CHECKNAME,
		SELECTGRAPHIC,
		CHECKGRAPHIC,
		WAITCHANGESCENE,
		MAX
	};

	//選んだ画像の番号
	int selectCharaIconNum = -1;

	//遷移フラグ
	bool canChangeScene = false;
	//シーン遷移までの時間
	const float BUFFERTIME = 2.0f;

	//シーン遷移中のdeltatime
	float bufferDeltaTime = 0.0f;

	//プレイヤーデータを送ったか
	bool isSend = false;

private:

	//シークエンス変更関数
	void ChangeSequence(int sequence);

	//描画関数
	void DrawWritingMessage();

	//既にUUIDを持っているかどうか確かめるシークエンス
	bool SeqCheckHaveUUID(const float deltatime);

	//名前を決めるシークエンス
	bool SeqInputCharaName(const float deltatime);

	//名前確認シークエンス
	bool SeqCheckNameSelect(const float deltatime);

	//画像決定シークエンス
	bool SeqSelectGraphic(const float deltatime);

	//画像確認シークエンス
	bool SeqCheckGraphic(const float deltatime);

	//遷移待ちシークエンス
	bool SeqWaitChangeScene(const float deltatime);

};

