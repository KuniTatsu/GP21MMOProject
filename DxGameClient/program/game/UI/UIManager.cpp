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
	//UIの種類ごとに描画判定
	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		auto& vector = GetUIVector(i);
		if (vector[NOWDRAWUIs[i]].empty())continue;

		for (auto ui : vector[NOWDRAWUIs[i]])
		{
			ui->Draw();
		}
	}

	/*if (makedMenuUI[nowDrawMenuUI].empty())return;

	for (auto ui : makedMenuUI[nowDrawMenuUI])
	{
		ui->Draw();
	}*/

	//DRAWSEQUENCE[nowDrawUI](this);
}

void UIManager::ChangeDrawUI(int MenuSeries, int UINum)
{
	//選んだメニューシリーズの最大数より多ければ変更しない
	if (UINum >= static_cast<int>(SERIESINNUM[MenuSeries]))return;

	if (NOWDRAWUIs[MenuSeries] == UINum)return;

	nowDrawMenuUI = UINum;
	NOWDRAWUIs[MenuSeries] = UINum;
}
//外部からのUI配列の取得用
const std::vector<std::vector<std::shared_ptr<GraphicUI>>>& UIManager::GetUI(int series)
{
	if (series >= static_cast<int>(UISERIES::MAX))return errorVec;

	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return makedMenuUI;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return makedSupNPCUI;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return makedDisassemblyNPCUI;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return makedGuardNPCUI;
		break;

	default:
		break;
	}

	return errorVec;
}

UIManager::UIManager()
{
	makedMenuUI.resize(static_cast<int>(MENUUI::MAX));
	makedSupNPCUI.resize(static_cast<int>(SUPNPCUI::MAX));
	makedDisassemblyNPCUI.resize(static_cast<int>(DISASSEMBLYNPCUI::MAX));
	makedGuardNPCUI.resize(static_cast<int>(GUARDNPCUI::MAX));

	//csvロード
	//UIの種類ごとにロード Menu,Sup,Disassembly,guard
	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		//結果を入れるベクターの参照を取得
		auto& vector = GetUIVector(i);
		//パスの取得
		auto pass = GetLoadPass(i);

		//種類の持つUIの個数で読み込む
		for (int k = 0; k < SERIESINNUM[i]; ++k) {
			LoadUI(pass[k], vector, k);
		}
	}
}

UIManager::~UIManager()
{
	makedMenuUI.clear();

	for (int i = 0; i < static_cast<int>(UISERIES::MAX); ++i) {

		//結果を入れるベクターの参照を取得
		auto& vector = GetUIVector(i);
		vector.clear();
	}
}

void UIManager::LoadUI(std::string Pass, std::vector<std::vector<std::shared_ptr<GraphicUI>>>& putInVector, int UIType)
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
			putInVector[UIType].emplace_back(newUI);
			//次のループへ
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUIクラスを生成(枠の中に画像がない場合)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			newUI->ChangeLiveUI();
			//vectorに登録
			putInVector[UIType].emplace_back(newUI);
		}
		else {
			//GraphicUIクラスを生成(枠の中に画像がある場合
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);
			newUI->ChangeLiveUI();
			//vectorに登録
			putInVector[UIType].emplace_back(newUI);
		}
	}
}
//ロード時の参照用
std::vector<std::vector<std::shared_ptr<GraphicUI>>>& UIManager::GetUIVector(int series)
{
	if (series >= static_cast<int>(UISERIES::MAX))return errorVec;

	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return makedMenuUI;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return makedSupNPCUI;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return makedDisassemblyNPCUI;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return makedGuardNPCUI;
		break;

	default:
		break;
	}

	return errorVec;
}

const std::string* UIManager::GetLoadPass(int series)
{
	switch (series)
	{
	case static_cast<int>(UISERIES::MENU):
		return MENUPASS;
		break;
	case static_cast<int>(UISERIES::SUPNPC):
		return SUPNPCUIPASS;
		break;
	case static_cast<int>(UISERIES::DISASSEMBLYNPC):
		return DISNOCUIPASS;
		break;
	case static_cast<int>(UISERIES::GUARDNPC):
		return GUARDNPCUIPASS;
		break;

	default:
		break;
	}
	return err;

}


