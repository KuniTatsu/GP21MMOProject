#pragma once

class Camera;

class SceneBase {
public :
	SceneBase(){}
	virtual ~SceneBase(){}
	virtual void initialzie() = 0;
	virtual void update( float delta_time ) {}
	virtual void render(Camera* camera){}

	bool isInIt = false;
};

