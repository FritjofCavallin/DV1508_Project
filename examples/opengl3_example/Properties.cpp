#include "Properties.h"

Properties::Properties(){
	winPosX = 300, winPosY = 626;
	winSizeX = 600, winSizeY = 454;

	//currBlock = nullptr;

	firstDraw = true;
}


Properties::~Properties(){
}

void Properties::draw(ImVec2 pos, ImVec2 size){
	// Common stuff
	ImGui::Begin("Properties", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	if(firstDraw){
		winPos = pos;
		winSize = size;
	}

	if(/*currBlock == nullptr*/true){
		//show help prompt

	}
	else{
		//show block properties
	}

	firstDraw = false;
	ImGui::End();
}

std::string Properties::AddSpace(std::string base, int comp){
	//1 space = 7 pixels wide
	int spaces = (int)((winSize.x - comp - base.length()) / 7);
	for(int i = 0; i < spaces; ++i) base += " ";

	return base;
}

std::string Properties::CenterString(std::string base, int comp){
	std::string newStr = "";
	int spaces = (int)((winSize.x - comp - base.length()) / (7*2));

	for(int i = 0; i < spaces; ++i) newStr += " ";
	newStr += base;
	for(int i = 0; i < spaces; ++i) newStr += " ";

	return newStr;
}