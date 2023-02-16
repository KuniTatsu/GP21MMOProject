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

	//チャット接続
	gManager->CreateChat();
#endif

#ifdef DEBUG_ON

	gManager->CreatePlayer(0);
	player = gManager->GetPlayer();
#endif // DEBUG_ON



	//マップの生成
	gManager->CreateMap();
	//エネミーの生成
	eManager->GetInstance();

	//playerの初期マップを登録
	gManager->SetStayMap();


#ifndef DEBUG_ON


	player = gManager->GetPlayer();
	//Dummy生成完了
	player->SetIsCreatedDummy();

	//エネミー取得
	gManager->GetServerEnemyInfo();
#endif
	menuText.clear();
	LoadMenuTextCsv();
	//NPCの生成
	NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::SUPPORT), 180, 240, 5);
	cursorGh = GameManager::GetInstance()->LoadGraphEx("graphics/menuCursor.png");
}

void Scene_Map::update(float delta_time)
{
	/*Player操作*/
	player->Update();

	/*Enemy生成*/
	eManager->SpawnEnemy(player->GetPos());
	/*Enemy動作*/
	eManager->Update(delta_time);
	/*カメラ操作*/
	camera.pos += (player->GetPos() - camera.pos) * 0.1f;

	/*エネミーの描画*/
	if (eManager != nullptr) {
		eManager->Update(gManager->deltaTime);
	}

	auto npcManager = NPCManager::GetInstance();
	npcManager->Update();

	auto& pos = player->GetPos();
	npcManager->CheckNearPlayer(pos.x, pos.y);


	EffectManager::GetInstance()->Update(gManager->deltaTime);

	mainSequence.update(gManager->deltaTime);

}
void Scene_Map::render()
{



	/*マップの描画*/
	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(false);
		map->Draw(&camera);
	}



	//Actorの描画
	ActorDrawManager::GetInstance()->DrawActorList(&camera);

	EffectManager::GetInstance()->Draw(&camera);

	for (auto map : gManager->GetMapList()) {
		map->SetIsDrawFront(true);
		map->Draw(&camera);
	}

	/*どこのシーンであるか*///debugMessage
	/*SetFontSize(50);
	DrawStringEx(50, 50, -1, "Scene_map");*/

#ifndef DEBUG_ON


#endif

	UIManager::GetInstance()->Draw();
	NPCManager::GetInstance()->DrawSpeak();

	//シークエンスごとの描画(UI)
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);

	EnemyManager::GetInstance()->Draw(&camera);

	//debug
	SetFontSize(30);
	DrawStringEx(500, 500, -1, "%d", cursorNum);
	SetFontSize(16);
}

bool Scene_Map::SeqWait(const float DeltaTime)
{
	auto uiManager = UIManager::GetInstance();

	//Escキーを押したらMenuを開く
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		//menuを開けない状態なら無視する
		if (!player->GetCanOpenMenu())return false;

		ChangeSequence(SEQUENCE::FIRSTMENU);
		return true;
	}

	return true;
}

bool Scene_Map::SeqFirstMenu(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		bufPoses.clear();
		cursorNum = 0;
		//MENUのUIを描画状態にする
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU), true);
		//描画するUIをTOPに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::TOP));
	}
	//上下にカーソル移動をさせ、項目を選ぶ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		cursorNum = (cursorNum + 1) % static_cast<int>(MENUINDEX::MAX);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		cursorNum = (cursorNum + static_cast<int>(MENUINDEX::MAX) - 1) % static_cast<int>(MENUINDEX::MAX);
	}

	//項目を決定
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//描画するUIを変更
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
	//Menuを閉じる
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeCanDrawUI(static_cast<int>(UIManager::UISERIES::MENU));
		ChangeSequence(SEQUENCE::WAIT);
	}
	return true;
}

bool Scene_Map::SeqStatus(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//描画するUIをStatusに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::STATUS));
	}




	//トップに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return true;
}

bool Scene_Map::SeqInventory(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//描画するUIをInventoryに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
		bufDataReset();
	}
	//トップに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}

	return true;
}

bool Scene_Map::SeqUseInventoryItem(const float Deltatime)
{
	if (mainSequence.isStart()) {
		//描画するUIをInventoryに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::USEITEM));
		bufDataReset();
	}
	//トップに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::INVENTORY);
	}

	return true;
}

bool Scene_Map::SeqEquip(const float DeltaTime)
{
	return false;
}

void Scene_Map::DrawWaitSequence()
{
}

void Scene_Map::DrawFirstMenuSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;
	if (mainSequence.isStart()) {
		firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//UIの左上を取得
		auto& leftTopPos = firstMenuGraphics[0]->GetLeftTopPos();
		bufPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y + 20, 0);
	}
	for (int i = 0; i < menuText.size(); ++i) {
		SetFontSize(22);
		DrawStringEx(bufPos.x, bufPos.y + (25 * i), -1, menuText[i].c_str());
		SetFontSize(16);
	}
	DrawRotaGraphF(bufPos.x - 10, bufPos.y + 10 + (cursorNum * 25), 0.5, 0, cursorGh, true);
}

