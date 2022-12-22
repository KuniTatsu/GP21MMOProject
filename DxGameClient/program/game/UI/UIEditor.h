#pragma once
//---------------使い方-------------
//・GameManagerなどの場所でUIEditorを生成してください。
// 
//・UIEditorは初期状態では動かないようになっています。
//	ChangeEnable()関数で有効にすると画面が表示されます。
// 
//・UIをCSVからのロードする際のパスは RELOADPASS を変更してください
//  デフォルトではslnファイルが有る階層から CSV/UI/ の中にcsvファイルを置きます
//・フォルダ内の画像を一括で読み込んでリソースに入れるパスは LOADFILEPASS を変更して下さい 
//  デフォルトでは graphics\\UI\\*.png ->slnファイルがある階層からgraphics/UI/の中にある".png"画像のみ対象にしています。
// 
//・ReLoad ～ボタンをクリックするとLoadボタンを押した時に読み込むcsvファイルを変更できます。
//・ChangeボタンをクリックするとUI作成時の拡大方法を変更できます

//・このEditorを使うには以下のクラスと関数、変数が必要になります。
//・GameManager->isClickedRect()	:短形とマウスのクリック感知関数
//・GameManager->LoadGraphEx()		:std::unorderedmapを利用した画像読み込み関数
//・GameManager->deltatime			:フレーム秒 game_mainより取得
//・GraphicUIクラス					:実際に画面内に描画するUIのクラス 完成品
//・UIDataクラス					:GraphicUIクラスを作るためのデータクラス 特に知らなくても良い
//・Graphicクラス					:Editor内で使用するデータクラス リソース画像の描画にも使用
//・dxlib_ext/dxlib_ext.h			:先生が作成したライブラリを使用するためのヘッダー
//・その他C++のスタンダードライブラリ:string,vector,memory
//・エディタ本体のための画像フォルダが必要となります。
//・graphics/UIEditor の中にある画像の名前は変更しないでください

//エディター内の関数及び変数、定数は上記 RELOADPASS,LOADFILEPASSを除き変更しないでください。動作を保証できません。
//なにか不明点や拡張してほしい要素があれば気軽にGP21 國武まで相談ください。常木先生経由の方がアポを取りやすいかもしれません。


#include<string>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class GraphicUI;
class Graphic;

/*
組み込み型のUIエディターを作る

必要要件

csvから読み込んでUIの生成,描画が出来ること

実行中にビジュアル的にUIの調整が可能で、テキストへの出力が行えること

自由拡大か、等比率拡大か、等倍を選べること

*/

class UIEditor
{
public:
	UIEditor();
	~UIEditor();

	//初期化関数
	void Init();
	//毎フレーム実行する更新関数
	void Update();
	//毎フレーム描画する関数
	void Draw();

	//UIEditorの有効無効状態を切り替える関数
	void ChangeEnable();

private:
	//gamemanager
	GameManager* gManager = nullptr;

	//UIEditorを表示、起動しているかどうか
	bool isEnable = false;

	//マウス座標
	int mouseX = 0;
	int mouseY = 0;

	//作成、読み込んだUIの配列
	std::vector<std::shared_ptr<GraphicUI>> makedUI;

	//リソース画像の配列
	std::vector<std::shared_ptr<Graphic>>resources;

	//selectシークエンスで選択した画像リソースポインタ
	std::shared_ptr<Graphic>nowSelectGraphic = nullptr;

	//editシークエンスで使用するための画像リソースポインタ
	std::shared_ptr<GraphicUI>edit = nullptr;

	//editシークエンスで使用する画像の左上の基準座標
	tnl::Vector3 leftTop = {};

	//リソース選択関数
	bool CheckSelectResource();

	//ロード時の拡大ありなし
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//--------------UIの拡大処理関係--------------------//

	//画像の拡大モード
	enum class EDITMODE :uint32_t {
		NOEDIT,		//拡大なし
		SAMERATIO,	//等比率拡大
		FREERATIO,	//自由拡大
		MAX
	};
	//関数使用のための配列
	const EDITMODE MODE[static_cast<uint32_t>(EDITMODE::MAX)] = { EDITMODE::NOEDIT,EDITMODE::SAMERATIO,EDITMODE::FREERATIO };
	const std::string MODESTRING[static_cast<uint32_t>(EDITMODE::MAX)] = { "NOEDIT","SAME","FREE" };

	//modeごとの使用画像配列
	const std::string MODEGRAPHICPASS[static_cast<uint32_t>(EDITMODE::MAX)] = { "graphics/UIEditor/ModeNoEdit.png","graphics/UIEditor/ModeSameRatio.png","graphics/UIEditor/ModeFreeRatio.png" };

	//現在のモード　フォルトは拡大なし
	int nowMode = static_cast<uint32_t>(EDITMODE::NOEDIT);

	//拡大モードを変更する関数
	inline void ChangeEditMode() {
		//クリックするごとに0->1->2->0->...の順で循環する　
		nowMode = (nowMode + 1) % static_cast<uint32_t>(EDITMODE::MAX);
	}

	//editシークエンス用 自由拡大関数 毎フレーム呼ぶ
	void EditFreeScale();
	//editシークエンス用 当比率拡大関数 毎フレーム呼ぶ
	void EditSameScale();

	//--------------------------------------------------//

	//----------エディター本体のシステムUI----------//

