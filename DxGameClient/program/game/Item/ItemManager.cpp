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
	//������URL�Ŏw�肳�ꂽCSV�t�@�C���̒��g�𕶎���Ƃ��Ď擾����
	auto loadCsv = tnl::LoadCsv(pass);


}


void ItemManager::update(float deltatime) {

}



void ItemManager::SpawnItem() {
	
}



