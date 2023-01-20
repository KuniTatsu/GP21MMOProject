/*
全てのアイテムクラスの基底クラス
	アイテムに関する基本情報を持つ

*/

#pragma once

class Item
{
public:

	Item();
	~Item();
private:

	
//アイテム種類
	int ItemId = 0;


//所持アイテム数
	int FullStackNum = 0;
//アイテムのランク
	int ItemRareRank = 0;
};

