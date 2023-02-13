#pragma once

//手助けNPC
//ヒントをくれたりアイテムをくれたりする

#include"NPC.h"



class SupportNPC :public NPC
{
public:
	SupportNPC(float x, float y, int ghNum = 0, float distance = 64.0f);
	~SupportNPC();

	void Update()override;
	void Draw(Camera* camera)override;
	void Init() override;


public:


private:

	//初期シークエンスを設定
	tnl::Sequence<SupportNPC> mainSequence =
		tnl::Sequence<SupportNPC>(this, &SupportNPC::SeqWait);

	//各シークエンスのUpdate関数
	bool SeqWait(const float DeltaTime);
	bool SeqFirstMenu(const float DeltaTime);
	bool SeqHint(const float DeltaTime);

	//シークエンスごとの描画関数
	void DrawWaitSequence();
	void DrawFirstMenuSequence();
	void DrawHintSequence();

	//現在のシークエンスの描画関数
	const std::function< void(SupportNPC*) > DRAWSEQUENCE[3] = { &SupportNPC::DrawWaitSequence, &SupportNPC::DrawFirstMenuSequence,&SupportNPC::DrawHintSequence };

	//シークエンス一覧
	enum class SEQUENCE :uint32_t {
		WAIT,
		FIRSTMENU,
		HINT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::WAIT;

	//シークエンス変更関数
	bool ChangeSequence(SEQUENCE NextSeq);

private:

	////npcの項目ごとのヒント文章
	//std::vector<std::string> hint;

	//メニュー番号
	int cursorNum = 0;

	//メニューのページ番号
	int maxPageNum = 0;
	int nowDrawPage = 0;

	//メニューの1ページに描画する最大数
	const int MAXDRAWNUM = 3;

};