void Scene_Map::DrawStatusSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>statusGraphics;
	if (mainSequence.isStart()) {
		statusGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//各項目のUIの左上を取得
		//menu項目のポジション
		auto& leftTopPos1 = statusGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//画像と名前などの枠のポジション
		auto& leftTopPos2 = statusGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x + 50, leftTopPos2.y + 40, 0));

		//才能の枠のポジション
		auto& leftTopPos3 = statusGraphics[3]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 10, 0));

		//職業の枠のポジション
		auto& leftTopPos4 = statusGraphics[4]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos4.x + 10, leftTopPos4.y + 10, 0));


		//プレイヤーの描画用ステータスを取得
		//正面画像,名前,合計職レベル,attribute,才能,職
		data = player->GetActorData();

		name = "名前:" + player->GetName();

		//画像取得　ghs[10]が正面静止画像
		ghs = player->GetGhs();

		//才能
		talents = player->GetMyTalents();
		//職
		jobs = player->GetmyJobs();

		//合計職レベル
		int sumJobLevel = 0;
		int bufMax = 0;
		for (int i = 0; i < jobs.size(); ++i) {
			sumJobLevel += jobs[i]->GetJobLevel();
			if (sumJobLevel < jobs[i]->GetJobLevel()) {
				highestLevelJob = jobs[i]->GetJobName();
			}
		}
		jobLevelText = "合計職レベル:" + std::to_string(sumJobLevel);
		highestLevelJob = "メイン職:" + highestLevelJob;

		//メインステータス
		mainStatus = data->GetMainStatus();
		names = data->GetStatusName();
	}

	DrawBox(bufPoses[1].x - 37, bufPoses[1].y - 37, bufPoses[1].x + 37, bufPoses[1].y + 37, -1, false);
	//プレイヤーの画像の描画
	DrawRotaGraph(bufPoses[1].x, bufPoses[1].y, 2, 0, ghs[10], true);
	SetFontSize(25);
	//名前の描画
	DrawStringEx(bufPoses[1].x + 100, bufPoses[1].y - 20, -1, name.c_str());
	//合計職レベルの描画
	DrawStringEx(bufPoses[1].x + 100, bufPoses[1].y + 5, -1, jobLevelText.c_str());
	//一番レベルが高い職を代表職として描画
	DrawStringEx(bufPoses[1].x - 32, bufPoses[1].y + 50, -1, highestLevelJob.c_str());

	//ステータスの描画
	SetFontSize(18);
	for (int i = 0; i < mainStatus.size(); ++i) {
		DrawStringEx(bufPoses[1].x - 32 + (i * 80), bufPoses[1].y + 100, -1, names[i].c_str());
	}
	SetFontSize(16);
	for (int i = 0; i < mainStatus.size(); ++i) {
		DrawStringEx(bufPoses[1].x - 16 + (i * 80), bufPoses[1].y + 130, -1, "%.f", mainStatus[i]);
	}
	SetFontSize(25);
	//職の描画 10個まで並べて描画する
	//10個を超えたらページを作る ToDO 職ができたらチェックすること

	DrawStringEx(bufPoses[3].x, bufPoses[3].y, -1, "職業一覧");

	for (int i = 0; i < jobs.size(); ++i) {
		if (jobs.empty())break;
		DrawStringEx(bufPoses[3].x, bufPoses[3].y + 40 + (i * 40), -1, jobs[i]->GetJobName().c_str());
	}
	//才能の描画
	DrawStringEx(bufPoses[2].x, bufPoses[2].y, -1, "才能一覧");
	for (int i = 0; i < talents.size(); ++i) {
		if (talents.empty())break;
		DrawStringEx(bufPoses[2].x, bufPoses[2].y + 40 + (i * 40), -1, talents[i]->GetName().c_str());

		std::string rankText = "★" + std::to_string(talents[i]->GetRank());
		DrawStringEx(bufPoses[2].x + 110, bufPoses[2].y + 40 + (i * 40), -1, rankText.c_str());
	}
	SetFontSize(18);
}

void Scene_Map::DrawInventorySequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//各項目のUIの左上を取得
		//menu項目のポジション
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//アイテムの枠のポジション
		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x, leftTopPos2.y + 10, 0));

	}
	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "所持アイテム一覧");
	SetFontSize(20);

	InventoryManager::GetInstance()->DrawInventory(bufPoses[1].x, bufPoses[1].y + 25);
	SetFontSize(16);
}

void Scene_Map::DrawUseInventoryItemSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//各項目のUIの左上を取得
		//menu項目のポジション
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//アイテムの枠のポジション
		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x, leftTopPos2.y + 10, 0));

	}
	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "所持アイテム一覧");
	SetFontSize(20);

	InventoryManager::GetInstance()->DrawInventory(bufPoses[1].x, bufPoses[1].y + 25);
	SetFontSize(16);
}

void Scene_Map::DrawEquipSequence()
{
	std::vector<std::shared_ptr<GraphicUI>>inventoryGraphics;
	if (mainSequence.isStart()) {
		inventoryGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));

		//各項目のUIの左上を取得
		//menu項目のポジション
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 20, leftTopPos1.y + 20, 0));

		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x + 20, leftTopPos2.y + 20, 0));
	}
	DrawStringEx(bufPoses[1].x, bufPoses[1].y, -1, "未実装です！");

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
