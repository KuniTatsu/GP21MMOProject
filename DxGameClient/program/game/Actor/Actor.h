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
	inline void	SetIsLive() {
		isLive = false;
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
	inline std::shared_ptr<ActorData>GetActorData() {
		return myData;
	}
	void SetActorData(double attackRange, float attack, float defence, float moveSpeed);

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
	int actWait = actSpeed;
	//�`�悷��A�j���[�V�����z��̃C���f�b�N�X�ԍ�
	int actIndex = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//����
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	//���� 8�����o�[�W���� ��]��O��
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


	//���̃N���X���ł����g��Ȃ��֐��͂����ɏ���
private:
	//�ړ��֐� �㉺���E

	void MoveUp();

	void MoveRight();

	void MoveDown();

	void MoveLeft();

	void MoveDummy() {};

	//�����Ă�������̔C�Ӎ��W���擾����֐�
	tnl::Vector3 GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance);

	//�p����Ŏg���֐�����private�Ȃ��̂͂����ɏ���
protected:
	//�ړ��֐��̃|�C���^�z��
	const std::function< void(Actor*) > MOVEFUNC[4] = { &Actor::MoveUp,&Actor::MoveRight,&Actor::MoveDown,&Actor::MoveLeft };

	//X��Y���������Ԃ��֐�
	uint32_t GetExDir(float x, float y);

	//X��Y���玩���̌����Ă��������ύX����֐�
	void SetExDir(float x, float y);

	//��{�U���֐�	
	void DefaultAttack();

	//�A�j���[�V�����X�V�֐�
	void Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed = 20);


};

