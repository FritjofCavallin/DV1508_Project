#pragma once

#include "UIContainer.h"

#include <string>

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer(Data* data);
	virtual ~SolutionExplorer();

	virtual void draw(ImVec2 pos, ImVec2 size);

	void AddNewFile(std::string name, bool isEmitter, bool open);
	void AddExistingFile();
	void OpenFileInWorkspace(/*Timeline* file*/);
	 
	std::string AddSpace(std::string base, int comp = 0);

	//styles:
	void Style_VS_Text_s();
	void Style_VS_Text_f();

	void Style_VS_Node_s();
	void Style_VS_Node_f();

protected:
	//ImGui
	ImVec2 winPos, winSize;

	//Timeline* effect;
	//std::vector<Timeline*> emitterTimelineVec;
	//std::vector<Timeline*> particleTimelineVec;

	//might want to add next-frame-do-stuff list
	bool firstDraw;
	bool drawNewFilePopup;
};

