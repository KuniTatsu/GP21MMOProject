#include "UIManager.h"
#include"../UI/GraphicUI.h"

UIManager* UIManager::instance = nullptr;
UIManager* UIManager::GetInstance()
{
	if (!instance) {
		instance = new UIManager();
	}
	return instance;
}

void UIManager::Destroy()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void UIManager::Update()
{
}

void UIManager::Draw()
{
	if (!canDrawUI)return;
	if (makedUI[nowDrawUI].empty())return;

	for (auto ui : makedUI[nowDrawUI])
	{
		ui->Draw();
	}

	//DRAWSEQUENCE[nowDrawUI](this);
}

void UIManager::ChangeDrawUI(int UINum)
{
	if (UINum >= static_cast<int>(UI::MAX))return;
	if (nowDrawUI == UINum)return;
	nowDrawUI = UINum;
}

UIManager::UIManager()
{
	makedUI.resize(static_cast<int>(UI::MAX));

	//csvロード
	for (int i = 0; i < static_cast<int>(UI::MAX); ++i) {
		LoadUI(RELOADPASS[i], i);
	}
}

UIManager::~UIManager()
{
	makedUI.clear();
}

void UIManager::LoadUI(std::string Pass, int UIType)
{
	//CSV読み込み
	auto loadUICsv = tnl::LoadCsv(Pass);

	//1行目からスタート(0行目は項目名)
	for (int i = 1; i < loadUICsv.size(); ++i) {
		//------string型のデータをint型とfloat型に変換し、ローカル変数に保管する処理----//

		//type 0:分割ロード,1:そのままロード
		int type = stoi(loadUICsv[i][2]);

		int allNum = stoi(loadUICsv[i][3]);
		int widthNum = stoi(loadUICsv[i][4]);
		int heightNum = stoi(loadUICsv[i][5]);
		int widthSize = stoi(loadUICsv[i][6]);
		int heightSize = stoi(loadUICsv[i][7]);

		float posX = stof(loadUICsv[i][8]);
		float posY = stof(loadUICsv[i][9]);

		int frameWidth = stoi(loadUICsv[i][10]);
		int frameHeight = stoi(loadUICsv[i][11]);

		//------------------------------------------------------------------------------//

		//UIDataクラスを生成
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		//画像を引き伸ばさずに使うUIの場合 ->使うコンストラクタを統一した
		if (type == static_cast<uint32_t>(LOADMODE::NORMAL)) {

			//GraphicUIクラスを生成(画像を拡大せずに使う場合)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vectorに登録
			makedUI[UIType].emplace_back(newUI);
			//次のループへ
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUIクラスを生成(枠の中に画像がない場合)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vectorに登録
			makedUI[UIType].emplace_back(newUI);
		}
		else {
			//GraphicUIクラスを生成(枠の中に画像がある場合
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);
			newUI->ChangeLiveUI();
			//vectorに登録
			makedUI[UIType].emplace_back(newUI);
		}
	}
}


