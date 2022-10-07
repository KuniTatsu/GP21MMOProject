#include "scene_base.h"

class SceneManager;

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;


private:
	SceneManager* sManager = nullptr;
};
