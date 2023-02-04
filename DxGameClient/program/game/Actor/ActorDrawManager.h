#pragma once
#include<list>
#include<memory>

class Actor;
class Camera;

class ActorDrawManager
{
public:
	// �C���X�^���X�̎擾
	static ActorDrawManager* GetInstance();

	//�`��Ώۂɒǉ�����
	void AddDrawActorList(std::shared_ptr<Actor> actor);
	//�n���ꂽActor��T���ĕ`��Ώۂ�������֐�
	void RemoveDrawActorList(std::shared_ptr<Actor> removeActor);
	//Actor���ׂĂ̕`��
	void DrawActorList(Camera* camera);

private:
	ActorDrawManager();
	~ActorDrawManager();

	static ActorDrawManager* instance;

	//Actor�̕`��Ώۃ��X�g
	std::list<std::shared_ptr<Actor>>drawActorList;
};

