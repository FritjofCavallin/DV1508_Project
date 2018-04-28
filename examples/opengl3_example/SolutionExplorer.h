#pragma once

#include "UIContainer.h"

#include <string>

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer();
	virtual ~SolutionExplorer();

	virtual void draw();
	void AddNewFile(std::string name, bool isEmitter, bool open);
	void AddExistingFile();
	void OpenFileInWorkspace(/*Timeline* file*/);

	const char* SolutionExplorer::CChar(std::string& s){ return s.data(); };
	char* SolutionExplorer::Char(std::string& s){ return &s[0]; };
	std::string AddSpace(std::string base, int comp = 0);

	//styles:
	void Style_VS_Text_s();
	void Style_VS_Text_f();

	void Style_VS_Node_s();
	void Style_VS_Node_f();

protected:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;

	//Timeline* effect;
	//std::vector<Timeline*> emitterTimelineVec;
	//std::vector<Timeline*> particleTimelineVec;

	//might want to add next-frame-do-stuff list
	bool firstDraw;
	bool drawNewFilePopup;
};