	//左端に置くUI見本の背景フレーム
	//GraphicUI* resourcesFrame = nullptr;
	std::shared_ptr<GraphicUI> resourcesFrame = nullptr;

	//現在のUIをcsvとして出力するボタン
	std::shared_ptr<GraphicUI> saveButton = nullptr;
	//現在の画面のUIを全てリセットするボタン
	std::shared_ptr<GraphicUI> resetButton = nullptr;
	//特定の名前のcsvからUIをロードし表示するボタン
	std::shared_ptr<GraphicUI> loadButton = nullptr;
	//特定のフォルダからリソースをロードするボタン
	std::shared_ptr<GraphicUI> resourceButton = nullptr;

	//拡大モードの変更ボタン
	std::shared_ptr<GraphicUI> modeChangeButton = nullptr;

	//リロードするCSVを変更するボタン
	std::shared_ptr<GraphicUI>reloadChangeButton = nullptr;



	//システムUIのボタン配列
	std::vector<std::shared_ptr<GraphicUI>>SystemButtons;
	//システムUI
	enum class SYSTEMUI :uint32_t {
		SAVE,
		RESET,
		LOAD,
		CHANGELOAD,
		CHANGE,
		RESOURCE,
		MAX
	};

	//システムUIとのクリック判定関数
	void CheckButtonClick();

	//saveボタン
	void SaveUIButton();
	//resetボタン
	void ResetUIButton();
	//loadボタン
	void LoadUIButton();
	//load先変更ボタン
	void ChangeLoadCSV();

	//changeボタン
	void ModeChangeButton();
	//resourceボタン
	void ResourceButton();

	//ボタンを押したときの処理を入れておく関数の配列
	const std::function< void(UIEditor*) > BUTTONPROCESS[static_cast<uint32_t>(SYSTEMUI::MAX)] = { &UIEditor::SaveUIButton,&UIEditor::ResetUIButton,
																									&UIEditor::LoadUIButton,& UIEditor::ChangeLoadCSV,
																									&UIEditor::ModeChangeButton,&UIEditor::ResourceButton };

	//---------アウトプット用-------------//
	//出力用整形済み文字列配列
	std::vector<std::string> UIText;

	//出力用の文字列型にデータを整形する関数
	void UiToString();
	//出力関数 カンマ区切りのデータで出力
	void UiOutput();
	//--------------------------------------//


	//----------UIEditorのリソース関係の関数----------//

	//リロード対象
	enum class UIFILE :uint32_t {
		DEFAULT,
		SAVED,
		DEBUG,
		MAX
	};

	//modeごとの使用画像配列
	const std::string LOADGRAPHICPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "graphics/UIEditor/ReloadDefault.png","graphics/UIEditor/ReloadSaved.png","graphics/UIEditor/ReloadDebug.png" };

	//****************-------------------------ここだけはいじっても良い--------------------------------------------------************//
	//UIロード対象のパス
	const std::string RELOADPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "Csv/UI/SaveUI.csv","Csv/UI/MakedSaveUI.csv","Csv/UI/TestSaveUI.csv" };

	//指定フォルダの相対パス(slnファイルが有る場所からのパス)
	const std::string LOADFILEPASS = "graphics\\UI\\*.png";

	//****************---------------------------------------------------------------------------------------------------************//

	//現在のリロードパス
	int nowReloadPass = static_cast<uint32_t>(UIFILE::DEFAULT);

	//リロードパスを変更する関数
	void ChangeReLoadPass();

	//リソース画像の読み込み(パス経由 コードでの暫定的なデバッグに使用)
	void LoadResourceGraphic(std::string Pass, int Width, int Height);

	//debugのためpublicに移動

	//リソース画像の再読み込み(実行画面中のボタンに仕込む 普段はこちらでリロードする)
	//指定したフォルダの中の全ての画像を読み込む
	void LoadFileResource();


	//CsvからのUIロード関数
	void LoadUI(std::string Pass);

	//リソースエリアに描画する画像の正方サイズ
	const int DRAWSIZE = 100;

	//リソースエリアの基準座標(一番上の画像の描画中心座標)
	const tnl::Vector3 FIRSTRESOURCECENTERPOS = { 70, 70, 0 };

	//初回リソース画像読み込み(基本UIの枠のみ必ず読み込む)
	void LoadDefaultResource();

	//リソース画像の描画
	void DrawResource();

	//----------------------------------------------//

	//----------シークエンス処理---------------------//
	//初期シークエンスを設定
	tnl::Sequence<UIEditor> mainSequence =
		tnl::Sequence<UIEditor>(this, &UIEditor::SeqSelect);

	//各シークエンスのUpdate関数
	bool SeqSelect(const float DeltaTime);
	bool SeqPlace(const float DeltaTime);
	bool SeqEdit(const float DeltaTime);

	//シークエンス一覧
	enum class SEQUENCE :uint32_t {
		SELECT,
		PLACE,
		EDIT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::SELECT;

	//シークエンス変更関数
	bool ChangeSequence(SEQUENCE NextSeq);

	//シークエンスごとの描画関数
	void DrawSelectSequence();
	void DrawPlaceSequence();
	void DrawEditSequence();

	//現在のシークエンスの描画関数
	const std::function< void(UIEditor*) > DRAWSEQUENCE[3] = { &UIEditor::DrawSelectSequence,&UIEditor::DrawPlaceSequence,&UIEditor::DrawEditSequence };

	//-----------------------------------------------------------//
};

