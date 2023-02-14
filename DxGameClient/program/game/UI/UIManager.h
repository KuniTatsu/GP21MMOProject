#pragma once
/*
ゲーム内のUI表示、保持を行うクラス

UIを増やすときは"UISERIES"と"NOWDRAWUIs","SERIESINNUM","canDrawUI"に追加した上で、入れ物とパスを用意すること
その後入れ者とパスの取得関数"GetUIVector"と"GetLoadPass"を更新すること
*/
#include<vector>
#include<memory>
#include<string>
#include<functional>
#include"../../dxlib_ext/dxlib_ext.h"

class GraphicUI;

class UIManager
{
public:
	// インスタンスの取得
	static UIManager* GetInstance();

	// 破棄
	void Destroy();

	//毎フレーム実行する更新関数
	void Update();
	//毎フレーム描画する関数
	void Draw();

	//描画するUIを変更する関数
	void ChangeDrawUI(int MenuSeries, int UINum);

	//UIの描画可否切り替え
	inline void ChangeCanDrawUI(int series, bool swich = false) {
		//今がfalse&trueにしろと来たらtrueに変える
		if (swich && !canDrawUI[series]) {
			canDrawUI[series] = true;
			return;
		}
		//今がtrueならでfalseにしろと来たらfalseにする
		else if (!swich && canDrawUI[series])canDrawUI[series] = false;
	}

	//描画可否取得
	inline bool GetCanDraw() {
		return canDrawUI;
	}

	//UIの入れ物を取得する関数
	const std::vector<std::vector<std::shared_ptr<GraphicUI>>>& GetUI(int series);

	//現在描画中のUIを取得する関数
	const std::vector<std::shared_ptr<GraphicUI>>& GetNowDrawGraphic(int series);

public:
	//どの機能のUIか
	enum class UISERIES :uint32_t {
		MENU,
		SUPNPC,
		DISASSEMBLYNPC,
		GUARDNPC,
		MAX
	};

	enum class MENUUI :uint32_t {
		TOP,
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};
	enum class SUPNPCUI :uint32_t {
		FIRSTMENU,
		HINT,
		MAX
	};

	enum class DISASSEMBLYNPCUI :uint32_t {
		FIRSTMENU,
		SELECTITEM,
		CHECK,
		RESULT,
		MAX
	};
	enum class GUARDNPCUI :uint32_t {
		FIRSTMENU,
		TALK,
		MAX
	};

private:
	static UIManager* instance;

	//現在表示中のUI番号の配列
	std::vector<int> NOWDRAWUIs = { nowDrawMenuUI,nowDrawSupNPCUI,nowDrawDisassemblyNpcUI,nowDrawGuardNpcUI };


	//機能ごとのUIの数の配列
	const std::vector<int>SERIESINNUM = { static_cast<int>(MENUUI::MAX),static_cast<int>(SUPNPCUI::MAX),
											static_cast<int>(DISASSEMBLYNPCUI::MAX),static_cast<int>(GUARDNPCUI::MAX) };



	//-----現在選択中のui番号-----
	int nowDrawMenuUI = static_cast<int>(MENUUI::TOP);
	int nowDrawSupNPCUI = static_cast<int>(SUPNPCUI::FIRSTMENU);
	int nowDrawDisassemblyNpcUI = static_cast<int>(DISASSEMBLYNPCUI::FIRSTMENU);
	int nowDrawGuardNpcUI = static_cast<int>(GUARDNPCUI::FIRSTMENU);

	//-----UIを保存する二次元配列-----
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedMenuUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedSupNPCUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedDisassemblyNPCUI;
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedGuardNPCUI;

	//ダミー
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> errorVec;

	//-----ロードするUIのパス配列-----
	//UI
	const std::string MENUPASS[static_cast<uint32_t>(MENUUI::MAX)] = { "Csv/UI/UseUI/TopUI.csv","Csv/UI/UseUI/StatusUI.csv","Csv/UI/UseUI/InventoryUI.csv","Csv/UI/UseUI/EquipUI.csv" };
	//Sup
	const std::string SUPNPCUIPASS[static_cast<uint32_t>(SUPNPCUI::MAX)] = { "Csv/UI/NPC/SuportNPCFirstMenu.csv","Csv/UI/NPC/SuportNPCHintMenu.csv" };
	//解体
	const std::string DISNOCUIPASS[static_cast<uint32_t>(DISASSEMBLYNPCUI::MAX)] = { "Csv/UI/NPC/DisAssemblyNPCFirstMenu.csv","Csv/UI/NPC/DisAssemblyNPCSelect.csv",
																					"Csv/UI/NPC/DisAssemblyNPCCheck.csv","Csv/UI/NPC/DisAssemblyNPCResult.csv", };
	//門番
	const std::string GUARDNPCUIPASS[static_cast<uint32_t>(GUARDNPCUI::MAX)] = { "Csv/UI/NPC/GuardNPCFirstMenu.csv","Csv/UI/NPC/GuardNPCTalk.csv" };

	//ロード時の拡大ありなし
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//UIを描画するかどうか 種類ごと
	bool canDrawUI[static_cast<int>(UISERIES::MAX)] = { false,false,false,false };

	const std::string err[2] = { "err","err" };

private:

	UIManager();
	~UIManager();

	//CsvからのUIロード関数
	void LoadUI(std::string Pass, std::vector<std::vector<std::shared_ptr<GraphicUI>>>& putInVector, int UIType);

	//UIの入れ物を取得する関数
	std::vector<std::vector<std::shared_ptr<GraphicUI>>>& GetUIVector(int series);

	//パスの配列を取得する関数
	const std::string* GetLoadPass(int series);

};

