#include "UIManager.h"
#include"../UI/GraphicUI.h"

UIManager* UIManager::instance = nullptr;
UIManager* UIManager::GetInstance()
{
	if (!instance) {
		instance = new UIManager();
	}
	return instance;
}

void UIManager::Destroy()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void UIManager::Update()
{
}

void UIManager::Draw()
{
	if (!canDrawUI)return;
	if (makedUI[nowDrawUI].empty())return;

	for (auto ui : makedUI[nowDrawUI])
	{
		ui->Draw();
	}

	//DRAWSEQUENCE[nowDrawUI](this);
}

void UIManager::ChangeDrawUI(int UINum)
{
	if (UINum >= static_cast<int>(UI::MAX))return;
	if (nowDrawUI == UINum)return;
	nowDrawUI = UINum;
}

UIManager::UIManager()
{
	makedUI.resize(static_cast<int>(UI::MAX));

	//csv���[�h
	for (int i = 0; i < static_cast<int>(UI::MAX); ++i) {
		LoadUI(RELOADPASS[i], i);
	}
}

UIManager::~UIManager()
{
	makedUI.clear();
}

void UIManager::LoadUI(std::string Pass, int UIType)
{
	//CSV�ǂݍ���
	auto loadUICsv = tnl::LoadCsv(Pass);

	//1�s�ڂ���X�^�[�g(0�s�ڂ͍��ږ�)
	for (int i = 1; i < loadUICsv.size(); ++i) {
		//------string�^�̃f�[�^��int�^��float�^�ɕϊ����A���[�J���ϐ��ɕۊǂ��鏈��----//

		//type 0:�������[�h,1:���̂܂܃��[�h
		int type = stoi(loadUICsv[i][2]);

		int allNum = stoi(loadUICsv[i][3]);
		int widthNum = stoi(loadUICsv[i][4]);
		int heightNum = stoi(loadUICsv[i][5]);
		int widthSize = stoi(loadUICsv[i][6]);
		int heightSize = stoi(loadUICsv[i][7]);

		float posX = stof(loadUICsv[i][8]);
		float posY = stof(loadUICsv[i][9]);

		int frameWidth = stoi(loadUICsv[i][10]);
		int frameHeight = stoi(loadUICsv[i][11]);

		//------------------------------------------------------------------------------//

		//UIData�N���X�𐶐�
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		//�摜�������L�΂����Ɏg��UI�̏ꍇ ->�g���R���X�g���N�^�𓝈ꂵ��
		if (type == static_cast<uint32_t>(LOADMODE::NORMAL)) {

			//GraphicUI�N���X�𐶐�(�摜���g�傹���Ɏg���ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vector�ɓo�^
			makedUI[UIType].emplace_back(newUI);
			//���̃��[�v��
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜���Ȃ��ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vector�ɓo�^
			makedUI[UIType].emplace_back(newUI);
		}
		else {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜������ꍇ
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);
			newUI->ChangeLiveUI();
			//vector�ɓo�^
			makedUI[UIType].emplace_back(newUI);
		}
	}
}


