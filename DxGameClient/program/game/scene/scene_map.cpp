#include "scene_map.h"
#include"../Actor/Player.h"
#include"../GameManager.h"
#include"Map.h"
#include"../EnemyManager.h"
#include"../Actor/Enemy.h"
#include"../Actor/DummyPlayer.h"
#include"../Actor/ActorData.h"
#include"../UI/UIManager.h"
#include"../UI/GraphicUI.h"
#include"../ResourceManager.h"
#include"../Actor/NPC/SupportNPC.h"
#include"../Actor/NPC/NPC.h"
#include"../Actor/NPC/NPCManager.h"
#include"../InventoryManager.h"
#include"../EffectManager.h"
#include"../Actor/ActorDrawManager.h"
#include"../DebugDef.h"
#include"../Job.h"
#include"../Talent.h"
#include"../ChatBase.h"

Scene_Map::Scene_Map()
{
	gManager = GameManager::GetInstance();
	rManager = ResourceManager::GetInstance();
	eManager = EnemyManager::GetInstance();
	iManager = InventoryManager::GetInstance();
}

Scene_Map::~Scene_Map()
{
}

void Scene_Map::initialzie()
{
#ifndef DEBUG_ON

	//�`���b�g�ڑ�
	gManager->CreateChat();
#else
	//player = gManager->GetPlayer();
	player = GameManager::GetInstance()->CreatePlayer(0);
#endif

//#ifdef DEBUG_ON
//
//	gManager->CreatePlayer(0);
//	player = gManager->GetPlayer();
//#endif 

	//�}�b�v�̐���
	gManager->CreateMap();
	//�G�l�~�[�̐���
	eManager->GetInstance();

	//player�̏����}�b�v��o�^
	gManager->SetStayMap();

#ifndef DEBUG_ON
	player = gManager->GetPlayer();
	//Dummy��������
	player->SetIsCreatedDummy();

	//�G�l�~�[�擾
	gManager->GetServerEnemyInfo();
#endif
	//NPC�̐���
	NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::SUPPORT), 180, 240, 5);

	//chat�̐���
	gManager->CreateChat();

	//UI�n��init
	menuText.clear();
	LoadMenuTextCsv();

	cursorGh = GameManager::GetInstance()->LoadGraphEx("graphics/menuCursor.png");
	firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));
	//MenuUI�̍�����擾
	auto& leftTopPos = firstMenuGraphics[0]->GetLeftTopPos();
	bufPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y + 20, 0);
}

void Scene_Map::update(float delta_time)
{
	mainSequence.update(gManager->deltaTime);

	/*Player����*/
	player->Update();

	/*Enemy����*/
	eManager->SpawnEnemy(player->GetPos());
	/*Enemy����*/
	eManager->Update(delta_time);
	/*�J��������*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	/*�G�l�~�[�̕`��*/
	if (eManager != nullptr) {
		eManager->Update(gManager->deltaTime);
	}

	auto npcManager = NPCManager::GetInstance();
	npcManager->Update();

	auto& pos = player->GetPos();
	npcManager->CheckNearPlayer(pos.x, pos.y);


	EffectManager::GetInstance()->Update(gManager->deltaTime);

	//debug
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_I)) {
		//�򑐂���ǉ�
		InventoryManager::GetInstance()->AddItemToInventory(1);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_O)) {
		InventoryManager::GetInstance()->AddItemToInventory(80000);
	}

}

void Scene_Map::render()
{



	/*�}�b�v�̕`��*/
	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(false);
		map->Draw(&camera);
	}



	//Actor�̕`��
	ActorDrawManager::GetInstance()->DrawActorList(&camera);

	EffectManager::GetInstance()->Draw(&camera);

	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(true);
		map->Draw(&camera);
	}

	/*�ǂ��̃V�[���ł��邩*///debugMessage
	/*SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");*/

	UIManager::GetInstance()->Draw();
	NPCManager::GetInstance()->DrawSpeak();

	//�V�[�N�G���X���Ƃ̕`��(UI)
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);

	EnemyManager::GetInstance()->Draw(&camera);

	//debug
	SetFontSize(30);
	//DrawStringEx(500, 500, -1, "%d", cursorNum);
	SetFontSize(16);
}

