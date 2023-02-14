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
	//NPC�̘b�����e�̓ǂݍ���
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
}

void SupportNPC::Init()
{

}

void SupportNPC::DrawNPCSpeak()
{
	//�V�[�N�G���X���Ƃ̕`��
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);
}

bool SupportNPC::SeqWait(const float DeltaTime)
{

	//�߂���player�����Ȃ������疳������
	if (!isNearPlayer)return false;

	//Enter�����m
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return true;
}

bool SupportNPC::SeqFirstMenu(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		cursorNum = 0;
		//SUPNPC��UI��`���Ԃɂ���
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC),true);
		//�`�悷��UI��FirstMenu�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::FIRSTMENU));
	}
	//�߂���player�����Ȃ������疳������
	if (!isNearPlayer) {
		cursorNum = 0;
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//�㉺�ɃJ�[�\���ړ��������A���ڂ�I��
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		cursorNum = (cursorNum + 1) % MAXDRAWNUM;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		cursorNum = (cursorNum + MAXDRAWNUM - 1) % MAXDRAWNUM;
	}

	//hint�̃y�[�W�؂�ւ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		nowDrawPage = (nowDrawPage + 1) % maxPageNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		nowDrawPage = (nowDrawPage + maxPageNum - 1) % maxPageNum;
	}

	//���ڂ�����
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//�`�悷��UI��hint�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::HINT));
		ChangeSequence(SEQUENCE::HINT);
	}
	//��b����߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
	}
	return true;
}

bool SupportNPC::SeqHint(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//�`�悷��UI��hint�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC), static_cast<int>(UIManager::SUPNPCUI::HINT));
	}

	//�߂���player�����Ȃ������疳������
	if (!isNearPlayer) {

		cursorNum = 0;
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::SUPNPC));
		ChangeSequence(SEQUENCE::WAIT);
		return false;
	}

	//hint�I����ʂɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return false;
}

void SupportNPC::DrawWaitSequence()
{
	SetFontSize(50);
//	DrawStringEx(20, 20, -1, "SupNPC:Wait");
	SetFontSize(16);
}

void SupportNPC::DrawFirstMenuSequence()
{
	/*tnl::Vector3 drawPos = {};*/

	//hint�̐��������j���[���o��
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;
	if (mainSequence.isStart()) {
		firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::SUPNPC));

		//2�Ԃ��^�C�g����`�悷��UI�g�Ȃ̂ł��������擾����
		auto& leftTopPos = firstMenuGraphics[1]->GetLeftTopPos();
		drawSpeakTitlePos = tnl::Vector3(leftTopPos.x + 50, leftTopPos.y+20, 0);
	}

	DrawNpcTextName(MAXDRAWNUM, nowDrawPage, drawSpeakTitlePos);

	DrawRotaGraph(drawSpeakTitlePos.x - 25, drawSpeakTitlePos.y + 10 + (cursorNum * 20), 0.25, 0, cursorGh, true);

	SetFontSize(50);
	//DrawStringEx(20, 20, -1, "SupNPC:MENU");
	SetFontSize(16);
}

void SupportNPC::DrawHintSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;
	std::vector<std::shared_ptr<GraphicUI>>hintMenuGraphics;
	if (mainSequence.isStart()) {
		firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::SUPNPC));
		hintMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::SUPNPC));

		//2�Ԃ��^�C�g����`�悷��UI�g�Ȃ̂ł��������擾����
		auto& titleLeftTopPos = firstMenuGraphics[1]->GetLeftTopPos();
		drawSpeakTitlePos = tnl::Vector3(titleLeftTopPos.x + 50, titleLeftTopPos.y + 20, 0);

		//3�Ԃ�������`�悷��UI�g�Ȃ̂ł��������擾����
		auto& leftTopPos = hintMenuGraphics[2]->GetLeftTopPos();
		drawSpeakPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y+20, 0);

		selectHint = nowDrawPage * MAXDRAWNUM + cursorNum;
	}
	DrawNpcTextName(MAXDRAWNUM, nowDrawPage, drawSpeakTitlePos);
	DrawNpcText(selectHint, drawSpeakPos);

	SetFontSize(50);
//	DrawStringEx(20, 20, -1, "SupNPC:Hint");
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
