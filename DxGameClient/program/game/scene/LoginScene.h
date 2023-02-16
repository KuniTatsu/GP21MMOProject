#pragma once
#include"scene_base.h"
#include"../../dxlib_ext/dxlib_ext.h"

//UUID���t�@�C������ǂݍ��݁A���݂���Ȃ炻�̃L�����̃f�[�^���T�[�o����󂯎���Đ������A�}�b�v�V�[���ɉf��
//�����Ȃ�V�����v���C���[�����V�[�N�G���X�Ɉړ�����

class LoginScene :public SceneBase
{
public:
	LoginScene();
	~LoginScene();

	void initialzie();
	void update(float delta_time);
	void render();


private:

	int g_InputHandle = 0;

	char buffer[100] = {};

	std::vector<int>charaIcon;

	//���O����͂��I�������
	bool checkNameInput = false;

	tnl::Sequence<LoginScene>mainSequence = tnl::Sequence<LoginScene>(this, &LoginScene::SeqCheckHaveUUID);

	enum class SEQUENCE :uint32_t {
		CHECKUUID,
		INPUTNAME,
		CHECKNAME,
		SELECTGRAPHIC,
		CHECKGRAPHIC,
		WAITCHANGESCENE,
		MAX
	};

	//�I�񂾉摜�̔ԍ�
	int selectCharaIconNum = -1;

	//�J�ڃt���O
	bool canChangeScene = false;
	//�V�[���J�ڂ܂ł̎���
	const float BUFFERTIME = 2.0f;

	//�V�[���J�ڒ���deltatime
	float bufferDeltaTime = 0.0f;

	//�v���C���[�f�[�^�𑗂�����
	bool isSend = false;

private:

	//�V�[�N�G���X�ύX�֐�
	void ChangeSequence(int sequence);

	//�`��֐�
	void DrawWritingMessage();

	//����UUID�������Ă��邩�ǂ����m���߂�V�[�N�G���X
	bool SeqCheckHaveUUID(const float deltatime);

	//���O�����߂�V�[�N�G���X
	bool SeqInputCharaName(const float deltatime);

	//���O�m�F�V�[�N�G���X
	bool SeqCheckNameSelect(const float deltatime);

	//�摜����V�[�N�G���X
	bool SeqSelectGraphic(const float deltatime);

	//�摜�m�F�V�[�N�G���X
	bool SeqCheckGraphic(const float deltatime);

	//�J�ڑ҂��V�[�N�G���X
	bool SeqWaitChangeScene(const float deltatime);

};