bool Scene_Map::SeqWait(const float DeltaTime)
{
	auto uiManager = UIManager::GetInstance();

	//Esc�L�[����������Menu���J��
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		//menu���J���Ȃ���ԂȂ疳������
		if (!player->GetCanOpenMenu())return false;

		//���ꂩ��J�����j���[�ȊO�̃��j���[���J���Ȃ�����
		player->SetCanOpenMenu(false);

		ChangeSequence(SEQUENCE::FIRSTMENU);
		return true;
	}

	return true;
}

bool Scene_Map::SeqFirstMenu(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		bufPoses.clear();
		/*cursorNum = 0;*/
		//MENU��UI��`���Ԃɂ���
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU), true);
		//�`�悷��UI��TOP�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::TOP));
	}
	//�㉺�ɃJ�[�\���ړ��������A���ڂ�I��
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		cursorNum = (cursorNum + 1) % static_cast<int>(MENUINDEX::MAX);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		cursorNum = (cursorNum + static_cast<int>(MENUINDEX::MAX) - 1) % static_cast<int>(MENUINDEX::MAX);
	}

	//���ڂ�����
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//�`�悷��UI��ύX
		switch (cursorNum)
		{
		case static_cast<int>(MENUINDEX::STATUS):
			UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::STATUS));
			ChangeSequence(SEQUENCE::STATUS);
			break;
		case static_cast<int>(MENUINDEX::INVENTORY):
			UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
			ChangeSequence(SEQUENCE::INVENTORY);
			break;
		case static_cast<int>(MENUINDEX::EQUIP):
			UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::EQUIP));
			ChangeSequence(SEQUENCE::EQUIP);
			break;
		default:
			break;
		}
		return true;
	}
	//Menu�����
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU));
		//���̃��j���[���J����悤�ɂ���
		player->SetCanOpenMenu(true);

		cursorNum = 0;
		ChangeSequence(SEQUENCE::WAIT);
	}
	return true;
}

bool Scene_Map::SeqStatus(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//�`�悷��UI��Status�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::STATUS));
	}




	//�g�b�v�ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::FIRSTMENU);
		return true;
	}

	return true;
}

bool Scene_Map::SeqInventory(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//�`�悷��UI��Inventory�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
	}
	//�C���x���g���̍X�V�֐� �J�[�\���̈ړ�,�C���x���g���̐؂�ւ�
	InventoryManager::GetInstance()->UpdateInventory();

	//Enter����������g�p�m�F�ֈڂ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//�C���x���g������Ȃ疳������
		if (InventoryManager::GetInstance()->isEmptyAllInventory())return true;

		ChangeSequence(SEQUENCE::USEITEM);
		//�`�悷��UI��UseItem�ɕύX
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::USEITEM));
		bufPoses.clear();
		return true;
	}

	//�g�b�v�ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		ChangeSequence(SEQUENCE::FIRSTMENU);
		return true;
	}

	return true;
}

bool Scene_Map::SeqUseInventoryItem(const float Deltatime)
{
	if (mainSequence.isStart()) {
	}

	//�͂� �� ��߂�@��I��
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		subCursorNum = (subCursorNum + 1) % 2;
	}

	//Enter����������
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//�͂���I��ł�����A�C�e�����g��
		if (subCursorNum == 0) {
			InventoryManager::GetInstance()->UseCursorItem();
			UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
			ChangeSequence(SEQUENCE::INVENTORY);
			subCursorNum = 0;
			bufPoses.clear();
			return true;
		}
		else {
			ChangeSequence(SEQUENCE::INVENTORY);
			UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
			subCursorNum = 0;
			bufPoses.clear();
			return true;
		}
	}

	//�C���x���g���ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
		bufPoses.clear();
		ChangeSequence(SEQUENCE::INVENTORY);
	}

	return true;
}

bool Scene_Map::SeqEquip(const float DeltaTime)
{
	//�g�b�v�ɖ߂�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}
	return false;
}

void Scene_Map::DrawWaitSequence()
{
}

void Scene_Map::DrawFirstMenuSequence()
{
	if (mainSequence.isStart()) {

	}
	DrawFirstMenu();
}

