#pragma once
#include<unordered_map>
#include<string>


class GameManager;


class JobLevelInfo {
public:

public:

	JobLevelInfo(int TalentId, int JobId1, std::string JobName1, int BonusValue1, int JobId2, std::string JobName2, int BonusValue2);
	~JobLevelInfo();

	// --------------------------------------------------------------------------------


	// ----------------------------------------------------------------------
	inline const std::vector<std::string>& GetJobNames() {
		return names;
	}

	// --------------------------------------------------------------------------------

	//�^�����gID�擾
	inline const int GetTalentId() {
		return talentId;
	}
	//�E�ƃ{�[�i�X�l�̑g�ݍ��킹��Map��Ԃ��֐�
	inline const std::unordered_map<int, int>& GetInfoMap() {
		return info;
	}

	// ------��ڂ̐E�̃{�[�i�X�o���l����ڂ̐E�ƈႤ�ꍇ�̂݃R�����g�A�E�g---------

	/*inline const int& GetBonusValue() {
		return info.at(jobId2);
	}*/

	// --------------------------------------------------------------------------------

private:
	std::unordered_map<int, int> info;	// �E�ɑ΂���{�[�i�X�l�̊i�[
	int talentId = 0;					// �^�����gID
	std::vector<std::string> names;


private:
};