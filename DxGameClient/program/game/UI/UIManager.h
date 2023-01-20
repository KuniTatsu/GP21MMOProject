#pragma once
/*
�Q�[������UI�\���A�ێ����s���N���X
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
	void ChangeDrawUI(int UINum);

	//UI�̕`��ې؂�ւ�
	inline void ChangeCanDrawUI() {
		if (!canDrawUI) {
			canDrawUI = true;
			return;
		}
		canDrawUI = false;
	}

	//�`��ێ擾
	inline bool GetCanDraw() {
		return canDrawUI;
	}

private:
	static UIManager* instance;

	enum class UI :uint32_t {
		TOP,
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};

	int nowDrawUI = static_cast<int>(UI::TOP);

	//���[�h���̊g�傠��Ȃ�
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};
	//�ǂݍ���UI�̔z��
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedUI;
	//UI���[�h�Ώۂ̃p�X
	const std::string RELOADPASS[static_cast<uint32_t>(UI::MAX)] = { "Csv/UI/UseUI/TopUI.csv","Csv/UI/UseUI/StatusUI.csv","Csv/UI/UseUI/InventoryUI.csv"
																	,"Csv/UI/UseUI/EquipUI.csv" };

	//UI��`�悷�邩�ǂ���
	bool canDrawUI = false;
private:

	UIManager();
	~UIManager();

	//Csv�����UI���[�h�֐�
	void LoadUI(std::string Pass, int UIType);



};

