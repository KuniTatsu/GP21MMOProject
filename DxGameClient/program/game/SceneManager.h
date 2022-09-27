#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class SceneManager
{
public:

	// インスタンスの取得
	static SceneManager* GetInstance();

	// 破棄
	static void Destroy();

	// 更新
	void Update(float delta_time);
	//描画
	void Draw();

	// シーンの変更
	// arg1... SceneBase を継承したクラスインスタンス
	void chengeScene(SceneBase* next);

private:

	static SceneManager* instance;

	int imgBlack = 0;

	//フェード用変数
	int col = 0;

	SceneManager();
	~SceneManager();

	// 画面遷移演出の時間
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float sceneTransitionTime = 0;
	float sceneTransitionAlpha = 1.0f;

	tnl::Sequence<SceneManager> sequence =
		tnl::Sequence<SceneManager>(this, &SceneManager::SeqSceneInTransition);

	// 画面遷移( フェードインプロセス )
	bool SeqSceneInTransition(const float delta_time);

	// ゲームプロセス
	bool SeqUpdate(const float delta_time);

	// 画面遷移( フェードアウトプロセス )
	bool SeqSceneOutTransition(const float delta_time);

	// 現在のシーン
	SceneBase* nowScene = nullptr;
	// 予約シーン
	SceneBase* nextScene = nullptr;

};

