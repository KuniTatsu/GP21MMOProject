#pragma once
#include<string>


//����NPC�̘b�����e�̃N���X
class NPCSpeak
{
public:
	NPCSpeak(int id, std::string name, std::string speak);
	~NPCSpeak();

	inline std::string GetTextName() {
		return textName;
	}
	inline std::string GetText() {
		return text;
	}

private:

	int textId = 0;
	std::string textName = "";
	std::string text = "";
};