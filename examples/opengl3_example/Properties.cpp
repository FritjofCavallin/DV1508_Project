#include "Properties.h"

Properties::Properties(){
	winPosX = 300, winPosY = 626;
	winSizeX = 600, winSizeY = 454;

	//currBlock = nullptr;
}


Properties::~Properties(){
}

void Properties::draw(ImVec2 pos, ImVec2 size){
	// Common stuff
	ImGui::Begin("Properties", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	if(/*currBlock == nullptr*/true){
		//show help prompt
	}
	else{
		//show block properties
	}

	ImGui::End();
}
