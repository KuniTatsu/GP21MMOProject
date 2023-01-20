#pragma once
/*
ゲーム内のUI表示、保持を行うクラス
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
	void ChangeDrawUI(int UINum);

	//UIの描画可否切り替え
	inline void ChangeCanDrawUI() {
		if (!canDrawUI) {
			canDrawUI = true;
			return;
		}
		canDrawUI = false;
	}

	//描画可否取得
	inline bool GetCanDraw() {
		return canDrawUI;
	}

private:
	static UIManager* instance;

	enum class UI :uint32_t {
		TOP,
		STATUS,
		INVENTORY,
		EQUIP,
		MAX
	};

	int nowDrawUI = static_cast<int>(UI::TOP);

	//ロード時の拡大ありなし
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};
	//読み込んだUIの配列
	std::vector<std::vector<std::shared_ptr<GraphicUI>>> makedUI;
	//UIロード対象のパス
	const std::string RELOADPASS[static_cast<uint32_t>(UI::MAX)] = { "Csv/UI/UseUI/TopUI.csv","Csv/UI/UseUI/StatusUI.csv","Csv/UI/UseUI/InventoryUI.csv"
																	,"Csv/UI/UseUI/EquipUI.csv" };

	//UIを描画するかどうか
	bool canDrawUI = false;
private:

	UIManager();
	~UIManager();

	//CsvからのUIロード関数
	void LoadUI(std::string Pass, int UIType);



};

