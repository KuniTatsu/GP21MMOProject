#pragma once
//NPC�̊��N���X
//Actor�N���X�Ɏ��f�[�^�͂��̃N���X�̒��ŏ�������
//������	���	���
//npc���甼�a��苗���ȓ��Řb��������{�^���������Ɖ�b���j���[���o��
//������npc�͉�b�Ńq���g�������
//���npc�̓����X�^�[�̎��[��f�ރA�C�e���ɕς��Ă����
//���npc�͒Z����b�ƁA���͈͓��ɋ߂Â����G��|���Ă����


#include"../Actor.h"
#include"../../../dxlib_ext/dxlib_ext.h"


class NPC :public Actor
{
public:
	NPC(float x, float y);
	~NPC();

	virtual void Update() = 0;

protected:

	inline tnl::Vector3& GetDrawPos() {
		return drawPos;
	}

private:



};

