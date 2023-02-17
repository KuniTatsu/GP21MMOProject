#pragma once
//死骸アイテムから素材アイテムを生成する機能クラス

#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<unordered_map>

class MaterialConverter;

class Disassembly
{
public:

	// インスタンスの取得
	static Disassembly* GetInstance();

	//死骸Idを受け取り、引数のインベントリに素材アイテムを追加する関数 --アイテムに死骸IDというデータがあることを前提
	void DisassemblyDeadBody(int deadId);


private:
	Disassembly();
	~Disassembly();



private:
	static Disassembly* instance;

	//死骸IDと情報を合わせたオブジェクトの入れ物
	std::vector<std::shared_ptr<MaterialConverter>> convertMaster;

};


