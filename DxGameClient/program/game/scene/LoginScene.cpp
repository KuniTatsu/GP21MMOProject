#include "LoginScene.h"
#include<fstream>
#include"../GameManager.h"
#include"../ResourceManager.h"
#include"../SceneManager.h"
#include"../scene/scene_map.h"

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
}

void LoginScene::initialzie()
{
	// �L�[���̓n���h�������(�L�����Z������S�p�����L�萔�l���͂Ȃ�)
	g_InputHandle = MakeKeyInput(30, true, false, false);
	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(g_InputHandle);

	charaIcon = ResourceManager::GetInstance()->GetGraphicVector(static_cast<int>(ResourceManager::RESOUCETYPE::CHARAICON));
}

void LoginScene::update(float delta_time)
{
	mainSequence.update(delta_time);
	if (canChangeScene)SceneManager::GetInstance()->chengeScene(new Scene_Map());
}

void LoginScene::render()
{
}

void LoginScene::ChangeSequence(int sequence)
{
	if (sequence >= static_cast<int>(SEQUENCE::MAX))return;

	switch (sequence)
	{
	case static_cast<int>(SEQUENCE::CHECKUUID):
		mainSequence.change(&LoginScene::SeqCheckHaveUUID);
		break;
	case static_cast<int>(SEQUENCE::INPUTNAME):
		mainSequence.change(&LoginScene::SeqInputCharaName);
		break;
	case static_cast<int>(SEQUENCE::CHECKNAME):
		mainSequence.change(&LoginScene::SeqCheckNameSelect);
		break;
	case static_cast<int>(SEQUENCE::SELECTGRAPHIC):
		mainSequence.change(&LoginScene::SeqSelectGraphic);
		break;
	case static_cast<int>(SEQUENCE::CHECKGRAPHIC):
		mainSequence.change(&LoginScene::SeqCheckGraphic);
		break;
	case static_cast<int>(SEQUENCE::WAITCHANGESCENE):
		mainSequence.change(&LoginScene::SeqWaitChangeScene);
		break;
	default:
		break;
	}
}

bool LoginScene::SeqCheckHaveUUID(const float deltatime)
{
	//�T�[�o�[�֐ڑ�
	GameManager::GetInstance()->ConnectServer();

	//ofstream�^�̕ϐ� �J�����t�@�C�����W�J�����
	std::ifstream loadfile;
	//���΃p�X
	std::string filename = "save/myUUID.txt";

	std::string UUID = "";


	//�p�X������͐ݒ�Ńt�@�C�����J��
	loadfile.open(filename, std::ios::in);

	if (loadfile) {
		loadfile >> UUID;

		//�J�����t�@�C���̊J��
		loadfile.close();
	}

	//UUID��ǂݍ��߂���
	if (UUID != "") {

		auto gManager = GameManager::GetInstance();

		//�T�[�o�[����UUID���g���ăX�e�[�^�X���擾,�A���Ă�������Player�𐶐�
		gManager->GetPlayerInfo(UUID);

		//UUID��o�^
		gManager->SetClientUUID(UUID);

		ChangeSequence(static_cast<int>(SEQUENCE::WAITCHANGESCENE));
	}
	//���߂Ẵ��O�C����������
	else {
		//�A�J�E���g�쐬�V�[�N�G���X�Ɉڂ�
		ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
	}

	return true;
}

bool LoginScene::SeqInputCharaName(const float deltatime)
{
	if (mainSequence.isStart()) {
		// ���͕����������������
		SetKeyInputString("", g_InputHandle);
	}

	//��ʂɕ`�悷�郁�b�Z�[�W
	SetFontSize(25);
	DrawStringEx(400, 200, -1, "���O����͂��Ă�������");
	SetFontSize(16);

	int hoge = CheckKeyInput(g_InputHandle);

	if (hoge != 0) {

		//����I�����̂݃��b�Z�[�W��ۑ��A���M����
		if (hoge == 1) {
			//���͂��ꂽ�������ۑ�����
			GetKeyInputString(buffer, g_InputHandle);

			std::string buf = buffer;

			if (buf != "") {
				GameManager::GetInstance()->SetPlayerName(buf);
				checkNameInput = true;
			}
		}
		ChangeSequence(static_cast<int>(SEQUENCE::CHECKNAME));
	}
	else {
		DrawWritingMessage();
	}

	return true;
}


