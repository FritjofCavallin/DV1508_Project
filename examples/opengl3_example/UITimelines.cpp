#include <algorithm>
#include <string>

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

		float channelHeight = (int) std::min(ImGui::GetContentRegionAvail().y / timeline->_channel.size(), 150.0f);
		float timelineDuration = timeline->_time.duration();


		// For every channel
		for (int c = 0; c < timeline->_channel.size(); ++c)
		{
			ImGui::PushID(c);
			// For every block in channel
			for (int b = 0; b < timeline->_channel[c]->_data.size(); ++b)
			{
				Block* block = timeline->_channel[c]->_data[b];

				float blockStart = block->_time._startTime;
				float blockEnd = block->_time._endTime;

				float blockStartPos = ImGui::GetContentRegionAvail().x * blockStart / timelineDuration;
				float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineDuration;


				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, handleColor);
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, handleActiveColor);
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, handleHoveredColor);

				// Left handle
				ImGui::PushID(b);
				drawHandle(true, block, timeline, c, channelHeight);

				// Right handle
				ImGui::PushID(b);
				drawHandle(false, block, timeline, c, channelHeight);

				ImGui::PopID();
				ImGui::PopID();
				ImGui::PopStyleColor(3);

				// Block main body
				ImGui::SetCursorPos(ImVec2(blockStartPos, menubarHeight + channelHeight * c));
				if (ImGui::Button(std::to_string(block->_time._endTime).c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * 0.8f))) {}
			}
			ImGui::PopID();
		}

		ImGui::EndChild();
	}

	ImGui::End();

	ImGui::PopStyleVar();	// Restore padding
}

void UITimelines::drawHandle(bool left, Block* block, Timeline* timeline, int channelIndex, float channelHeight)
{
	bool* draggingBool = left ? &(block->draggingLeft) : &(block->draggingRight);
	float* editedTimeValue = left ? &(block->_time._startTime) : &(block->_time._endTime);
	ImGuiIO& io = ImGui::GetIO();
	float timelineDuration = timeline->_time.duration();

	float blockStart = block->_time._startTime;
	float blockEnd = block->_time._endTime;

	float blockStartPos = ImGui::GetContentRegionAvail().x * blockStart / timelineDuration;
	float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineDuration;

	dragDistance = ImGui::GetMouseDragDelta(0.0f);

	// If left mouse button is not pressed
	if (*draggingBool && io.MouseDownDuration[0] < 0.0f)
	{
		*draggingBool = false;
	}
	if (*draggingBool == true)
	{
		ImGui::SetMouseCursor(4);

		// Update start time
		*editedTimeValue = (block->dragStart + dragDistance.x) * timelineDuration / ImGui::GetContentRegionAvail().x;
		timeline->_channel[channelIndex]->correctBlockDuration(block, timeline->_time, left);
	}
	if (left)
		ImGui::SetCursorPos(ImVec2(blockStartPos, menubarHeight + channelHeight * channelIndex));
	else
		ImGui::SetCursorPos(ImVec2(blockStartPos + blockWidth - blockHandleWidth, menubarHeight + channelHeight * channelIndex));

	if (ImGui::Button("", ImVec2(blockHandleWidth, channelHeight))) {}
	if (ImGui::IsItemHovered() || ImGui::IsItemFocused())
		ImGui::SetMouseCursor(4);
	if (ImGui::IsItemActive() && !*draggingBool)
	{
		if (dragDistance.x != 0.0f || dragDistance.y != 0.0f)
		{
			*draggingBool = true;
			block->dragStart = blockStartPos + (left ? 0.0f : blockWidth);

		}
	}
}
