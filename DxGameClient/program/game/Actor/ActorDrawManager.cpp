#include "ActorDrawManager.h"
#include"Actor.h"

ActorDrawManager* ActorDrawManager::instance = nullptr;
ActorDrawManager::ActorDrawManager()
{
}

ActorDrawManager::~ActorDrawManager()
{
	drawActorList.clear();
}

ActorDrawManager* ActorDrawManager::GetInstance()
{
	if (!instance) {
		instance = new ActorDrawManager();
	}
	return instance;
}

void ActorDrawManager::AddDrawActorList(std::shared_ptr<Actor> actor)
{
	if (actor == nullptr)return;
	drawActorList.emplace_back(actor);
}
//�n���ꂽActor��T���ĕ`��Ώۂ�������֐�
void ActorDrawManager::RemoveDrawActorList(std::shared_ptr<Actor> removeActor)
{
	for (auto itr = drawActorList.begin(); itr != drawActorList.end(); ) {
		if ((*itr) == removeActor) {
			itr = drawActorList.erase(itr);
		}
		else ++itr;
	}
}

void ActorDrawManager::DrawActorList(Camera* camera)
{
	//���X�g��y���W�Ń\�[�g

	drawActorList.sort([&](std::shared_ptr<Actor>left, std::shared_ptr<Actor>right) {
		auto pos1 = left->GetPos().y;
		auto pos2 = right->GetPos().y;

		if (pos1 < pos2)return true;
		return false;
		});

	for (auto& actor : drawActorList) {
		actor->Draw(camera);
	}
}
