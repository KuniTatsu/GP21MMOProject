#pragma once
//死骸アイテムから素材アイテムを生成する機能クラス

#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<unordered_map>

class Inventory;
class DisassemblyData;

class Disassembly
{
public:

	// インスタンスの取得
	static Disassembly* GetInstance();

	//死骸Idを受け取り、引数のインベントリに素材アイテムを追加する関数 --アイテムに死骸IDというデータがあることを前提
	void DisassemblyDeadBody(int deadId, std::shared_ptr<Inventory>inventory);


private:
	Disassembly();
	~Disassembly();

	//死骸Idと解体後アイテムのマスターをCsvから読み取り
	void LoadDisassemblyResult();

private:
	static Disassembly* instance;

	std::vector<std::shared_ptr<DisassemblyData>>disassemblyMaster;

};


class DisassemblyData
{
public:
	DisassemblyData(int id,std::string Name,int id1,int weight1, int id2, int weight2, int id3, int weight3, int id4, int weight4);
	~DisassemblyData();

public:

	//死骸Id	名前	解体後アイテムId1	ウェイト1	解体後アイテムId2	ウェイト2	解体後アイテムId3	ウェイト3	解体後アイテムId4	ウェイト4

	int fromId = 0;
	std::string name;
	std::unordered_map<int, int>disassemblyResult;

};
