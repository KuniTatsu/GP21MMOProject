#pragma once
#include"Actor.h"

class Camera;
class GameManager;


//fukushi_develop
//gManager->GetVectorToPlayer�������ăv���C���[�ւ̕����x�N�g�����擾���A�����̎���moveSpeed���|�����l��1�t���[�����Ɉړ�����ړ���
//Move�֐���V�������A���̒��ɂ��̒l���擾����R�[�h���������A�ړ�������
//move�֐���update�̒��ŌĂ�orgameManager��update�Ń��X�g����Ă�
//Enemy�̃R���X�g���N�^�ɃO���t�B�b�N�X�n���h��int�^�ň����Ɏ����Ă���
//std::vector<int>�̎Q�Ƃ������Ɏ���

class Enemy : public Actor {
public:

	//���N���C�A���g�p�R���X�g���N�^
	Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type);

	//�T�[�o�[������������Ă��č�鎞�p
	Enemy(tnl::Vector3 SpawnPos, const std::shared_ptr<ActorData> data, std::vector<int>& ghs, int type,int IdentId);

	~Enemy();

	int createEnemy = 0;

	bool init = false;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	inline int GetIdentId() {
		return identId;
	}

	inline void SetIdentId(int IdentId) {
		identId = IdentId;
	}

	//���m���ŃG�l�~�[���f�J���Ȃ�d�l�̃Z�b�g
	inline void SetIsBig() {
		isBig = 1;
	}

	inline void SetEnemyId(int EnemyId) {
		if (enemyId != -1)return;
		enemyId = EnemyId;
	}

	inline int GetEnemyId() {
		return enemyId;
	}

	//�ʒu���W�̓���
	void MoveEnemyFromServerInfo(float x, float y, int dir);
	//�X�e�[�^�X�̓���
	void ChangeStatusFromServerInfo(float moveHP);

private:
	
	//���G�͈͂ɓ�������TRUE
	bool onFollowToPlayer = false;

	//�ǔ��^�[�Q�b�g
	std::shared_ptr<Actor> followTarget = nullptr;

	std::vector<int>myAnimationGh;

	/*�ړ��X�s�[�h*/
	float SPEED = 0;

	int identId = -1;
	//�G�l�~�[�^�C�v�̎擾
	int TYPE = 0;


	/*�U���C���^�[�o��*/
	int atackInterval = 0;
	float atackintervalLimit = 1.5f;

	//�f�J�G���ǂ��� 0:�ʏ� 1:�f�J
	int isBig = 0;

	//enemyId
	int enemyId = -1;
	
	unsigned int ChangedColor();

	GameManager* gManager = nullptr;

private:
	//void Move();

	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	
	/*Playe�ւ̒Ǐ]����*/
	void EnemyMove();

};