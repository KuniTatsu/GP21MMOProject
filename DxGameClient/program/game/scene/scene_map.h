#pragma once
#include"scene_base.h"
#include"../Actor/Camera.h"
#include<memory>
#include"../UI/UIEditor.h"

class Player;
class ActorData;
class Talent;
class Job;
class CreateMap;
class GameManager;
class EnemyManager;
class ResourceManager;
class InventoryManager;

class GraphicUI;

class Scene_Map : public SceneBase {
public:
	Scene_Map();
	~Scene_Map();

	//std::list<CreateMap*>	map;
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
private:

	std::shared_ptr<Player> player = nullptr;
	Camera camera;

	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;
	ResourceManager* rManager = nullptr;
	InventoryManager* iManager = nullptr;

	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<Scene_Map> mainSequence =
		tnl::Sequence<Scene_Map>(this, &Scene_Map::SeqWait);

	//�V�[�N�G���X�ꗗ
	enum class SEQUENCE :uint32_t {
		WAIT,
		FIRSTMENU,
		STATUS,
		INVENTORY,
		USEITEM,
		EQUIP,
		MAX
	};

	//�c�[���`�b�v�̕`��
	void DrawToolTip();

	//�e�V�[�N�G���X��Update�֐�
	bool SeqWait(const float DeltaTime);
	bool SeqFirstMenu(const float DeltaTime);
	bool SeqStatus(const float DeltaTime);
	bool SeqInventory(const float DeltaTime);
	bool SeqUseInventoryItem(const float Deltatime);

	bool SeqEquip(const float DeltaTime);

	//�V�[�N�G���X���Ƃ̕`��֐�
	void DrawWaitSequence();
	void DrawFirstMenuSequence();
	void DrawStatusSequence();
	void DrawInventorySequence();
	void DrawUseInventoryItemSequence();

	void DrawEquipSequence();

	//���݂̃V�[�N�G���X�̕`��֐�
	const std::function< void(Scene_Map*) > DRAWSEQUENCE[static_cast<int>(SEQUENCE::MAX)] =
				{&Scene_Map::DrawWaitSequence, &Scene_Map::DrawFirstMenuSequence,&Scene_Map::DrawStatusSequence,
				&Scene_Map::DrawInventorySequence,&Scene_Map::DrawUseInventoryItemSequence,&Scene_Map::DrawEquipSequence };

	

	SEQUENCE nowSequence = SEQUENCE::WAIT;

	//�V�[�N�G���X�ύX�֐�
	bool ChangeSequence(SEQUENCE NextSeq);

	//Menu�̍���
	enum class MENUINDEX :uint32_t {
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};

	int cursorGh = 0;

	//�c�[���`�b�v�̒ʏ�U���A�C�R��
	int defaultAttackIcon = 0;

	int noneIcon = 0;

	int coolDawnFade = 0;

	int escKey = 0;

	std::vector<std::shared_ptr<GraphicUI>>wait;


	//menu�e�L�X�g�̔z��
	std::vector<std::string>menuText;

	//menu�e�L�X�g�̃��[�h
	void LoadMenuTextCsv();

	//menu�e�L�X�g�̕`��
	void DrawFirstMenu();

	//menu�̃O���t�B�b�N
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;

	//���C�����j���[�̃J�[�\���Ɏg���ԍ�
	int cursorNum = 0;

	//�A�C�e���g�p�̕����̃J�[�\���Ɏg���ԍ�
	int subCursorNum = 0;

	//�`��̂��߂̈ꎞ�ۑ����W
	tnl::Vector3 bufPos = {};

	//�����K�v�ȂƂ��p�̈ꎞ�ۑ����W	
	std::vector<tnl::Vector3> bufPoses;

	//------------------------------
	//�X�e�[�^�X�V�[�N�G���X�p�`��f�[�^�̈ꎞ�ۑ���
	std::shared_ptr<ActorData>data=nullptr;
	std::string name="";
	std::vector<int>ghs = {};
	std::vector<std::shared_ptr<Talent>>talents = {};
	std::vector<std::shared_ptr<Job>>jobs = {};
	std::string highestLevelJob = "";
	std::string jobLevelText = "";
	std::vector<float>mainStatus = {};
	std::vector<std::string>names = {};

	//reset�֐�
	inline void bufDataReset() {
		data=nullptr;
		name="";
		ghs.clear();
		talents.clear();
		jobs.clear();
		highestLevelJob = "";
		jobLevelText = "";
		mainStatus.clear();
		names.clear();
	}



};