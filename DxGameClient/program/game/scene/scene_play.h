#pragma once
#include"scene_base.h"
class Scene_Play : public SceneBase {
public:
	Scene_Play(){}
	~Scene_Play() {}

	void initialzie()override;
	void update(float delta_time)override;
	void render()override;

};