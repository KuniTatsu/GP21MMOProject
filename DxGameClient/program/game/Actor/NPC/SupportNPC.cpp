#include "SupportNPC.h"
#include"NPCSpeak.h"
#include"../../GameManager.h"
#include"../../UI/UIManager.h"
#include"../../UI/GraphicUI.h"
#include"../Camera.h"
#include<math.h>

SupportNPC::SupportNPC(float x, float y, int ghNum, float distance) :NPC(x, y, ghNum)
{
	canHearDistance = distance;
	//NPCの話す内容の読み込み
	if (loadNPCHint(static_cast<int>(NPCTYPE::SUP))) {
		maxPageNum = static_cast<int>(std::floor(npcSpeaks.size() / MAXDRAWNUM));
	}
}

SupportNPC::~SupportNPC()
{
}

void SupportNPC::Update()
{
	auto gManager = GameManager::GetInstance();
	float deltaTime = gManager->deltaTime;
	mainSequence.update(deltaTime);

}

void SupportNPC::Draw(Camera* camera)
{
	DrawRotaGraphF(drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1), drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1),
		1, 0, ghs[10], true);
	//シークエンスごとの描画
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);
}

void SupportNPC::Init()
{

}

bool SupportNPC::SeqWait(const float DeltaTime)
{

	//近くにplayerがいなかったら無視する
	if (!isNearPlayer)return false;

	//Enterを感知
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return true;
}

bool SupportNPC::SeqFirstMenu(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		cursorNum = 0;
		//SUPNPCのUIを描画状態にする
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		//描画するUIをFirstMenuに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::FIRSTMENU));
	}
	//近くにplayerがいなかったら無視する
	if (!isNearPlayer) {
		cursorNum = 0;
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//上下にカーソル移動をさせ、項目を選ぶ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		cursorNum = (cursorNum + 1) % MAXDRAWNUM;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		cursorNum = (cursorNum + MAXDRAWNUM - 1) % MAXDRAWNUM;
	}

	//hintのページ切り替え
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		nowDrawPage = (nowDrawPage + 1) % maxPageNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		nowDrawPage = (nowDrawPage + maxPageNum - 1) % maxPageNum;
	}

	//項目を決定
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//描画するUIをhintに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::HINT));
		ChangeSequence(SEQUENCE::HINT);
	}
	//会話をやめる
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
	}
	return true;
}

bool SupportNPC::SeqHint(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//描画するUIをhintに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::HINT));
	}

	//近くにplayerがいなかったら無視する
	if (!isNearPlayer) {

		cursorNum = 0;
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//hint選択画面に戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return false;
}

void SupportNPC::DrawWaitSequence()
{
	SetFontSize(50);
	DrawStringEx(20, 20, -1, "SupNPC:Wait");
	SetFontSize(16);
}

void SupportNPC::DrawFirstMenuSequence()
{
	tnl::Vector3 drawPos = {};

	//hintの数だけメニューを出す
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;
	if (mainSequence.isStart()) {
		firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::SUPNPC));

		//1番が文字を描画するUI枠なのでそこだけ取得する
		auto& leftTopPos = firstMenuGraphics[1]->GetLeftTopPos();
		drawPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y, 0);
	}

	DrawNpcTextName(MAXDRAWNUM, nowDrawPage, drawPos);

	SetFontSize(50);
	DrawStringEx(20, 20, -1, "SupNPC:MENU");
	SetFontSize(16);
}

void SupportNPC::DrawHintSequence()
{
	//選ばれたヒントの配列番号
	int selectHint = 0;
	std::vector<std::shared_ptr<GraphicUI>>hintMenuGraphics;
	if (mainSequence.isStart()) {
		hintMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::SUPNPC));

		//2番が文字を描画するUI枠なのでそこだけ取得する
		auto& leftTopPos = hintMenuGraphics[2]->GetLeftTopPos();
		drawPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y, 0);

		selectHint = nowDrawPage * MAXDRAWNUM + cursorNum;
	}

	DrawNpcText(selectHint, drawPos);

	SetFontSize(50);
	DrawStringEx(20, 20, -1, "SupNPC:Hint");
	SetFontSize(16);
}

bool SupportNPC::ChangeSequence(SEQUENCE NextSeq)
{
	switch (NextSeq)
	{
	case SEQUENCE::WAIT:
		mainSequence.change(&SupportNPC::SeqWait);
		nowSequence = SEQUENCE::WAIT;
		return true;
		break;
	case SEQUENCE::FIRSTMENU:
		mainSequence.change(&SupportNPC::SeqFirstMenu);
		nowSequence = SEQUENCE::FIRSTMENU;
		return true;
		break;
	case SEQUENCE::HINT:
		mainSequence.change(&SupportNPC::SeqHint);
		nowSequence = SEQUENCE::HINT;
		return true;
		break;
	default:
		return false;
		break;
	}

	return false;
}
