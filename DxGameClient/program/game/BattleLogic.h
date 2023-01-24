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
	double CalcDefaultDamage(float attack, float defence, int level, bool isSuccess, float coreDamage = 50.0f, float fixRatio = 1.0f);

	//有効な攻撃かどうか判定する関数
	bool IsSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType);




public:
	enum class ATTACKTYPE :uint32_t {
		MELEE,
		RANGE,
		MAX
	};

private:

	BattleLogic();
	~BattleLogic();

	//有効率計算
	float CalcSuccessRatio(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData);

	//攻撃強制成功判定
	bool IsForceSuccessAttack(const std::shared_ptr<ActorData> AttackerData, const std::shared_ptr<ActorData> DefenderData, int attackType);


private:
	static BattleLogic* instance;


};

