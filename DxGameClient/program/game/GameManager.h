#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class SceneManager;
class GameManager {
private :
	GameManager();
	~GameManager();
	static GameManager* instance;

	SceneManager* sManager = nullptr;

public :

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

public :

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��


};




