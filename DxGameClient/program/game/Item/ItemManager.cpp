#include "ItemManager.h"

ItemManager::ItemManager()
{
	fieldDropItems.clear();
	itemMaster.resize(static_cast<int>(ITEMTYPE::MAX));
}

ItemManager::~ItemManager()
{
}

void ItemManager::LoadItemCsv(std::string pass, std::vector< std::vector<int>>& putInVector, int type) {
	//引数のURLで指定されたCSVファイルの中身を文字列として取得する
	auto loadCsv = tnl::LoadCsv(pass);


}


void ItemManager::update(float deltatime) {

}



void ItemManager::SpawnItem() {
	
}



