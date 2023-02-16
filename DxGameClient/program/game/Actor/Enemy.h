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

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	inline int GetIdentId() {
		return identId;
	}
	//�ʒu���W�̓���
	void MoveEnemyFromServerInfo(float x, float y, int dir);
	//�X�e�[�^�X�̓���
	void ChangeStatusFromServerInfo(float moveHP);

private:
	int img_Ghost = 0;
	bool onFollowToPlayer = false;

	std::vector<int>myAnimationGh;

	/*�ړ��X�s�[�h*/
	float SPEED = 0;

	int identId = -1;
	
	unsigned int ChangedColor();

	GameManager* gManager = nullptr;

private:
	//void Move();

	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	void EnemyMove();

};