#include "DisassemblyNPC.h"

DisassemblyNPC::DisassemblyNPC(float x, float y, int ghNum, float distance) :NPC(x, y, ghNum)
{
	canHearDistance = distance;
	//NPC�̘b�����e�̓ǂݍ���
	if (loadNPCHint(static_cast<int>(NPCTYPE::DISASSEMBLY))) {
		maxPageNum = static_cast<int>(std::floor(npcSpeaks.size() / MAXDRAWNUM));
	}
}

DisassemblyNPC::~DisassemblyNPC()
{
}
