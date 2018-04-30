#include "UITimelines.h"

UITimelines::UITimelines(Data* data)
{
	this->data = data;
}


UITimelines::~UITimelines()
{
}

void UITimelines::draw(ImVec2 pos, ImVec2 size)
{
	ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(2, 2));	// Reduce padding

	// Common stuff
	ImGui::Begin("Timelines", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings /*| ImGuiWindowFlags_NoTitleBar*/);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	ImGui::PopStyleVar();	// Restore padding

	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Timelines");
		ImGui::EndMenuBar();
	}

	ImGui::BeginChild("Timeline 1", ImVec2(ImGui::GetContentRegionAvail().x, 200), true, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Timeline 1");
		
		ImGui::SameLine(ImGui::GetContentRegionAvail().x * 0.1f);
		if (ImGui::Button("+", ImVec2(20, 0)))
		{
			// Add block
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted("Add block");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}

		ImGui::EndMenuBar();
	}

	for (int i = 0; i < 2; ++i)
	{
		ImGui::SetCursorPos(ImVec2(20 + 20 * i, 15 * i));
		if (ImGui::Button("Block", ImVec2(100 + i * 4, 30 + i * 2))) { }

	}
	
	ImGui::EndChild();

	ImGui::End();
}