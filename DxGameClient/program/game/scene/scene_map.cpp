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
#include"../Actor/NPC/DisassemblyNPC.h"
#include"../Actor/NPC/NPC.h"
#include"../Actor/NPC/NPCManager.h"
#include"../InventoryManager.h"
#include"../EffectManager.h"
#include"../Actor/ActorDrawManager.h"
#include"../DebugDef.h"
#include"../Job.h"
#include"../Talent.h"
#include"../ChatBase.h"
#include"../JobManager.h"
#include"../Disassembly.h"

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
#ifndef DEBUG_ON //通信しない時


	player = GameManager::GetInstance()->CreatePlayer(0);

#endif

#ifdef DEBUG_ON


	gManager->CreatePlayer(0);
	player = gManager->GetPlayer();
#endif 


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
	//NPCの生成
	auto okNpc=NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::SUPPORT), 180, 240, 5);
	auto npc = NPCManager::GetInstance()->CreateNPC(static_cast<int>(NPCManager::NPCTYPE::DISASSEMBLY), 10, 10, 3);


	//UI系のinit
	menuText.clear();
	LoadMenuTextCsv();

	cursorGh = GameManager::GetInstance()->LoadGraphEx("graphics/menuCursor.png");
	defaultAttackIcon = GameManager::GetInstance()->LoadGraphEx("graphics/skillIcon/defaultAttack.png");
	noneIcon = GameManager::GetInstance()->LoadGraphEx("graphics/skillIcon/none.png");
	coolDawnFade = GameManager::GetInstance()->LoadGraphEx("graphics/skillIcon/coolDownFade.png");
	escKey = GameManager::GetInstance()->LoadGraphEx("graphics/Key/button_Escape.png");

	firstMenuGraphics = UIManager::GetInstance()->GetNowDrawGraphic(static_cast<int>(UIManager::UISERIES::MENU));
	//MenuUIの左上を取得
	auto& leftTopPos = firstMenuGraphics[0]->GetLeftTopPos();
	bufPos = tnl::Vector3(leftTopPos.x + 20, leftTopPos.y + 20, 0);

	wait = UIManager::GetInstance()->GetWaitUI();

	//チャット接続
	gManager->CreateChat();
}

void Scene_Map::update(float delta_time)
{
	mainSequence.update(gManager->deltaTime);

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

	//debug
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_I)) {
		//薬草を一つ追加
		InventoryManager::GetInstance()->AddItemToInventory(1);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_O)) {
		InventoryManager::GetInstance()->AddItemToInventory(80000);
	}


	//debug
	//ctrl+Jでデバッグ用職業リスト1を生成し付与する
	if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL)) {

		if (!player->GetmyJobs().empty())return;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
			auto job1 = JobManager::GetInstance()->CreateDebugJob(843, 4);
			auto job2 = JobManager::GetInstance()->CreateDebugJob(830, 6);
			auto job3 = JobManager::GetInstance()->CreateDebugJob(822, 10);
			auto job4 = JobManager::GetInstance()->CreateDebugJob(800, 10);
			auto job5 = JobManager::GetInstance()->CreateDebugJob(823, 9);
			auto job6 = JobManager::GetInstance()->CreateDebugJob(825, 9);

			player->SetPlayerJob(job1);
			player->SetPlayerJob(job2);
			player->SetPlayerJob(job3);
			player->SetPlayerJob(job4);
			player->SetPlayerJob(job5);
			player->SetPlayerJob(job6);
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
			auto job1 = JobManager::GetInstance()->CreateDebugJob(827, 8);
			auto job2 = JobManager::GetInstance()->CreateDebugJob(831, 6);
			auto job3 = JobManager::GetInstance()->CreateDebugJob(818, 10);
			auto job4 = JobManager::GetInstance()->CreateDebugJob(810, 10);
			auto job5 = JobManager::GetInstance()->CreateDebugJob(816, 9);
			auto job6 = JobManager::GetInstance()->CreateDebugJob(819, 3);

			player->SetPlayerJob(job1);
			player->SetPlayerJob(job2);
			player->SetPlayerJob(job3);
			player->SetPlayerJob(job4);
			player->SetPlayerJob(job5);
			player->SetPlayerJob(job6);

		}
		//死骸アイテムを解体
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
			Disassembly::GetInstance()->DisassemblyDeadBody(2001);
		}


	}
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

	auto chat = gManager->GetChat();
	if (chat) {
		chat->Update();
		chat->Draw();
	}

	//各種UI描画
	UIManager::GetInstance()->Draw();

	DrawToolTip();

	NPCManager::GetInstance()->DrawSpeak();

	//シークエンスごとの描画(UI)
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);

	EnemyManager::GetInstance()->Draw(&camera);

	//debug
	SetFontSize(30);
	//DrawStringEx(500, 500, -1, "%d", cursorNum);
	SetFontSize(16);
}

