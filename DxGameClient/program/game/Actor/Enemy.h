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
	Enemy(tnl::Vector3 SpawnPos,double attackRange, float attack, float defence, float speed);
	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

private:
	int img_Ghost = 0;
	bool onFollowToPlayer = false;
	
	/*�ړ��X�s�[�h*/
	float SPEED = 0;

	unsigned int ChangedColor();

	GameManager* gManager = nullptr;
private:
	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	void EnemyMove();
};