void Scene_Map::DrawStatusSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>statusGraphics;
	if (mainSequence.isStart()) {
		statusGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//�e���ڂ�UI�̍�����擾
		//menu���ڂ̃|�W�V����
		auto& leftTopPos1 = statusGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//�摜�Ɩ��O�Ȃǂ̘g�̃|�W�V����
		auto& leftTopPos2 = statusGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x + 50, leftTopPos2.y + 40, 0));

		//�˔\�̘g�̃|�W�V����
		auto& leftTopPos3 = statusGraphics[3]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 10, 0));

		//�E�Ƃ̘g�̃|�W�V����
		auto& leftTopPos4 = statusGraphics[4]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos4.x + 10, leftTopPos4.y + 10, 0));


		//�v���C���[�̕`��p�X�e�[�^�X���擾
		//���ʉ摜,���O,���v�E���x��,attribute,�˔\,�E
		data = player->GetActorData();

		name = "���O:" + player->GetName();

		//�摜�擾�@ghs[10]�����ʐÎ~�摜
		ghs = player->GetGhs();

		//�˔\
		talents = player->GetMyTalents();
		//�E
		jobs = player->GetmyJobs();

		//���v�E���x��
		int sumJobLevel = 0;
		int bufMax = 0;
		for (int i = 0; i < jobs.size(); ++i) {
			sumJobLevel += jobs[i]->GetJobLevel();
			if (sumJobLevel < jobs[i]->GetJobLevel()) {
				highestLevelJob = jobs[i]->GetJobName();
			}
		}
		jobLevelText = "���v�E���x��:" + std::to_string(sumJobLevel);
		highestLevelJob = "���C���E:" + highestLevelJob;

		//���C���X�e�[�^�X
		mainStatus = data->GetMainStatus();
		names = data->GetStatusName();
	}

	DrawFirstMenu();

	//�v���C���[�摜�̊O�g
	DrawBox(bufPoses[1].x - 37, bufPoses[1].y - 37, bufPoses[1].x + 37, bufPoses[1].y + 37, -1, false);
	//�v���C���[�̉摜�̕`��
	DrawRotaGraph(bufPoses[1].x, bufPoses[1].y, 2, 0, ghs[10], true);
	SetFontSize(25);
	//���O�̕`��
	DrawStringEx(bufPoses[1].x + 100, bufPoses[1].y - 20, -1, name.c_str());
	//���v�E���x���̕`��
	DrawStringEx(bufPoses[1].x + 100, bufPoses[1].y + 5, -1, jobLevelText.c_str());
	//��ԃ��x���������E���\�E�Ƃ��ĕ`��
	DrawStringEx(bufPoses[1].x - 32, bufPoses[1].y + 50, -1, highestLevelJob.c_str());

	//�X�e�[�^�X�̕`��
	SetFontSize(18);
	for (int i = 0; i < mainStatus.size(); ++i) {
		DrawStringEx(bufPoses[1].x - 32 + (i * 80), bufPoses[1].y + 100, -1, names[i].c_str());
	}
	SetFontSize(16);
	for (int i = 0; i < mainStatus.size(); ++i) {
		DrawStringEx(bufPoses[1].x - 16 + (i * 80), bufPoses[1].y + 130, -1, "%.f", mainStatus[i]);
	}
	SetFontSize(25);
	//�E�̕`�� 10�܂ŕ��ׂĕ`�悷��
	//10�𒴂�����y�[�W����� ToDO �E���ł�����`�F�b�N���邱��

	DrawStringEx(bufPoses[3].x, bufPoses[3].y, -1, "�E�ƈꗗ");

	for (int i = 0; i < jobs.size(); ++i) {
		if (jobs.empty())break;
		DrawStringEx(bufPoses[3].x, bufPoses[3].y + 40 + (i * 40), -1, jobs[i]->GetJobName().c_str());
	}
	//�˔\�̕`��
	DrawStringEx(bufPoses[2].x, bufPoses[2].y, -1, "�˔\�ꗗ");
	for (int i = 0; i < talents.size(); ++i) {
		if (talents.empty())break;
		DrawStringEx(bufPoses[2].x, bufPoses[2].y + 40 + (i * 40), -1, talents[i]->GetName().c_str());

		std::string rankText = "��" + std::to_string(talents[i]->GetRank());
		DrawStringEx(bufPoses[2].x + 110, bufPoses[2].y + 40 + (i * 40), -1, rankText.c_str());
	}
	SetFontSize(18);
}