void Scene_Map::DrawToolTip()
{
	std::vector<tnl::Vector3> toolTipPos;

	//toolTipの描画
	auto& toolTipUI = UIManager::GetInstance()->GetToolTipUI();

	auto& leftTopPos1 = toolTipUI[1]->GetLeftTopPos();
	toolTipPos.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 50, 0));

	auto& leftTopPos2 = toolTipUI[2]->GetLeftTopPos();
	toolTipPos.emplace_back(tnl::Vector3(leftTopPos2.x + 50, leftTopPos2.y + 50, 0));

	auto& leftTopPos3 = toolTipUI[3]->GetLeftTopPos();
	toolTipPos.emplace_back(tnl::Vector3(leftTopPos3.x + 50, leftTopPos3.y + 50, 0));

	auto& leftTopPos4 = toolTipUI[4]->GetLeftTopPos();
	toolTipPos.emplace_back(tnl::Vector3(leftTopPos4.x + 50, leftTopPos4.y + 50, 0));


	//各種スキルアイコンを並べる
	//本来は職業のスキルを自分で選んでセットする
	//今後実装予定
	DrawRotaGraphF(toolTipPos[0].x, toolTipPos[0].y, 1, 0, defaultAttackIcon, true);

	//クールダウン中なら黒でフェードさせる
	float coolDawn = GameManager::GetInstance()->GetPlayer()->GetCoolDown();

	if (coolDawn > 0) {
		float max = GameManager::GetInstance()->GetPlayer()->GetMaxCoolDawn();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
		DrawExtendGraphF(toolTipPos[0].x - 50, toolTipPos[0].y - 50, (toolTipPos[0].x + 50), (toolTipPos[0].y - 50) + (100 * coolDawn / max), coolDawnFade, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	DrawRotaGraphF(toolTipPos[1].x, toolTipPos[1].y, 1, 0, noneIcon, true);
	DrawRotaGraphF(toolTipPos[2].x, toolTipPos[2].y, 1, 0, noneIcon, true);
	DrawRotaGraphF(toolTipPos[3].x, toolTipPos[3].y, 1, 0, noneIcon, true);


}

bool Scene_Map::SeqWait(const float DeltaTime)
{
	auto uiManager = UIManager::GetInstance();

	//Escキーを押したらMenuを開く
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		//menuを開けない状態なら無視する
		if (!player->GetCanOpenMenu())return false;

		//これから開くメニュー以外のメニューを開けなくする
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
		//他のメニューを開けるようにする
		player->SetCanOpenMenu(true);

		cursorNum = 0;
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
		return true;
	}

	return true;
}

