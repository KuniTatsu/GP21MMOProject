#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>
#include<memory>

class GameManager;
class UIData;

class GraphicUI
{
public:
	//GraphicUI(tnl::Vector3 Pos, int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData>UIData);

	//�t���[�����ɉ摜������ꍇ
	GraphicUI(int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData>FrameData, int Type);
	//�t���[�����ɉ摜�������ꍇ(�t���[���݂̂̕`��)
	GraphicUI(int FrameWidth, int FrameHeight, std::shared_ptr<UIData>FrameData, int Type);

	//-----�����������炵�����ʁ��̃R���X�g���N�^�Ɠ�������-------//
	/*
	//�t���[���������L�΂��Ȃ��ꍇ
	//GraphicUI(std::string Pass, int FrameWidth, int FrameHeight, std::shared_ptr<UIData> imageData,int Type);
	//					��
	GraphicUI(int FrameWidth, int FrameHeight, std::shared_ptr<UIData> imageData,int Type);
	*/

	~GraphicUI();

	void Draw();

	//���S���W�̎擾
	inline tnl::Vector3& GetCenterPos() {
		return centerPos;
	}
	//UI�̕��̎擾
	inline int GetUIWidth() {
		return width;
	}
	//UI�̍����̎擾
	inline int GetUIHeight() {
		return height;
	}
	//UI�̕��̍X�V
	inline void	SetUIWidth(int Width) {
		width = Width;
	}
	//UI�̍����̍X�V
	inline void	SetUIHeight(int Height) {
		height = Height;
	}

	/*inline tnl::Vector3& GetLeftTopPos() {
		return pos;
	}*/

	//UI�̒���Y���W�擾
	inline int GetUnderBottomPos() {
		return static_cast<int>(underBottomPosY);
	}

	//UI�̍���̍��W�擾
	tnl::Vector3& GetLeftTopPos();

	//CSV�o�͂̍ۂ̃f�[�^�擾�֐�
	std::string GetCsvStringData(int Id);

	//pass���g�����摜�ύX�֐�
	void ReLoadGraphic(std::string Pass);

	//�\���؂�ւ�
	void ChangeLiveUI() {
		if (!isDraw) {
			isDraw = true;
			return;
		}
		isDraw = false;
	}

private:

	GameManager* gManager = nullptr;

	//�gUI�̃f�[�^ �摜�p�X,����������,������,�c����,���T�C�Y,�c�T�C�Y
	std::shared_ptr<UIData> frameData = nullptr;

	//����UI��\�����邩�ǂ���
	bool isDraw = false;

	//vector�ւ̕������[�h
	void LoadDivGraphEx(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize);

	//�摜�ύX/�ă��[�h�֐�
	void ReLoadDivGraphic(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize);

	//UI��̍���`����W
	tnl::Vector3 pos = {};

	//UI�摜�̒��S�`����W
	tnl::Vector3 centerPos = {};

	//UI�̃^�C�v�@0:�����g��,1:���̂܂܊g��Ȃ�
	int uiType = -1;

	enum class UITYPE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//UI�̘g�̉���
	int width = 0;
	//UI�̘g�̏c��
	int height = 0;

	//UI�̘g��3����������ӂ̒���
	int splitLength = 0;

	//�g������y���W
	float underBottomPosY = 0;

	//�g�摜�n���h��
	std::vector<int>frameGh;

	//���������摜�̃p�X
	std::string buttonPass = "";
	//���������摜�̃n���h��
	int buttonGh = 0;

	//�g���ɕ`�悷��UI�摜�̃p�X
	std::string drawGraphicPass = "none";

	//�g���ɕ`�悷��UI�摜�n���h��
	int drawUIGh = -1;

	//�g�̕`��֐�
	void DrawFrame();
};

class UIData
{
public:
	UIData(std::string GraphicPass, int AllNum, int WidthNum, int HeightNum, int XSize, int YSize, float PosX, float PosY);
	~UIData();

	//GraphicUI�N���X�����private�����o�ϐ����A�N�Z�X�o����
	friend GraphicUI;

private:

	std::string pass = "";

	//�����摜�̏ꍇ��9��������̂�9,�����Ȃ��̏ꍇ��1
	int allNum = 0;

	//�����摜�̏ꍇ��3��������̂�3,�����Ȃ��̏ꍇ��1
	int widthNum = 0;
	int heightNum = 0;

	//�����摜�̏ꍇ��3������������, �������Ȃ��ꍇ�͈�ӂ̒���
	int xSize = 0;
	int ySize = 0;

	tnl::Vector3 leftTopPos = {};

};
