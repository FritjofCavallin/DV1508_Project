#pragma once

#include "UIContainer.h"
#include <string>

class Properties : public UIContainer
{
public:
	Properties();
	virtual ~Properties();
	virtual void draw(ImVec2 pos, ImVec2 size);

	const char* CChar(std::string& s){ return s.data(); };
	char* Char(std::string& s){ return &s[0]; };
	std::string AddSpace(std::string base, int comp = 0);
	std::string CenterString(std::string base, int comp = 0);

	//styles:
	void Style_VS_Text_s();
	void Style_VS_Text_f();

	void Style_VS_Node_s();
	void Style_VS_Node_f();

private:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;
	ImVec2 winPos, winSize;

	//Block* currBlock;

	bool firstDraw;
};

