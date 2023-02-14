#include "NPC.h"
#include"NPCSpeak.h"
#include"../../GameManager.h"
#include"../../ResourceManager.h"

NPC::NPC(float x, float y,int ghNum)
{
	//�������W�̓o�^
	drawPos.x = x;
	drawPos.y = y;

	cursorGh = GameManager::GetInstance()->LoadGraphEx("graphics/menuCursor.png");

	//NPC�̌����ڂ�ݒ�
	ghs = ResourceManager::GetInstance()->GetCharaVectorAtGhNum(ghNum);
}

NPC::~NPC()
{
	npcSpeaks.clear();
}

bool NPC::loadNPCHint(int npcType)
{
	std::string pass = "";
	switch (npcType)
	{
	case static_cast<int>(NPCTYPE::SUP):
		pass = "csv/NpcText/hint.csv";
		break;
	case static_cast<int>(NPCTYPE::DISASSEMBLY):
		pass = "csv/NpcText/disassembly.csv";
		break;
	case static_cast<int>(NPCTYPE::GUARD):
		pass = "csv/NpcText/guard.csv";
		break;
	default:
		break;
	}

	bool ret = false;

	auto loadCsv = tnl::LoadCsv(pass);

	for (int i = 1; i < loadCsv.size(); ++i) {
		CreateNpcSpeak(std::stoi(loadCsv[i][0]), loadCsv[i][1], loadCsv[i][2]);
	}
	if (IsCreatedNpcSpeak())ret = true;
	return ret;
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
	for (int i = 0; i < (maxNum ); ++i) {
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

bool NPC::CheckNearNPC(float PlayerX, float PlayerY)
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