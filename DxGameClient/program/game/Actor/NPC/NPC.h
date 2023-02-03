#pragma once
//NPCの基底クラス
//Actorクラスに持つデータはこのクラスの中で処理する
//お助け	解体	門番
//npcから半径一定距離以内で話しかけるボタンを押すと会話メニューを出す
//お助けnpcは会話でヒントをくれる
//解体npcはモンスターの死骸を素材アイテムに変えてくれる
//門番npcは短い会話と、一定範囲内に近づいた敵を倒してくれる


#include"../Actor.h"
#include"../../../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>

class NPCSpeak;


class NPC :public Actor
{
public:
	NPC(float x, float y);
	~NPC();

	virtual void Update() = 0;
	virtual void Draw(Camera* camera) = 0;
	virtual void Init() = 0;

	//NPCが話す内容を登録する関数
	void CreateNpcSpeak(int id, std::string name, std::string speak);

	//NPCが話す内容が登録されているか返す関数
	inline bool IsCreatedNpcSpeak() {
		return !npcSpeaks.empty();
	}
	//NPCの話す内容のタイトルを描画する関数
	void DrawNpcTextName(int maxNum,int nowDrawPage, tnl::Vector3& drawPos);
	//NPCのタイトルごとのテキストを描画する関数
	void DrawNpcText(int textId, tnl::Vector3& drawPos);


protected:

	inline tnl::Vector3& GetDrawPos() {
		return drawPos;
	}
	int cursorGh = 0;

	//NPCが話す内容の配列
	std::vector<std::shared_ptr<NPCSpeak>> npcSpeaks;
private:

};


