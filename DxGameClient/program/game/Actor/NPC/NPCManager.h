#pragma once
#include<vector>
#include<memory>

class NPC;

class NPCManager
{
public:
	// �C���X�^���X�̎擾
	static NPCManager* GetInstance();

	enum class NPCTYPE {
		SUPPORT,
		DISASSEMBLY,
		GUARD,
		MAX
	};
	std::shared_ptr<NPC>CreateNPC(int npcType, float x, float y, int ghNum);

	//NPC���X�g�̎擾
	inline std::vector<std::shared_ptr<NPC>>& GetNPCList() {
		return NpcList;
	}

private:
	NPCManager();
	~NPCManager();
private:
	static NPCManager* instance;

	std::vector<std::shared_ptr<NPC>>NpcList;

};

