#include "NPCManager.h"
#include"SupportNPC.h"

NPCManager* NPCManager::instance = nullptr;
NPCManager* NPCManager::GetInstance()
{
	if (!instance) {
		instance = new NPCManager();
	}
	return instance;
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

	default:
		break;
	}

	NpcList.emplace_back(ret);
	return ret;
}

NPCManager::NPCManager()
{
}

NPCManager::~NPCManager()
{
}
