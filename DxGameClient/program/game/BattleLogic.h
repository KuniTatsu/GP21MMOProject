#pragma once
#include"../dxlib_ext/dxlib_ext.h"
#include"Actor/ActorData.h"
#include<memory>


class BattleLogic
{
public:
	// インスタンスの取得
	static BattleLogic* GetInstance();


	//ダメージ計算 args1:攻撃力 args2:防御力 args3:職レベル合計 args4:基礎ダメージ デフォルトは通常攻撃の値 args5:最終補正
	float CalcDefaultDamage(float attack, float defence, int level, float coreDamage = 50.0f, float fixRatio = 1.0f);

	//有効な攻撃かどうか判定する関数
	bool isSuccessAttack(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData);

	
	

public:


private:

	BattleLogic();
	~BattleLogic();

	//有効率計算
	float calcSuccessRatio(std::shared_ptr<ActorData>& AttackerData, std::shared_ptr<ActorData>& defenderData);

private:
	static BattleLogic* instance;


};

