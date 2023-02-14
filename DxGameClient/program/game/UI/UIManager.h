#pragma once
/*
�Q�[������UI�\���A�ێ����s���N���X

UI�𑝂₷�Ƃ���"UISERIES"��"NOWDRAWUIs","SERIESINNUM","canDrawUI"�ɒǉ�������ŁA���ꕨ�ƃp�X��p�ӂ��邱��
���̌����҂ƃp�X�̎擾�֐�"GetUIVector"��"GetLoadPass"���X�V���邱��
*/
#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"../../dxlib_ext/dxlib_ext.h"

class GraphicUI;

class UIManager
{
public:
	// �C���X�^���X�̎擾
	static UIManager* GetInstance();

	// �j��
	void Destroy();

	//���t���[�����s����X�V�֐�
	void Update();
	//���t���[���`�悷��֐�
	void Draw();

	//�`�悷��UI��ύX����֐�
	void ChangeDrawUI(int MenuSeries, int UINum);

	//UI�̕`��ې؂�ւ�
	inline void ChangeCanDrawUI(int series, bool swich = false) {
		//����false&true�ɂ���Ɨ�����true�ɕς���
		if (swich && !canDrawUI[series]) {
			canDrawUI[series] = true;
			return;
		}
		//����true�Ȃ��false�ɂ���Ɨ�����false�ɂ���
		else if (!swich && canDrawUI[series])canDrawUI[series] = false;
	}

	//�`��ێ擾
	inline bool GetCanDraw() {
		return canDrawUI;
	}

	//UI�̓��ꕨ���擾����֐�
	const std::vector<std::vector<std::shared_ptr<GraphicUI>>>& GetUI(int series);

	//���ݕ`�撆��UI���擾����֐�
	const std::vector<std::shared_ptr<GraphicUI>>& GetNowDrawGraphic(int series);

public:
	//�ǂ̋@�\��UI��
	enum class UISERIES :uint32_t {
		MENU,
		SUPNPC,
		DISASSEMBLYNPC,
		GUARDNPC,
		MAX
	};

	enum class MENUUI :uint32_t {
		TOP,
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};
	enum class SUPNPCUI :uint32_t {
		FIRSTMENU,
		HINT,
		MAX
	};

	enum class DISASSEMBLYNPCUI :uint32_t {
		FIRSTMENU,
		SELECTITEM,
		CHECK,
		RESULT,
		MAX
	};
	enum class GUARDNPCUI :uint32_t {
		FIRSTMENU,
		TALK,
		MAX
	};

private:
	static UIManager* instance;

	//���ݕ\������UI�ԍ��̔z��
	std::vector<int> NOWDRAWUIs = { nowDrawMenuUI,nowDrawSupNPCUI,nowDrawDisassemblyNpcUI,nowDrawGuardNpcUI };


	//�@�\���Ƃ�UI�̐��̔z��
	const std::vector<int>SERIESINNUM = { static_cast<int>(MENUUI::MAX),static_cast<int>(SUPNPCUI::MAX),
											static_cast<int>(DISASSEMBLYNPCUI::MAX),static_cast<int>(GUARDNPCUI::MAX) };



	//-----���ݑI�𒆂�ui�ԍ�-----
	int nowDrawMenuUI = static_cast<int>(MENUUI::TOP);
	int nowDrawSupNPCUI = static_cast<int>(SUPNPCUI::FIRSTMENU);
	int nowDrawDisassemblyNpcUI = static_cast<int>(DISASSEMBLYNPCUI::FIRSTMENU);
	int nowDrawGuardNpcUI = static_cast<int>(GUARDNPCUI::FIRSTMENU);

	//-----UI��ۑ�����񎟌��z��-----
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedMenuUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedSupNPCUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedDisassemblyNPCUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedGuardNPCUI;

	//�_�~�[
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> errorVec;

	//-----���[�h����UI�̃p�X�z��-----
	//UI
	const std::string MENUPASS[static_cast<uint32_t>(MENUUI::MAX)] = { "Csv/UI/UseUI/TopUI.csv","Csv/UI/UseUI/StatusUI.csv","Csv/UI/UseUI/InventoryUI.csv","Csv/UI/UseUI/EquipUI.csv" };
	//Sup
	const std::string SUPNPCUIPASS[static_cast<uint32_t>(SUPNPCUI::MAX)] = { "Csv/UI/NPC/SuportNPCFirstMenu.csv","Csv/UI/NPC/SuportNPCHintMenu.csv" };
	//���
	const std::string DISNOCUIPASS[static_cast<uint32_t>(DISASSEMBLYNPCUI::MAX)] = { "Csv/UI/NPC/DisAssemblyNPCFirstMenu.csv","Csv/UI/NPC/DisAssemblyNPCSelect.csv",
																					"Csv/UI/NPC/DisAssemblyNPCCheck.csv","Csv/UI/NPC/DisAssemblyNPCResult.csv", };
	//���
	const std::string GUARDNPCUIPASS[static_cast<uint32_t>(GUARDNPCUI::MAX)] = { "Csv/UI/NPC/GuardNPCFirstMenu.csv","Csv/UI/NPC/GuardNPCTalk.csv" };

	//���[�h���̊g�傠��Ȃ�
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//UI��`�悷�邩�ǂ��� ��ނ���
	bool canDrawUI[static_cast<int>(UISERIES::MAX)] = { false,false,false,false };

	const std::string err[2] = { "err","err" };

private:

	UIManager();
	~UIManager();

	//Csv�����UI���[�h�֐�
	void LoadUI(std::string Pass, std::vector<std::vector<std::shared_ptr<GraphicUI>>>& putInVector, int UIType);

	//UI�̓��ꕨ���擾����֐�
	std::vector<std::vector<std::shared_ptr<GraphicUI>>>& GetUIVector(int series);

	//�p�X�̔z����擾����֐�
	const std::string* GetLoadPass(int series);

};

