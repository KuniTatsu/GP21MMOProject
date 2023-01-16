#pragma once
#include"Actor.h"

class Camera;
class GameManager;


//fukushi_develop
//gManager->GetVectorToPlayer�������ăv���C���[�ւ̕����x�N�g�����擾���A�����̎���moveSpeed���|�����l��1�t���[�����Ɉړ�����ړ���
//Move�֐���V�������A���̒��ɂ��̒l���擾����R�[�h���������A�ړ�������
//move�֐���update�̒��ŌĂ�orgameManager��update�Ń��X�g����Ă�

class Enemy : public Actor {
public:

	//Enemy(tnl::Vector3 SpawnPos);
	Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed);
	Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed, int IdentId);
	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	inline int GetIdentId() {
		return identId;
	}
	//�ʒu���W�̓���
	void MoveEnemyFromServerInfo(float x,float y,int dir);
	//�X�e�[�^�X�̓���
	void ChangeStatusFromServerInfo(float moveHP);

private:
	int img_Ghost = 0;

	int identId = -1;

	unsigned int ChangedColor(bool atack);

	GameManager* gManager = nullptr;
private:
	void SearchCircle(int SpawnPosX, int SpawnPosY, double atackRange);
	//void Move();
};