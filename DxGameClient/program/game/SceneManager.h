#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class SceneManager
{
public:

	// �C���X�^���X�̎擾
	static SceneManager* GetInstance();

	// �j��
	static void Destroy();

	// �X�V
	void Update(float delta_time);
	//�`��
	void Draw();

	// �V�[���̕ύX
	// arg1... SceneBase ���p�������N���X�C���X�^���X
	void chengeScene(SceneBase* next);

private:

	static SceneManager* instance;

	int imgBlack = 0;

	//�t�F�[�h�p�ϐ�
	int col = 0;

	SceneManager();
	~SceneManager();

	// ��ʑJ�ډ��o�̎���
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float sceneTransitionTime = 0;
	float sceneTransitionAlpha = 1.0f;

	tnl::Sequence<SceneManager> sequence =
		tnl::Sequence<SceneManager>(this, &SceneManager::SeqSceneInTransition);

	// ��ʑJ��( �t�F�[�h�C���v���Z�X )
	bool SeqSceneInTransition(const float delta_time);

	// �Q�[���v���Z�X
	bool SeqUpdate(const float delta_time);

	// ��ʑJ��( �t�F�[�h�A�E�g�v���Z�X )
	bool SeqSceneOutTransition(const float delta_time);

	// ���݂̃V�[��
	SceneBase* nowScene = nullptr;
	// �\��V�[��
	SceneBase* nextScene = nullptr;

};

