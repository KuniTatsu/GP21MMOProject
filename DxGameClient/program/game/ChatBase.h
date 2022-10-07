#pragma once
#include<string>
#include<vector>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;

class ChatBase
{
public:
	ChatBase();
	~ChatBase();

	//Œ»İ“ü—Í’†‚Ì•¶š—ñ‚ğ•`‰æ‚·‚éŠÖ”
	void DrawWritingMessage();
	//“ü—ÍŠÖ”
	void Write();

	//“ü—ÍŠ®—¹Œã‚Ì•¶š—ñ‚ğ•`‰æ‚·‚éŠÖ”
	void DrawAllMessage();

	//XVŠÖ”
	void Update();

	//•`‰æŠÖ”
	void Draw();

	int g_InputHandle;

	

private:
	//“ü—Í‚ªŠ®—¹‚µ‚½‚ ‚Æ‚Ì•¶š—ñ
	std::vector<std::string>savedMessage;
	//“ü—Í’†‚Ì•¶š—ñ
	std::string bufMessage;

	char buffer[100] = {};

	tnl::Sequence<ChatBase> sequence =
		tnl::Sequence<ChatBase>(this, &ChatBase::SeqWait);

	bool SeqDrawMessage(const float deltatime);
	bool SeqWait(const float deltatime);

	void CreateKeyInput();


	GameManager* gManager = nullptr;

};
