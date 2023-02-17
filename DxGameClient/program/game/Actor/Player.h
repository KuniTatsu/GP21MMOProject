#pragma once
#include"Actor.h"


class Talent;
class Job;
class Inventory;
class EquipItem;

class Player :public Actor
{
public:
	//���񃍃O�C�����̃v���C���[�쐬�R���X�g���N�^
	Player(int startX, int startY, int type);
	//�ă��O�C�����͂�����
	Player(int startX, int startY, double HP, int ghNum);
	~Player();

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	//�˔\�̎c�胉���N�����擾����֐�
	inline int GetRemainRankNum() {
		return remainRankNum;
	}
	//�˔\�̎c�胉���N�������炷�֐�
	inline void MinusRemainRank(int minusNum) {
		remainRankNum -= minusNum;
	}

	//�˔\�ꗗ���擾����֐�
	inline const std::vector<std::shared_ptr<Talent>>& GetMyTalents() {
		return myTalents;
	}

	//�E�ꗗ���擾����֐�
	inline std::vector<std::shared_ptr<Job>>& GetmyJobs() {
		return myJobs;
	}

	inline bool GetIsCreatedDummy() {
		return isCreatedDummy;
	}
	inline void	SetIsCreatedDummy() {
		isCreatedDummy = true;
	}

	void SetAttributeFromServer(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	void SetTalent();

	void SetPlayerJob(std::shared_ptr<Job>job);


	// �E�̃f�[�^���擾����֐�
	void SetPlayerInitJob();
	//Menu���J����󋵂��ǂ���
	inline bool GetCanOpenMenu() {
		return canOpenMenu;
	}
	inline void SetCanOpenMenu(bool swich) {
		if (canOpenMenu == swich)return;
		canOpenMenu = swich;
	}

	//�����A�C�e���̈ꗗ���擾����֐�
	inline std::vector<std::shared_ptr<EquipItem>>& GetEquipItems() {
		return myEquipItem;
	}

private:

	void Move();

	//���L�[�̔z��
	const tnl::Input::eKeys arrowKeys[static_cast<int>(DIR::MAX)] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,
																		tnl::Input::eKeys::KB_DOWN, tnl::Input::eKeys::KB_LEFT };

	//�L�[�擾
	inline tnl::Input::eKeys GetKeys(int KeyNum) {
		return arrowKeys[KeyNum];
	}

	//�ꎞ�ۊǗpX�ړ���
	float moveX = 0.0f;
	//�ꎞ�ۊǗpY�ړ���
	float moveY = 0.0f;

	//�ړ��X�s�[�h
	const int SPEED = 5;

	//�ړ��L�[���������Ƃ��̈ړ���
	const int MOVEAMOUNT[static_cast<int>(DIR::MAX)] = { -SPEED,SPEED,SPEED,-SPEED };


	int testGh = 0;

	//�˔\�̍ő僉���N���v��
	const int maxTalentRank = 20;

	//�˔\�̌��݂̎c�胉���N��
	int remainRankNum = maxTalentRank;

	//�v���C���[�������Ă���^�����g�̔z��
	std::vector<std::shared_ptr<Talent>>myTalents;

	//	�v���C���[�������Ă���E�̔z��
	std::vector<std::shared_ptr<Job>>myJobs;

	//���ł�Dummy������Ă��邩
	bool isCreatedDummy = false;
	//menu���J���邩
	bool canOpenMenu = true;

	std::vector<std::shared_ptr<EquipItem>>myEquipItem;
};

