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
	//UI�̎�ނ��Ƃɕ`�攻��
	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		auto& vector = GetUIVector(i);
		if (vector[NOWDRAWUIs[i]].empty())continue;

		for (auto ui : vector[NOWDRAWUIs[i]])
		{
			ui->Draw();
		}
	}

	/*if (makedMenuUI[nowDrawMenuUI].empty())return;

	for (auto ui : makedMenuUI[nowDrawMenuUI])
	{
		ui->Draw();
	}*/

	//DRAWSEQUENCE[nowDrawUI](this);
}

void UIManager::ChangeDrawUI(int MenuSeries, int UINum)
{
	//�I�񂾃��j���[�V���[�Y�̍ő吔��葽����ΕύX���Ȃ�
	if (UINum >= static_cast<int>(SERIESINNUM[MenuSeries]))return;

	if (NOWDRAWUIs[MenuSeries] == UINum)return;

	nowDrawMenuUI = UINum;
	NOWDRAWUIs[MenuSeries] = UINum;
}
//�O�������UI�z��̎擾�p
const std::vector<std::vector<std::shared_ptr<GraphicUI>>>& UIManager::GetUI(int series)
{
	if (series >= static_cast<int>(UISERIES::MAX))return errorVec;

	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return makedMenuUI;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return makedSupNPCUI;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return makedDisassemblyNPCUI;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return makedGuardNPCUI;
		break;

	default:
		break;
	}

	return errorVec;
}

UIManager::UIManager()
{
	makedMenuUI.resize(static_cast<int>(MENUUI::MAX));
	makedSupNPCUI.resize(static_cast<int>(SUPNPCUI::MAX));
	makedDisassemblyNPCUI.resize(static_cast<int>(DISASSEMBLYNPCUI::MAX));
	makedGuardNPCUI.resize(static_cast<int>(GUARDNPCUI::MAX));

	//csv���[�h
	//UI�̎�ނ��ƂɃ��[�h Menu,Sup,Disassembly,guard
	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		//���ʂ�����x�N�^�[�̎Q�Ƃ��擾
		auto& vector = GetUIVector(i);
		//�p�X�̎擾
		auto pass = GetLoadPass(i);

		//��ނ̎���UI�̌��œǂݍ���
		for (int k = 0; k < SERIESINNUM[i]; ++k) {
			LoadUI(pass[k], vector, k);
		}
	}
}

UIManager::~UIManager()
{
	makedMenuUI.clear();

	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		//���ʂ�����x�N�^�[�̎Q�Ƃ��擾
		auto& vector = GetUIVector(i);
		vector.clear();
	}
}

void UIManager::LoadUI(std::string Pass, std::vector<std::vector<std::shared_ptr<GraphicUI>>>& putInVector, int UIType)
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
			putInVector[UIType].emplace_back(newUI);
			//���̃��[�v��
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜���Ȃ��ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vector�ɓo�^
			putInVector[UIType].emplace_back(newUI);
		}
		else {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜������ꍇ
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);
			newUI->ChangeLiveUI();
			//vector�ɓo�^
			putInVector[UIType].emplace_back(newUI);
		}
	}
}
//���[�h���̎Q�Ɨp
std::vector<std::vector<std::shared_ptr<GraphicUI>>>& UIManager::GetUIVector(int series)
{
	if (series >= static_cast<int>(UISERIES::MAX))return errorVec;

	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return makedMenuUI;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return makedSupNPCUI;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return makedDisassemblyNPCUI;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return makedGuardNPCUI;
		break;

	default:
		break;
	}

	return errorVec;
}

const std::string* UIManager::GetLoadPass(int series)
{
	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return MENUPASS;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return SUPNPCUIPASS;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return DISNOCUIPASS;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return GUARDNPCUIPASS;
		break;

	default:
		break;
	}
	return err;

}


