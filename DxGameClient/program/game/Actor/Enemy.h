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

	Enemy(tnl::Vector3 SpawnPos);
	Enemy(tnl::Vector3 SpawnPos, double attackRange, float attack, float defence, float speed, int type);
	Enemy(tnl::Vector3 SpawnPos, std::shared_ptr<ActorData>& data);
	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	void SetCircleSize(tnl::Vector3& size);

	inline float GetCircleSize() {
		return circleSize;
	}

private:
	int img_Ghost = 0;
	GameManager* gManager = nullptr;
	//�����蔻��p�̔��a
	float circleSize = 0.0f;
};