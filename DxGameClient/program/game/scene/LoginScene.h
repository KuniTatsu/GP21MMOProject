#pragma once
#include"scene_base.h"

//UUIDをファイルから読み込み、存在するならそのキャラのデータをサーバから受け取って生成し、マップシーンに映る
//無いなら新しくプレイヤーを作るシークエンスに移動する

class LoginScene :SceneBase
{
public:
	LoginScene();
	~LoginScene();

	void initialzie();
	void update(float delta_time);
	void render();

private:



};

