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

	// インスタンスの取得
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

public :

	// ゲーム全体で参照したい変数はここで用意


};




