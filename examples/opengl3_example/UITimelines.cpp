#include "UITimelines.h"
#include "Timelines/Timeline.h"

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
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_NoTitleBar*/);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Timelines");
		ImGui::EndMenuBar();
	}

	float timelineHeight = (ImGui::GetContentRegionAvail().y - (ImGui::GetStyle().WindowPadding.y + 1.0f) * (data->getOpenCount())) / data->getOpenCount();
	// Draw all open timelines
	for (int i = 0; i < data->getOpenCount(); ++i)
	{
		// Store reference to current timeline
		Timeline* timeline = data->getOpenTimeline(i);

		ImGui::BeginChild(timeline->_name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, timelineHeight + (i == 0 ? 3.0f : 0.0f)), true, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			ImGui::Text(timeline->_name.c_str());

			//ImGui::SameLine(ImGui::GetContentRegionAvail().x * 0.1f);
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

		for (int i = 0; i < 1; ++i)
		{
			ImGui::SetCursorPos(ImVec2(50 + 20 * i, 60 + 15 * i));
			if (ImGui::Button("Block", ImVec2(100 + i * 4, 30 + i * 2))) {}

		}

		ImGui::EndChild();
	}

	ImGui::End();

	ImGui::PopStyleVar();	// Restore padding
}