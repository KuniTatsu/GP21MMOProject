#pragma once
#include<list>
#include<memory>

class Actor;
class Camera;

class ActorDrawManager
{
public:
	// ƒCƒ“ƒXƒ^ƒ“ƒX‚Ìæ“¾
	static ActorDrawManager* GetInstance();

	//•`‰æ‘ÎÛ‚É’Ç‰Á‚·‚é
	void AddDrawActorList(std::shared_ptr<Actor> actor);
	//“n‚³‚ê‚½Actor‚ğ’T‚µ‚Ä•`‰æ‘ÎÛ‚©‚çÁ‚·ŠÖ”
	void RemoveDrawActorList(std::shared_ptr<Actor> removeActor);
	//Actor‚·‚×‚Ä‚Ì•`‰æ
	void DrawActorList(Camera* camera);

private:
	ActorDrawManager();
	~ActorDrawManager();

	static ActorDrawManager* instance;

	//Actor‚Ì•`‰æ‘ÎÛƒŠƒXƒg
	std::list<std::shared_ptr<Actor>>drawActorList;
};

