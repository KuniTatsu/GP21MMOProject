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


class NPC :public Actor
{
public:
	NPC(float x, float y);
	~NPC();

	virtual void Update() = 0;

protected:

	inline tnl::Vector3& GetDrawPos() {
		return drawPos;
	}

private:



};

