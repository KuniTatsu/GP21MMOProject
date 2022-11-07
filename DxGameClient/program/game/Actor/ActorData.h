/*Actorの基本データを管理するクラス
	ステータスや画像なども含む
	個別の特別なステータス等がある場合は継承先で実装する方針で
*/
#pragma once


class ActorData
{
public:
	ActorData();
	~ActorData();

	//レンジのgetter,setter
	inline double GetAttackRange() {
		return attackRange;
	}
	inline void SetAttackRange(double setRange) {
		if (setRange < 0.0)return;
		attackRange = setRange;
	}


private:

	//通常攻撃の当たる距離(レンジ)基本値
	double attackRange = 0.0f;



};

