#include "scene_base.h"
#include<memory>

class Player;

class SceneManager;

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

private:
	//std::shared_ptr<Player>player = nullptr;
	
	bool init = false;
	SceneManager* sManager = nullptr;

	int gh = 0;

};