void Scene_Map::DrawInventorySequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//�e���ڂ�UI�̍�����擾
		//menu���ڂ̃|�W�V����
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//�A�C�e���̘g�̃|�W�V����
		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x, leftTopPos2.y + 10, 0));

		//�������̘g�̃|�W�V����
		auto& leftTopPos3 = inventoryGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 20, 0));
	}

	DrawFirstMenu();

	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "�����A�C�e���ꗗ");
	SetFontSize(20);

	InventoryManager::GetInstance()->DrawInventory(bufPoses[1].x, bufPoses[1].y + 25);

	InventoryManager::GetInstance()->DrawCursorItemDesc(bufPoses[2].x, bufPoses[2].y);
	SetFontSize(16);
}

void Scene_Map::DrawUseInventoryItemSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//�e���ڂ�UI�̍�����擾
		//menu���ڂ̃|�W�V����
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//�A�C�e���̘g�̃|�W�V����
		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x, leftTopPos2.y + 10, 0));

		//�������̘g�̃|�W�V����
		auto& leftTopPos3 = inventoryGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 20, 0));

		//�g�p�m�F�̘g�̃|�W�V����
		auto& leftTopPos4 = inventoryGraphics[3]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos4.x + 10, leftTopPos4.y + 10, 0));
	}
	DrawFirstMenu();
	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "�����A�C�e���ꗗ");
	SetFontSize(20);
	InventoryManager::GetInstance()->DrawInventory(bufPoses[1].x, bufPoses[1].y + 25);

	InventoryManager::GetInstance()->DrawCursorItemDesc(bufPoses[2].x, bufPoses[2].y);

	//�A�C�e�����g�����m�F���b�Z�[�W���o��
	DrawStringEx(bufPoses[3].x, bufPoses[3].y, -1, "�A�C�e�����g���܂����H");
	SetFontSize(16);

	DrawStringEx(bufPoses[3].x + 20, bufPoses[3].y + 30, -1, "�͂�");
	DrawStringEx(bufPoses[3].x + 80, bufPoses[3].y + 30, -1, "������");

	DrawRotaGraphF(bufPoses[3].x + (subCursorNum * 70), bufPoses[3].y + 40, 0.5, 0, cursorGh, true);

}

void Scene_Map::DrawEquipSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//�e���ڂ�UI�̍�����擾
		//menu���ڂ̃|�W�V����
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 20, leftTopPos1.y + 20, 0));

		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x + 20, leftTopPos2.y + 20, 0));
	}

	DrawFirstMenu();

	DrawStringEx(bufPoses[1].x, bufPoses[1].y, -1, "�������ł��I");

}

bool Scene_Map::ChangeSequence(SEQUENCE NextSeq)
{
	switch (NextSeq)
	{
	case SEQUENCE::WAIT:
		mainSequence.change(&Scene_Map::SeqWait);
		nowSequence = SEQUENCE::WAIT;
		return true;
		break;
	case SEQUENCE::FIRSTMENU:
		mainSequence.change(&Scene_Map::SeqFirstMenu);
		nowSequence = SEQUENCE::FIRSTMENU;
		return true;
		break;
	case SEQUENCE::STATUS:
		mainSequence.change(&Scene_Map::SeqStatus);
		nowSequence = SEQUENCE::STATUS;
		return true;
		break;
	case SEQUENCE::INVENTORY:
		mainSequence.change(&Scene_Map::SeqInventory);
		nowSequence = SEQUENCE::INVENTORY;
		return true;
	case SEQUENCE::USEITEM:
		mainSequence.change(&Scene_Map::SeqUseInventoryItem);
		nowSequence = SEQUENCE::USEITEM;
		return true;
	case SEQUENCE::EQUIP:
		mainSequence.change(&Scene_Map::SeqEquip);
		nowSequence = SEQUENCE::EQUIP;
		return true;
	default:
		return false;
		break;
	}

	return false;
}

void Scene_Map::LoadMenuTextCsv()
{
	auto csv = tnl::LoadCsv("csv/Menu/MenuElements.csv");

	for (int i = 1; i < csv.size(); ++i) {
		menuText.emplace_back(csv[i][1]);
	}

}

void Scene_Map::DrawFirstMenu()
{
	for (int i = 0; i < menuText.size(); ++i) {
		SetFontSize(22);
		DrawStringEx(bufPos.x, bufPos.y + (25 * i), -1, menuText[i].c_str());
		SetFontSize(16);
	}
	DrawRotaGraphF(bufPos.x - 10, bufPos.y + 10 + (cursorNum * 25), 0.5, 0, cursorGh, true);
}
