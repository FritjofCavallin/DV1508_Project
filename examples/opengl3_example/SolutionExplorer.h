#pragma once

#include "UIContainer.h"

#include <string>

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer();
	virtual ~SolutionExplorer();

	virtual void draw();

	const char* SolutionExplorer::CChar(std::string& s){ return s.data(); };
	char* SolutionExplorer::Char(std::string& s){ return &s[0]; };
	std::string AddSpace(std::string base, int comp = 0);

	//styles:
	void Style_VS_s();
	void Style_VS_f();

protected:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;

	//Timeline* effect;
	//std::vector<Timeline*> emitterTimelineVec;
	//std::vector<Timeline*> particleTimelineVec;

	bool firstDraw;
};

