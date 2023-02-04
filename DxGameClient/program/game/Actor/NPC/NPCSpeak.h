#pragma once
#include<string>


//一つ一つのNPCの話す内容のクラス
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