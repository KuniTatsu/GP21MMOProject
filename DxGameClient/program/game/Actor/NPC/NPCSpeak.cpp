#include"NPCSpeak.h"


NPCSpeak::NPCSpeak(int id, std::string name, std::string speak)
{
	textId = id;
	textName = name;
	text = speak;
}

NPCSpeak::~NPCSpeak()
{
}