bool LoginScene::SeqCheckNameSelect(const float deltatime)
{
	//�������O����͂��Ă��Ȃ������ꍇ
	if (!checkNameInput) {
		DrawStringEx(400, 300, -1, "���O����͂��Ă�������");
		DrawStringEx(400, 400, -1, "Enter�Ŗ߂�");

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
		}
		return true;
	}
	//�{���ɂ��̖��O�ł������\������
	const std::string& name = GameManager::GetInstance()->GetPlayerName();

	SetFontSize(25);

	DrawStringEx(400, 200, -1, "���̖��O�Ŏn�߂Ă��ǂ��ł���? Y:�n�߂� N:�߂�");
	DrawStringEx(400, 300, -1, name.c_str());

	SetFontSize(16);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Y)) {
		ChangeSequence(static_cast<int>(SEQUENCE::SELECTGRAPHIC));
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_N)) {
		ChangeSequence(static_cast<int>(SEQUENCE::INPUTNAME));
	}
	return true;
}

bool LoginScene::SeqSelectGraphic(const float deltatime)
{
	SetFontSize(25);
	DrawStringEx(400, 200, -1, "���Ȃ��̌����ڂ�I��ł�������");
	SetFontSize(16);

	for (int i = 0; i < charaIcon.size(); ++i) {
		//2�i��
		if (i > charaIcon.size() / 2) {
			DrawRotaGraph(100 + 45 * i, 350, 1, 0, charaIcon[i], true);
		}
		//1�i��
		DrawRotaGraph(100 + 45 * i, 300, 1, 0, charaIcon[i], true);
	}

	for (int i = 0; i < charaIcon.size(); ++i) {
		//�e�摜�̒��S���W�Ƃ���}�E�X�̃N���b�N��������߂�
		tnl::Vector3 centerPos = {};
		if (i > charaIcon.size() / 2) {
			centerPos = tnl::Vector3(100 + 45 * i, 350, 0);
		}
		else {
			centerPos = tnl::Vector3(100 + 45 * i, 300, 0);
		}
		//�N���b�N���Ă�����
		if (GameManager::GetInstance()->isClickedRect(centerPos)) {
			selectCharaIconNum = i;
			ChangeSequence(static_cast<int>(SEQUENCE::CHECKGRAPHIC));
			return true;
		}
	}

	return true;
}

bool LoginScene::SeqCheckGraphic(const float deltatime)
{

	SetFontSize(25);

	DrawStringEx(400, 200, -1, "���̉摜�Ŏn�߂Ă��ǂ��ł���? Y:�n�߂� N:�߂�");
	DrawRotaGraph(512, 384, 1, 0, charaIcon[selectCharaIconNum], true);

	SetFontSize(16);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Y)) {

		//���O���T�[�o�[�֑��M
		GameManager::GetInstance()->EntryServer();
		//UUID�̎擾
		GameManager::GetInstance()->GetMyUUID();


		ChangeSequence(static_cast<int>(SEQUENCE::WAITCHANGESCENE));
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_N)) {
		ChangeSequence(static_cast<int>(SEQUENCE::SELECTGRAPHIC));
	}

	return true;
}

bool LoginScene::SeqWaitChangeScene(const float deltatime)
{
	if (mainSequence.isStart()) {
		//�T�[�o�[�ʐM�擾�p�X���b�h�̍쐬
		GameManager::GetInstance()->CreateThread();
	}


	SetFontSize(25);

	DrawStringEx(300, 384, -1, "LiveWorld�ւ悤����");
	DrawStringEx(300, 450, -1, "���E�֓]�����Ă��܂�");

	SetFontSize(16);

	bufferDeltaTime += deltatime;
	if (BUFFERTIME > bufferDeltaTime)return true;

	canChangeScene = true;

	return false;
}

void LoginScene::DrawWritingMessage()
{
	// ���̓��[�h��`��
	/*DrawKeyInputModeString(640, 480);*/

	// ���͓r���̕������`��
	DrawKeyInputString(0, 0, g_InputHandle);
}