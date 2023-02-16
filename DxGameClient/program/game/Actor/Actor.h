#pragma once

#include<functional>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class Camera;
class ActorData;

class Actor :public std::enable_shared_from_this<Actor>
{
	//getter�Ȃǂ͂����ɏ���
public:
	Actor();
	virtual~Actor() {}

	//������Ԃ̊l��
	inline bool& GetIsLive() {
		return isLive;
	}
	//���S����Z�b�g�֐�
	inline void	SetIsLive(bool IsLive) {
		isLive = IsLive;
	}

	//�`����W�̎擾
	inline tnl::Vector3& GetPos() {
		return drawPos;
	}
	//�`����W�̃Z�b�g
	inline void	SetPos(tnl::Vector3 Pos) {
		drawPos = Pos;
	}
	//���[�J�����W�̎擾
	inline tnl::Vector3& GetLocalPos() {
		return localPos;
	}
	//���[�J�����W�̃Z�b�g
	inline void	SetLocalPos(tnl::Vector3 Pos) {
		localPos = Pos;
	}
	//actorData�̎擾
	inline const std::shared_ptr<ActorData>GetActorData() {
		return myData;
	}
	void SetActorData(float attack, float defence, float moveSpeed);

	void SetActorAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	//type�̎擾
	inline int GetActorType() {
		return actorType;
	}
	inline void SetActorType(int type) {
		if (type > 1)return;
		if (type == actorType)return;
		actorType = type;
	}

	//�L�����摜�̎l�_�̍��W�����߂�֐� ����,�E��,����,�E��
	std::vector<tnl::Vector3> GetCharaEdgePos();

	//�����Ă�������̎擾
	inline int GetDir() {
		return static_cast<int>(myExDir);
	}

	void SetCircleSize(tnl::Vector3& size);

	//���a�擾
	inline float GetCircleSize() {
		return circleSize;
	}

	//�ʏ�U���Ԋu�̕ύX�֐�
	inline void SetCanAttackTime(float time) {
		if (time <= 0.0f)return;
		canAttackTime = time;
	}
	//�ʏ�U���Ԋu�̎擾�֐�
	inline float GetCanAttackTime(float time) {
		return canAttackTime;
	}

	inline void SetName(std::string Name) {
		name = Name;
	}

	inline std::string GetName() {
		return name;
	}

	inline const std::vector<int>& GetGhs() {
		return ghs;
	}

	//*******�������z�֐� �p����Ŏ���************//
	virtual void Update() = 0;

	virtual void Draw(Camera* camera) = 0;

	virtual void Init() = 0;

	//�p����Ŏg������private�ȕϐ��͂����ɏ���
protected:
	//�`����W
	tnl::Vector3 drawPos;

	//���[�J�����W
	tnl::Vector3 localPos;

	//test
	std::vector<tnl::Vector3> bufPos;

	//���O
	std::string name = "";

	//�v���C���[���G��
	int actorType = 0;//�f�t�H���g�̓v���C���[


	//�L�����N�^�[�摜�̕� �����l�̓v���C���[�̊�{�̑傫��
	//����
	float width = 32.0f;
	//�c��
	float height = 32.0f;

	//�摜�n���h��
	int gh = 0;

	//�A�j���[�V�����֌W
	//�A�j���[�V�����֑ؑ��x
	const int actSpeed = 20;
	//���ۂɍ��`�撆�̃O���t�B�b�N�n���h��
	int drawGh = 0;
	//���݂̐؂�ւ��^�C�}�[
	float actWait = actSpeed;
	//�`�悷��A�j���[�V�����z��̃C���f�b�N�X�ԍ�
	int actIndex = 0;

	////�A�j���[�V����������X�s�[�h �W����1
	//float decreaseAnimSpeed = 1;

	//�A�j���[�V�����̍Đ����[�h
	enum class ANIMMODE {
		NORMAL,
		FAST2X,
		FAST3X,
		HALF,
		STOP,
		MAX
	};

