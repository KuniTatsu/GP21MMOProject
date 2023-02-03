#pragma once
#include<vector>
#include<memory>

class NPC;

class NPCManager
{
public:
	// インスタンスの取得
	static NPCManager* GetInstance();

	enum class NPCTYPE {
		SUPPORT,
		DISASSEMBLY,
		GUARD,
		MAX
	};
	std::shared_ptr<NPC>CreateNPC(int npcType, float x, float y, int ghNum);

	//NPCリストの取得
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

