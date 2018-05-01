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

		float channelHeight = (int) ImGui::GetContentRegionAvail().y / timeline->_channel.size();
		float menubarHeight = 21.0f;
		float timelineDuration = timeline->_time.duration();

		// For every channel
		for (int c = 0; c < timeline->_channel.size(); ++c)
		{
			// For every block in channel
			for (int b = 0; b < timeline->_channel[c]->_data.size(); ++b)
			{
				// Block main body
				float blockStart = timeline->_channel[c]->_data[b]->_time._startTime;
				float blockEnd = timeline->_channel[c]->_data[b]->_time._endTime;

				float blockStartPos = ImGui::GetContentRegionAvail().x * blockStart / timelineDuration;
				float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineDuration;

				ImGui::SetCursorPos(ImVec2(blockStartPos, menubarHeight + channelHeight * c));
				if (ImGui::Button("Block", ImVec2(blockWidth, channelHeight * 0.8f))) {}
			}
		}

		ImGui::EndChild();
	}

	ImGui::End();

	ImGui::PopStyleVar();	// Restore padding
}