bool Scene_Map::SeqInventory(const float DeltaTime)
{
	if (mainSequence.isStart()) {
		//描画するUIをInventoryに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
	}
	//インベントリの更新関数 カーソルの移動,インベントリの切り替え
	InventoryManager::GetInstance()->UpdateInventory();

	//Enterを押したら使用確認へ移る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		//インベントリが空なら無視する
		if (InventoryManager::GetInstance()->isEmptyAllInventory())return true;

		ChangeSequence(SEQUENCE::USEITEM);
		//描画するUIをUseItemに変更
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::USEITEM));
		bufPoses.clear();
		return true;
	}

	//トップに戻る
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

	//はい と やめる　を選ぶ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		subCursorNum = (subCursorNum + 1) % 2;
	}

	//Enterをおしたら
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//はいを選んでいたらアイテムを使う
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

	//インベントリに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		UIManager::GetInstance()->ChangeDrawUI(static_cast<int>(UIManager::UISERIES::MENU), static_cast<int>(UIManager::MENUUI::INVENTORY));
		bufPoses.clear();
		ChangeSequence(SEQUENCE::INVENTORY);
	}

	return true;
}

bool Scene_Map::SeqEquip(const float DeltaTime)
{
	//トップに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		bufDataReset();
		ChangeSequence(SEQUENCE::FIRSTMENU);
	}
	return false;
}

void Scene_Map::DrawWaitSequence()
{
	wait[0]->Draw();
	DrawRotaGraphF(50, 50, 1, 0, escKey, true);
	DrawStringEx(82, 40, -1, "でメニューを開く");
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

	DrawFirstMenu();

	//プレイヤー画像の外枠
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

		std::string jobLevelText = "Level:" + std::to_string(jobs[i]->GetNowLevel());
		//職レベル描画
		DrawStringEx(bufPoses[3].x + 90, bufPoses[3].y + 40 + (i * 40), -1, jobLevelText.c_str());
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

		//説明文の枠のポジション
		auto& leftTopPos3 = inventoryGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 20, 0));
	}

	DrawFirstMenu();

	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "所持アイテム一覧");
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

		//各項目のUIの左上を取得
		//menu項目のポジション
		auto& leftTopPos1 = inventoryGraphics[0]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos1.x + 50, leftTopPos1.y + 20, 0));

		//アイテムの枠のポジション
		auto& leftTopPos2 = inventoryGraphics[1]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos2.x, leftTopPos2.y + 10, 0));

		//説明文の枠のポジション
		auto& leftTopPos3 = inventoryGraphics[2]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos3.x + 10, leftTopPos3.y + 20, 0));

		//使用確認の枠のポジション
		auto& leftTopPos4 = inventoryGraphics[3]->GetLeftTopPos();
		bufPoses.emplace_back(tnl::Vector3(leftTopPos4.x + 10, leftTopPos4.y + 10, 0));
	}
	DrawFirstMenu();
	SetFontSize(25);
	DrawStringEx(bufPoses[1].x + 30, bufPoses[1].y, -1, "所持アイテム一覧");
	SetFontSize(20);
	InventoryManager::GetInstance()->DrawInventory(bufPoses[1].x, bufPoses[1].y + 25);

	InventoryManager::GetInstance()->DrawCursorItemDesc(bufPoses[2].x, bufPoses[2].y);

	//アイテムを使うか確認メッセージを出す
	DrawStringEx(bufPoses[3].x, bufPoses[3].y, -1, "アイテムを使いますか？");
	SetFontSize(16);

	DrawStringEx(bufPoses[3].x + 20, bufPoses[3].y + 30, -1, "はい");
	DrawStringEx(bufPoses[3].x + 80, bufPoses[3].y + 30, -1, "いいえ");

	DrawRotaGraphF(bufPoses[3].x + (subCursorNum * 70), bufPoses[3].y + 40, 0.5, 0, cursorGh, true);

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

	DrawFirstMenu();

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

void Scene_Map::DrawFirstMenu()
{
	for (int i = 0; i < menuText.size(); ++i) {
		SetFontSize(22);
		DrawStringEx(bufPos.x, bufPos.y + (25 * i), -1, menuText[i].c_str());
		SetFontSize(16);
	}
	DrawRotaGraphF(bufPos.x - 10, bufPos.y + 10 + (cursorNum * 25), 0.5, 0, cursorGh, true);
}
