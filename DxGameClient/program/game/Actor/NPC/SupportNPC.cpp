#include "SupportNPC.h"
#include"../../GameManager.h"

SupportNPC::SupportNPC(float x, float y, float distance) :NPC(x, y)
{

	canHearDistance = distance;

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

bool SupportNPC::CheckNearNPC(float PlayerX, float PlayerY)
{
	bool ret = false;

	auto gManager = GameManager::GetInstance();

	tnl::Vector3 pPos(PlayerX, PlayerY, 0);

	float distance = gManager->GetLength(pPos, GetDrawPos());

	if (canHearDistance > distance)
	{
		isNearPlayer = true;
		ret = true;
	}
	else {
		isNearPlayer = false;
	}

	return ret;
}

bool SupportNPC::loadNPCHint()
{
	return false;
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
	}
	//近くにplayerがいなかったら無視する
	if (!isNearPlayer) {
		cursorNum = 0;
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//上下にカーソル移動をさせ、項目を選ぶ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		cursorNum = (cursorNum + 1) % hint.size();
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		cursorNum = (cursorNum + hint.size() - 1) % hint.size();
	}

	//項目を決定
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		
		ChangeSequence(SEQUENCE::HINT);
	}
	//会話をやめる
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		ChangeSequence(SEQUENCE::WAIT);
	}
	return true;
}

bool SupportNPC::SeqHint(const float DeltaTime)
{
	//近くにplayerがいなかったら無視する
	if (!isNearPlayer) {

		cursorNum = 0;
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//hint選択画面に戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return false;
}

void SupportNPC::DrawFirstMenuSequence()
{
	//hintの数だけメニューを出す



}

void SupportNPC::DrawHintSequence()
{
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
