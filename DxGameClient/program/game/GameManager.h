#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class SceneManager;

class ChatBase;
class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	SceneManager* sManager = nullptr;

public:

	ChatBase* chat = nullptr;

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

	float deltaTime = 0.0f;

public:

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��


};




