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

	//初期シークエンスを設定
	tnl::Sequence<Scene_Map> mainSequence =
		tnl::Sequence<Scene_Map>(this, &Scene_Map::SeqWait);

	//シークエンス一覧
	enum class SEQUENCE :uint32_t {
		WAIT,
		FIRSTMENU,
		STATUS,
		INVENTORY,
		USEITEM,
		EQUIP,
		MAX
	};

	//ツールチップの描画
	void DrawToolTip();

	//各シークエンスのUpdate関数
	bool SeqWait(const float DeltaTime);
	bool SeqFirstMenu(const float DeltaTime);
	bool SeqStatus(const float DeltaTime);
	bool SeqInventory(const float DeltaTime);
	bool SeqUseInventoryItem(const float Deltatime);

	bool SeqEquip(const float DeltaTime);

	//シークエンスごとの描画関数
	void DrawWaitSequence();
	void DrawFirstMenuSequence();
	void DrawStatusSequence();
	void DrawInventorySequence();
	void DrawUseInventoryItemSequence();

	void DrawEquipSequence();

	//現在のシークエンスの描画関数
	const std::function< void(Scene_Map*) > DRAWSEQUENCE[static_cast<int>(SEQUENCE::MAX)] =
				{&Scene_Map::DrawWaitSequence, &Scene_Map::DrawFirstMenuSequence,&Scene_Map::DrawStatusSequence,
				&Scene_Map::DrawInventorySequence,&Scene_Map::DrawUseInventoryItemSequence,&Scene_Map::DrawEquipSequence };

	

	SEQUENCE nowSequence = SEQUENCE::WAIT;

	//シークエンス変更関数
	bool ChangeSequence(SEQUENCE NextSeq);

	//Menuの項目
	enum class MENUINDEX :uint32_t {
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};

	int cursorGh = 0;

	//ツールチップの通常攻撃アイコン
	int defaultAttackIcon = 0;

	int noneIcon = 0;

	int coolDawnFade = 0;

	int escKey = 0;

	std::vector<std::shared_ptr<GraphicUI>>wait;


	//menuテキストの配列
	std::vector<std::string>menuText;

	//menuテキストのロード
	void LoadMenuTextCsv();

	//menuテキストの描画
	void DrawFirstMenu();

	//menuのグラフィック
	std::vector<std::shared_ptr<GraphicUI>>firstMenuGraphics;

	//メインメニューのカーソルに使う番号
	int cursorNum = 0;

	//アイテム使用の部分のカーソルに使う番号
	int subCursorNum = 0;

	//描画のための一時保存座標
	tnl::Vector3 bufPos = {};

	//複数必要なとき用の一時保存座標	
	std::vector<tnl::Vector3> bufPoses;

	//------------------------------
	//ステータスシークエンス用描画データの一時保存先
	std::shared_ptr<ActorData>data=nullptr;
	std::string name="";
	std::vector<int>ghs = {};
	std::vector<std::shared_ptr<Talent>>talents = {};
	std::vector<std::shared_ptr<Job>>jobs = {};
	std::string highestLevelJob = "";
	std::string jobLevelText = "";
	std::vector<float>mainStatus = {};
	std::vector<std::string>names = {};

	//reset関数
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