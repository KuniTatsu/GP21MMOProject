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
#include<string>
#include<vector>

class NPCSpeak;


class NPC :public Actor
{
public:
	NPC(float x, float y);
	~NPC();

	virtual void Update() = 0;
	virtual void Draw(Camera* camera) = 0;
	virtual void Init() = 0;

	//NPC���b�����e��o�^����֐�
	void CreateNpcSpeak(int id, std::string name, std::string speak);

	//NPC���b�����e���o�^����Ă��邩�Ԃ��֐�
	inline bool IsCreatedNpcSpeak() {
		return !npcSpeaks.empty();
	}
	//NPC�̘b�����e�̃^�C�g����`�悷��֐�
	void DrawNpcTextName(int maxNum,int nowDrawPage, tnl::Vector3& drawPos);
	//NPC�̃^�C�g�����Ƃ̃e�L�X�g��`�悷��֐�
	void DrawNpcText(int textId, tnl::Vector3& drawPos);


protected:

	inline tnl::Vector3& GetDrawPos() {
		return drawPos;
	}
	int cursorGh = 0;

	//NPC���b�����e�̔z��
	std::vector<std::shared_ptr<NPCSpeak>> npcSpeaks;
private:

};


