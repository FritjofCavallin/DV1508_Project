#include <string>
#include <iomanip>
#include <sstream>

#include "UITimelines.h"
#include "Timelines/Timeline.h"
#include "Timelines/EmittBlocks/BoxVolumeBlock.h"
#include "Timelines/EmittBlocks/SpawnBlock.h"
#include "Timelines/ParticleBlocks/ForceBlock.h"
#include "Timelines/ParticleBlocks/ScaleBlock.h"

#define BUTTON_WIDTH 70

UITimelines::UITimelines(Data* data)
{
	this->data = data;
	_addingNewBlock = -1;
	_holdingBlockId = -1;

	_movingBlock = nullptr;

	blockNames[0] = new std::vector<std::string>();
	blockNames[0]->push_back("Test1");
	blockNames[0]->push_back("Test2");
	blockNames[0]->push_back("Test3");
	blockNames[1] = new std::vector<std::string>();
	blockNames[1]->push_back("Box\nVolume");
	blockNames[1]->push_back("Spawn");
	blockNames[2] = new std::vector<std::string>();
	blockNames[2]->push_back("Test1");
	blockNames[2]->push_back("Force");
	blockNames[2]->push_back("Scale");
	blockNames[2]->push_back("Test2");
	blockNames[2]->push_back("Test3");
}


UITimelines::~UITimelines()
{
	for (unsigned int i = 0; i < 3; ++i)
		delete blockNames[i];
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
	float menubarHeight = 21.0f;

	// Draw all open timelines
	for (int i = 0; i < data->getOpenCount(); ++i)
	{
		// Store reference to current timeline
		Timeline* timeline = data->getOpenTimeline(i);

		float timelineWidth = ImGui::GetContentRegionAvail().x;

		ImGui::BeginChild(timeline->_name.c_str(), ImVec2(timelineWidth, timelineHeight + (i == 0 ? 3.0f : 0.0f)), true, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			ImGui::Text(timeline->_name.c_str());

			std::string text;
			// Menu for linking particle to emitter
			if (timeline->_type == type::Emitter)
			{
				ImGui::SameLine(300);
				ImGui::Text("Linked particle: ");
				ImGui::SameLine();
				text = "[Click here to attach]";
				if (timeline->_particleLink != nullptr)
					text = timeline->_particleLink->_name;
				std::stringstream ss;
				ss << text << std::setw(30 - text.length()) << "";
				text = ss.str();
				if (ImGui::BeginMenu(text.c_str()))
				{
					std::list<Timeline*>& particles = data->getParticleTimelines();
					for (auto p : particles)
					{
						if (ImGui::Selectable(p->_name.c_str(), timeline->_particleLink == p))
							timeline->_particleLink = p;
					}
					ImGui::EndMenu();
				}
			}

			// Button for adding block
			text = "  +  ";
			if (_addingNewBlock == i)
				text = "  -  ";
			ImGui::SameLine(timelineWidth - 70);
			if (ImGui::Button(text.c_str(), ImVec2(43, 0)))
			{
				if (_addingNewBlock == i)
					_addingNewBlock = -1;
				else 
					_addingNewBlock = i;
			}
			// Tooltip
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				if (_addingNewBlock != i)
					ImGui::TextUnformatted("Add block");
				else
					ImGui::TextUnformatted("Cancel");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			ImGui::EndMenuBar();
		}

		// If the user has clicked the "+" in any timeline
		if (_addingNewBlock == i)
		{
			bool holdingButton = false;

			for (unsigned int b = 0; b < blockNames[timeline->_type]->size(); ++b)
			{
				// Choose start pos
				float startY = timelineHeight / 2 - BUTTON_WIDTH / 2 - menubarHeight;
				if (_holdingBlockId == b)
					ImGui::SetCursorPos(ImVec2(40 + (BUTTON_WIDTH + 15) * b + _moveDist.x, startY + _moveDist.y));
				else
					ImGui::SetCursorPos(ImVec2(40 + (BUTTON_WIDTH + 15) * b, startY));

				// Create button
				ImGui::Button(blockNames[timeline->_type]->at(b).c_str(), ImVec2(BUTTON_WIDTH, BUTTON_WIDTH));

				// Add click effect
				if (ImGui::IsItemActive())
				{
					_moveDist = ImGui::GetMouseDragDelta(0);
					_holdingBlockId = b;
					holdingButton = true;
				}

				// Add tool tip
				if (ImGui::IsItemHovered() && _holdingBlockId == -1)
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted("Short block info");
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				if (b != blockNames[timeline->_type]->size() - 1)
					ImGui::SameLine();
			}

			if (!holdingButton)
			{
				_holdingBlockId = -1;
			}

			// Help text
			ImGui::SetCursorPos(ImVec2(10, timelineHeight - 20));
			if (_holdingBlockId == -1)
				ImGui::Text("Click and hold on an icon...");
			else
				ImGui::Text("Now move it and release to place it in a channel");

			// Starts moving and closes the adding menu
			if (abs(_moveDist.x) > 20 || abs(_moveDist.y) > 20)
			{
				switch (timeline->_type)
				{
				case type::Effect:

					break;
				case type::Emitter:
					switch (_holdingBlockId)
					{
					case 0:
						_movingBlock = new BoxVolumeBlock(TimeInterval());
						break;
					case 1:
						_movingBlock = new SpawnBlock(TimeInterval());
						break;
					}
					break;
				case type::Particle:
					switch (_holdingBlockId)
					{
					case 0:
						_movingBlock = new ForceBlock(TimeInterval());
						break;
					case 1:
						_movingBlock = new ScaleBlock(TimeInterval());
						break;
					}
				}

				_moveDist = ImVec2(0, 0);
				_addingNewBlock = -1;
				_holdingBlockId = -1;
			}
		}
		else  // Showing the timeline as usual
		{
			float channelHeight = (int)ImGui::GetContentRegionAvail().y / timeline->_channel.size();
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
		}

		ImGui::EndChild();
	}

	ImGui::End();

	ImGui::PopStyleVar();	// Restore padding
}