#include "NPCManager.h"
#include"SupportNPC.h"
#include"DisassemblyNPC.h"
#include"../ActorDrawManager.h"

NPCManager* NPCManager::instance = nullptr;
NPCManager* NPCManager::GetInstance()
{
	if (!instance) {
		instance = new NPCManager();
	}
	return instance;
}

void NPCManager::Destroy()
{

	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void NPCManager::Update()
{
	for (auto& npc : NpcList) {
		npc->Update();
	}
}

void NPCManager::DrawSpeak()
{
	for (auto& npc : NpcList) {
		npc->DrawNPCSpeak();
	}
}

std::shared_ptr<NPC> NPCManager::CreateNPC(int npcType, float x, float y, int ghNum)
{
	std::shared_ptr<NPC> ret = nullptr;
	switch (npcType)
	{
	case static_cast<int>(NPCTYPE::SUPPORT):
		//float x, float y, int ghNum, float distance
		ret = std::make_shared<SupportNPC>(x, y, ghNum);
		break;
	case static_cast<int>(NPCTYPE::DISASSEMBLY):
		//float x, float y, int ghNum, float distance
		ret = std::make_shared<DisassemblyNPC>(x, y, ghNum);
		break;

	default:
		break;
	}

	NpcList.emplace_back(ret);

	ActorDrawManager::GetInstance()->AddDrawActorList(ret);
	return ret;
}

void NPCManager::CheckNearPlayer(float x, float y)
{
	for (auto& npc : NpcList) {
		npc->CheckNearNPC(x, y);
	}
}

NPCManager::NPCManager()
{
}

NPCManager::~NPCManager()
{
	NpcList.clear();
}
