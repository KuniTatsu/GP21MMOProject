#include "NPC.h"
#include"NPCSpeak.h"
#include"../../GameManager.h"

NPC::NPC(float x, float y)
{
	//�������W�̓o�^
	drawPos.x = x;
	drawPos.y = y;

	cursorGh = GameManager::GetInstance()->LoadGraphEx("graphics/menuCursor.png");

	
}

NPC::~NPC()
{
	npcSpeaks.clear();
}

void NPC::CreateNpcSpeak(int id, std::string name, std::string speak)
{
	auto text = std::make_shared<NPCSpeak>(id, name, speak);
	npcSpeaks.emplace_back(text);
}

void NPC::DrawNpcTextName(int maxNum, int nowDrawPage, tnl::Vector3& drawPos)
{
	//maxNum�̕������c�ɕ\������
	//�z��̑傫����maxNum���傫���ꍇ�͎��̃y�[�W�ɕ`�悷��
	for (int i = 0; i < (maxNum - 1); ++i) {
		int index = (maxNum * nowDrawPage) + i;
		if (index > npcSpeaks.size())return;

		std::string text = npcSpeaks[index]->GetTextName();
		DrawStringEx(drawPos.x, drawPos.y + (20 * i), -1, text.c_str());
	}
}

void NPC::DrawNpcText(int textId,tnl::Vector3& drawPos)
{
	std::string text = npcSpeaks[textId]->GetText();

	DrawStringEx(drawPos.x, drawPos.y, -1, text.c_str());
}
