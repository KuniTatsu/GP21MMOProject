#pragma once
#include<vector>
#include<memory>

class NPC;

class NPCManager
{
public:
	// インスタンスの取得
	static NPCManager* GetInstance();

	// 破棄
	void Destroy();

	//NPCのUpdate
	void Update();

	//NPCの会話文のみの描画関数 UIが表示されるときのみ描画すること
	void DrawSpeak();

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

	//各NPCのPlayer隣接チェック
	void CheckNearPlayer(float x, float y);

private:
	NPCManager();
	~NPCManager();
private:
	static NPCManager* instance;

	std::vector<std::shared_ptr<NPC>>NpcList;

};

