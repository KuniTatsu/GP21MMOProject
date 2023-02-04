#pragma once
#include<list>
#include<memory>

class Actor;
class Camera;

class ActorDrawManager
{
public:
	// インスタンスの取得
	static ActorDrawManager* GetInstance();

	//描画対象に追加する
	void AddDrawActorList(std::shared_ptr<Actor> actor);
	//渡されたActorを探して描画対象から消す関数
	void RemoveDrawActorList(std::shared_ptr<Actor> removeActor);
	//Actorすべての描画
	void DrawActorList(Camera* camera);

private:
	ActorDrawManager();
	~ActorDrawManager();

	static ActorDrawManager* instance;

	//Actorの描画対象リスト
	std::list<std::shared_ptr<Actor>>drawActorList;
};