	//���̃A�j���[�V�����̍Đ����[�h
	int nowAnimMode = static_cast<int>(ANIMMODE::NORMAL);

	//���[�h���Ƃ̃X�s�[�h
	const float ANIMSPEED[static_cast<int>(ANIMMODE::MAX)] = { 1.0,2.0,3.0,0.5,0 };

	//�ʏ�U���̌��m�Ԋu
	float canAttackTime = 1.0f;
	//�ʏ�U���̌��݂̃C���^�[�o��
	float attackInterval = 0.0f;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//�����蔻��p�̔��a
	float circleSize = 0.0f;

	//����
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};


	//���� 8�����o�[�W���� ��]��O��@���������g������
	enum class EXDIR :uint32_t {
		LEFTTOP,
		LEFT,
		LEFTBOTTOM,
		BOTTOM,
		RIGHTBOTTOM,
		RIGHT,
		RIGHTTOP,
		TOP,
		MAX
	};

	//�U���^�C�v
	enum class ATTACKTYPE {
		MELEE,
		RANGE,
		MAX
	};
	//�����̌����Ă������
	DIR myDir = DIR::DOWN;

	//�����̌����Ă������(8����Ver) �������ō��㓮��������
	EXDIR myExDir = EXDIR::TOP;

	//�U���^�C�v->�����Ă��镐��̎�� �����l�͋ߐ�
	ATTACKTYPE myType = ATTACKTYPE::MELEE;

	//�e��Actor�̃f�[�^
	std::shared_ptr<ActorData> myData = nullptr;

	//�����Ă�������̋����̃I�t�Z�b�g ��,�E,��,��
	const tnl::Vector3 VECOFFSET[4] = { tnl::Vector3(1,-1,0),tnl::Vector3(1,1,0),tnl::Vector3(1,1,0),tnl::Vector3(-1,1,0) };

	//�ʏ�U���G�t�F�N�g�p�����I�t�Z�b�g
	tnl::Vector3 EFFECTOFFSET[8] = {};

	//�A�j���[�V��������gh �{���͂��������g��
	std::vector<int>ghs;


	//���̃N���X���ł����g��Ȃ��֐��͂����ɏ���
private:


	//�����Ă�������̔C�Ӎ��W���擾����֐�
	tnl::Vector3 GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance);

	//������W�ƁA�����Ƃ̍ŋߓ_�Ƃ̈�ԋ߂��_�����߂�֐�
	tnl::Vector3 GetNearestPoint(tnl::Vector3& Pos, std::vector<tnl::Vector3>& boxPos);

	//�ʏ�U���p�G�t�F�N�g�p�̃I�t�Z�b�g�����߂�֐�
	void SetDefaultAttackOffset();

	//�p����Ŏg���֐�����private�Ȃ��̂͂����ɏ���
protected:

	//X��Y���������Ԃ��֐�
	uint32_t GetExDir(float x, float y);

	void SetExDirFromInt(int dir);

	//X��Y���玩���̌����Ă��������ύX����֐�
	void SetExDir(float x, float y);

	//������������Ă��������ύX����֐�
	void SetExDir(int dir);

	//�A�j���[�V�������[�h��ύX����֐�
	void ChangeAnimMode(int changeMode);

	//��{�U���֐�	
	void DefaultAttack();

	//�ʏ�U���̃C���^�[�o���X�V
	void UpdateAttackInterval(const float deltatime);

	//��{�U���̋ߐڃ^�C�v�͈̔͂��v�Z����֐� ����,�E��,����,�E���̏�
	std::vector<tnl::Vector3>GetMeleeAttackBox();
	//�A�j���[�V�����X�V�֐�
	void Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed = 20);

	/*�}�b�v�ƃL�����N�^�[�̓����蔻��*/
	bool HitMaptoCharacter(tnl::Vector3& pos);

};

