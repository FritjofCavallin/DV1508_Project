
#define NOMINMAX
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "UITimelines.h"
#include "Timelines/Timeline.h"
#include "Timelines/EmittBlocks/BoxVolumeBlock.h"
#include "Timelines/EmittBlocks/SpawnBlock.h"
#include "Timelines/EmittBlocks/TextureBlock.h"
#include "Timelines/ParticleBlocks/ColorBlock.h"
#include "Timelines/ParticleBlocks/ConstantForce.h"
#include "Timelines/ParticleBlocks/ForceBlock.h"
#include "Timelines/ParticleBlocks/GravityBlock.h"
#include "Timelines/ParticleBlocks/RotationBlock.h"
#include "Timelines/ParticleBlocks/ScaleBlock.h"
#include "Timelines/ParticleBlocks/TextureFadeBlock.h"
#include "Timelines/EffectBlock.h"

#define BUTTON_WIDTH 70

UITimelines::UITimelines(Data* data)
{
	this->data = data;
	_addingNewBlock = -1;
	_holdingBlockId = -1;

	// Effect blocks
	_blockInfos[0] = new std::vector<BlockInfo>();  // The items are added dynamically each frame
	
	// Emitter blocks
	_blockInfos[1] = new std::vector<BlockInfo>();
	std::vector<Block*> temp;
	temp.push_back(new BoxVolumeBlock({ 0, 0 }));
	temp.push_back(new SpawnBlock({ 0, 0 }));
	temp.push_back(new TextureBlock({ 0, 0 }, "", -1));
	for (auto& e : temp)
	{
		_blockInfos[1]->push_back({ e->visualName, e->desc });
	}
	temp.clear();

	// Particle blocks
	_blockInfos[2] = new std::vector<BlockInfo>();
	temp.push_back(new ColorBlock({ 0, 0 }));
	temp.push_back(new ConstantForce({ 0, 0 }));
	temp.push_back(new ForceBlock({ 0, 0 }));
	temp.push_back(new GravityBlock({ 0, 0 }));
	temp.push_back(new RotationBlock({ 0, 0 }));
	temp.push_back(new ScaleBlock({ 0, 0 }));
	temp.push_back(new TextureFadeBlock({ 0, 0 }, -1));
	for (auto& p : temp)
	{
		_blockInfos[2]->push_back({ p->visualName, p->desc });
	}
}


UITimelines::~UITimelines()
{
	for (unsigned int i = 0; i < 3; ++i)
		delete _blockInfos[i];
}

void UITimelines::draw(ImVec2 pos, ImVec2 size)
{
	ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(2, 2));	// Reduce padding

	// Common stuff
	ImGui::Begin("Timelines", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_NoTitleBar*/);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	// Adding info about emitters
	_blockInfos[0]->clear();
	std::string info;
	for (auto e : data->getEmitterTimelines())
	{
		info = "Length: " + std::to_string(e->_timeTotal.duration()) + " s\nChannels: " + std::to_string(e->_channel.size()) + "\nLinked particle:\n   ";
		if (e->_particleLink != nullptr)
			info += e->_particleLink->_name;
		else
			info += "None";
		_blockInfos[0]->push_back({ e->_name, info });
	}

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

		ImGuiIO& io = ImGui::GetIO();

		ImVec4 color = ImVec4(0.1f, 0, 0.2f, 1);
		if (timeline->_type == type::Emitter)
			color = ImVec4(0, 0.2f, 0.3f, 1);
		else if (timeline->_type == type::Effect)
			color = ImVec4(0, 0, 0.3f, 1);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, color);

		ImGui::BeginChild(timeline->_name.c_str(), ImVec2(timelineWidth, timelineHeight + (i == 0 ? 3.0f : 0.0f)), true, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar);

		if (ImGui::BeginMenuBar())
		{
			ImGui::Text(timeline->_name.c_str());

			std::string text;
			// Menu for linking particle to emitter
			if (timeline->_type == type::Emitter && _addingNewBlock != i)
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
					for (auto& p : particles)
					{
						ss.str("");
						ss << p->_name.c_str() << std::setw(30 - p->_name.length()) << "";
						if (ImGui::Selectable(ss.str().c_str(), timeline->_particleLink == p))
							timeline->_particleLink = p;
					}
					ImGui::EndMenu();
				}
			}

			// Button for adding block
			text = " Add new ";
			if (_addingNewBlock == i)
				text = " Cancel  ";
			ImGui::SameLine(timelineWidth - 200);
			if (ImGui::Button(text.c_str()))
			{
				if (_addingNewBlock == i)
					_addingNewBlock = -1;
				else 
					_addingNewBlock = i;
			}

			// Button for closing the timeline
			if (_addingNewBlock != i)
			{
				ImGui::SameLine(timelineWidth - 40);
				if (ImGui::Button("X", ImVec2(40, 0)))
				{
					data->closeTimeline(i);
				}
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted("Close timeline");
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}
			}

			ImGui::EndMenuBar();
		}
		
		float chCount = (float)(timeline ? timeline->_channel.size() : 1);
		float channelHeight = (int)ImGui::GetContentRegionAvail().y / chCount;

		// If the user has clicked to start adding a new block
		if (_addingNewBlock == i)
		{
			bool holdingButton = false;

			size_t blockTypes = _blockInfos[timeline->_type]->size();
			float startY = timelineHeight / 2 - BUTTON_WIDTH / 2;
			for (unsigned int b = 0; b < blockTypes; ++b)
			{
				// Choose start pos
				float startX = timelineWidth / 2 - (BUTTON_WIDTH + 15) * blockTypes / 2;
				if (_holdingBlockId == b)
					ImGui::SetCursorPos(ImVec2(startX + (BUTTON_WIDTH + 15) * b + _moveDist.x, startY + _moveDist.y));
				else
					ImGui::SetCursorPos(ImVec2(startX + (BUTTON_WIDTH + 15) * b, startY));

				// Create button
				ImGui::Button(_blockInfos[timeline->_type]->at(b)._name.c_str(), ImVec2(BUTTON_WIDTH, BUTTON_WIDTH));

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
					std::string text = _blockInfos[timeline->_type]->at(b)._name + "\n---------\n" + _blockInfos[timeline->_type]->at(b)._desc;
					ImGui::TextUnformatted(text.c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				if (b != blockTypes - 1)
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
				{
					auto& ets = data->getEmitterTimelines();
					int index = 0;
					for (auto& et : ets)
					{
						if (index == _holdingBlockId)
						{
							timeline->_movingBlock = new EffectBlock(et, TimeInterval());
							break;
						}
					}
					break;
				}
				case type::Emitter:
					switch (_holdingBlockId)
					{
					case 0:
						timeline->_movingBlock = new BoxVolumeBlock(TimeInterval());
						break;
					case 1:
						timeline->_movingBlock = new SpawnBlock(TimeInterval());
						break;
					case 2:
						timeline->_movingBlock = new TextureBlock(TimeInterval(), "", -1);
						break;
					}
					break;
				case type::Particle:
					switch (_holdingBlockId)
					{
					case 0:
						timeline->_movingBlock = new ColorBlock(TimeInterval());
						break;
					case 1:
						timeline->_movingBlock = new ConstantForce(TimeInterval());
						break;
					case 2:
						timeline->_movingBlock = new ForceBlock(TimeInterval());
						break;
					case 3:
						timeline->_movingBlock = new GravityBlock(TimeInterval());
						break;
					case 4:
						timeline->_movingBlock = new RotationBlock(TimeInterval());
						break;
					case 5:
						timeline->_movingBlock = new ScaleBlock(TimeInterval());
						break;
					case 6:
						timeline->_movingBlock = new TextureFadeBlock(TimeInterval(), -1);
						break;
					}
				}

				if (timeline->_movingBlock)
					timeline->_movingBlock->dragBodyYOffset = channelHeight * 0.5f;
				_moveDist = ImVec2(0, 0);
				_addingNewBlock = -1;
				_holdingBlockId = -1;
			}
		}
		else  // Showing the timeline as usual
		{
			// Check if the mouse if above the timeline
			if (ImGui::IsWindowHovered())
			{
				float& start = timeline->_timeShown._startTime;
				float& end = timeline->_timeShown._endTime;
				float half = (end - start) / 2;
				if (io.KeyCtrl)  // Pressing CTRL
				{
					// Zooming
					float zoomSpeed = 0.9;
					float center = start + half;
					if (io.MouseWheel > 0)  //Zooming in
					{
						half *= 0.93;
						start = center - half;
						end = center + half;
					}
					else if (io.MouseWheel < 0)  //Zooming out
					{
						half *= 1.07;
						start = std::max(center - half, 0.f);
						end = std::min(center + half, timeline->_timeTotal._endTime);
					}
				}
				else
				{
					// Panning
					float speed = half / 12.f;
					if (io.MouseWheel > 0)
					{
						end += speed;
						end = std::min(end, timeline->_timeTotal._endTime);
						start = end - 2 * half;
					}
					else if (io.MouseWheel < 0)
					{
						start -= speed;
						start = std::max(start, 0.f);
						end = start + 2 * half;
					}
				}
			}

			float timelineShownDuration = timeline->_timeShown.duration();

			// For every channel
			for (size_t c = 0; c < timeline->_channel.size(); ++c)
			{
				ImGui::PushID(c);
				// For every block in channel
				for (size_t b = 0; b < timeline->_channel[c]->_data.size(); ++b)
				{
					Block* block = timeline->_channel[c]->_data[b];

					float blockStart = (block->_time._startTime - timeline->_timeTotal._startTime) - timeline->_timeShown._startTime;
					float blockEnd = block->_time._endTime - timeline->_timeShown._startTime;

					float blockStartPos = ImGui::GetContentRegionAvail().x * (blockStart) / timelineShownDuration;
					float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineShownDuration;
					
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, handleLeftColor);
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, handleLeftActiveColor);
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, handleLeftHoveredColor);

					// Left handle
					ImGui::PushID(b);
					drawHandle(true, block, timeline, c, channelHeight);
					ImGui::PopStyleColor(3);

					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, handleRightColor);
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, handleRightActiveColor);
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, handleRightHoveredColor);

					// Right handle
					ImGui::PushID(b);
					drawHandle(false, block, timeline, c, channelHeight);
					ImGui::PopStyleColor(3);

					// Block main body
					ImGui::PushID(b);
					ImGui::SetCursorPos(ImVec2(blockStartPos, menubarHeight + channelHeight * c));
					if (ImGui::Button(block->visualName.c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * blockHeightRatio))) {}
					if (ImGui::IsItemActive() && !timeline->_movingBlock)
					{
						if (dragDistance.x != 0.0f || dragDistance.y != 0.0f)
						{
							timeline->_movingBlock = timeline->removeBlock(block, false);
							block->dragBodyStart = blockStartPos;
							block->dragBodyYOffset = io.MousePos.y - ImGui::GetWindowPos().y - (menubarHeight + channelHeight * c);
						}
					}

					ImGui::PopID();
					ImGui::PopID();
					ImGui::PopID();
				}
				ImGui::PopID();
			}

			// Draw vertical lines at bottom
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			float timeStart = timeline->_timeShown._startTime;
			float timeEnd = timeline->_timeShown._endTime;
			float duration = timeEnd - timeStart;
			float secLen = timelineWidth / duration;
			float curr = -timeStart;
			while (curr < timeEnd)
			{
				float x = pos.x + 3 + (curr) / duration * timelineWidth;
				float y = pos.y + 19 + (timelineHeight + 3) * (i + 1);
				ImGui::SetCursorPos(ImVec2(x - pos.x - 5, timelineHeight - 15 - i));
				ImGui::Text("%d", (int)(curr + timeStart + 0.9));
				draw_list->AddLine(ImVec2(x, y), ImVec2(x, y - 5), ImGui::GetColorU32(ImGuiCol_ButtonActive), 1.f);
				// 1/10
				for (unsigned int d = 0; d < 10; ++d)
				{
					draw_list->AddLine(ImVec2(x + secLen / 10 * d, y), ImVec2(x + secLen / 10 * d, y - 4), ImGui::GetColorU32(ImGuiCol_ButtonActive), 1.f);
					// 1/100
					for (unsigned int h = 1; h < 10; ++h)
					{
						draw_list->AddLine(ImVec2(x + secLen / 10 * d + secLen / 100 * h, y), ImVec2(x + secLen / 10 * d + secLen / 100 * h, y - 1), ImGui::GetColorU32(ImGuiCol_ButtonActive), 1.f);
					}
				}
				curr += 1.0f;
			}
		}

		// Dragged block
		drawDraggedBlock(timeline, channelHeight);
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	ImGui::End();

	ImGui::PopStyleVar();	// Restore padding
}


void UITimelines::drawHandle(bool left, Block* block, Timeline* timeline, int channelIndex, float channelHeight)
{
	bool* draggingBool = left ? &(block->draggingLeft) : &(block->draggingRight);
	float* editedTimeValue = left ? &(block->_time._startTime) : &(block->_time._endTime);
	ImGuiIO& io = ImGui::GetIO();

	float timelineShownDuration = timeline->_timeShown.duration();

	float blockStart = (block->_time._startTime - timeline->_timeTotal._startTime) - timeline->_timeShown._startTime;
	float blockEnd = block->_time._endTime - timeline->_timeShown._startTime;

	float blockStartPos = ImGui::GetContentRegionAvail().x * (blockStart) / timelineShownDuration;// + timeline->_timeShown._startTime * 2;
	float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineShownDuration;

	dragDistance = ImGui::GetMouseDragDelta(0);

	// If left mouse button is not pressed
	if (*draggingBool && io.MouseDownDuration[0] < 0.0f)
	{
		*draggingBool = false;
	}
	if (*draggingBool == true)
	{
		ImGui::SetMouseCursor(4);

		// Update start time
		*editedTimeValue = (((block->dragHandleStart + dragDistance.x) * timelineShownDuration)) / ImGui::GetContentRegionAvail().x + timeline->_timeShown._startTime;
		timeline->_channel[channelIndex]->correctBlockDuration(block, timeline->_timeTotal, left);
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
			block->dragHandleStart = blockStartPos + (left ? 0.0f : blockWidth);
		}
	}
}

void UITimelines::drawDraggedBlock(Timeline* timeline, float channelHeight)
{
	ImGuiIO& io = ImGui::GetIO();

	// Get mouse position relative to window and clamp it to within timeline channels
	ImVec2 mouseWindowPos = ImVec2(io.MousePos.x - ImGui::GetWindowPos().x, io.MousePos.y - ImGui::GetWindowPos().y);
	mouseWindowPos.x = std::min(std::max(mouseWindowPos.x, 0.0f), ImGui::GetWindowWidth());
	mouseWindowPos.y = std::min(std::max(mouseWindowPos.y, menubarHeight), ImGui::GetWindowHeight());
	float hoveredChannel = ((mouseWindowPos.y - menubarHeight) / (ImGui::GetWindowHeight() - menubarHeight)) * timeline->_channel.size();
	if (((unsigned int)hoveredChannel) >= timeline->_channel.size())
		hoveredChannel = (float)(timeline->_channel.size() - 1);

	// If mouse is in the upper 20% of the channel, insert a channel and then add block there
	float hoveredChannelFrac = (hoveredChannel - ((float)((int)hoveredChannel)));
	bool insertChannel = hoveredChannelFrac <= 0.2f;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->PushClipRectFullScreen();
	// Draw a line between channels to signify insertion
	if (insertChannel && timeline->_movingBlock && mouseWindowPos.y < ImGui::GetWindowPos().y + ImGui::GetWindowHeight())
	{
		draw_list->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel)),
			ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel)), ImGui::GetColorU32(ImGuiCol_Button), 4.0f);
	}
	// Draw a line over the channel being inserted into
	else if (timeline->_movingBlock)
	{
		draw_list->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) + channelHeight * 0.5f),
			ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) + channelHeight * 0.5f), ImGui::GetColorU32(ImGuiCol_Button), channelHeight);
	}
	draw_list->PopClipRect();

	// If mouse button is not held
	if (timeline->_movingBlock && io.MouseDownDuration[0] < 0.0f)
	{
		// Place block. If placement fails, restore its position
		if (!timeline->addBlock(timeline->_movingBlock, (int)hoveredChannel, insertChannel))
		{
			float timelineDuration = timeline->_timeTotal.duration();
			TimeInterval* movingBlockTime = &(timeline->_movingBlock->_time);
			float blockStart = movingBlockTime->_startTime - timeline->_timeTotal._startTime;
			float blockEnd = movingBlockTime->_endTime - timeline->_timeTotal._startTime;

			movingBlockTime->_startTime = (((timeline->_movingBlock->dragBodyStart + dragDistance.x) * timelineDuration)) / ImGui::GetContentRegionAvail().x + timeline->_timeTotal._startTime;
			movingBlockTime->_endTime = movingBlockTime->_startTime + blockEnd - blockStart;

			// If placing fails again, delete block
			if (!timeline->addBlock(timeline->_movingBlock, (int)hoveredChannel, insertChannel))
				delete timeline->_movingBlock;
		}

		timeline->_movingBlock = nullptr;
	}

	// Update moving block
	if (timeline->_movingBlock)
	{
		//float timelineDuration = timeline->_timeTotal.duration();

		TimeInterval* movingBlockTime = &(timeline->_movingBlock->_time);

		float timelineShownDuration = timeline->_timeShown.duration();

		float blockStart = (timeline->_movingBlock->_time._startTime - timeline->_timeTotal._startTime) - timeline->_timeShown._startTime;
		float blockEnd = timeline->_movingBlock->_time._endTime - timeline->_timeShown._startTime;

		float blockStartPos = ImGui::GetContentRegionAvail().x * (blockStart) / timelineShownDuration;
		float blockWidth = ImGui::GetContentRegionAvail().x * (blockEnd - blockStart) / timelineShownDuration;

		movingBlockTime->_startTime = (((timeline->_movingBlock->dragBodyStart + dragDistance.x) * timelineShownDuration)) 
										/ ImGui::GetContentRegionAvail().x + timeline->_timeShown._startTime;
		movingBlockTime->_endTime = movingBlockTime->_startTime + blockEnd - blockStart;

		// Correct if outside timeline interval
		if (movingBlockTime->_startTime < timeline->_timeTotal._startTime)
		{
			movingBlockTime->_startTime = timeline->_timeTotal._startTime;
			movingBlockTime->_endTime = timeline->_timeTotal._startTime + blockEnd - blockStart;
		}
		if (movingBlockTime->_endTime > timeline->_timeTotal._endTime)
		{
			movingBlockTime->_endTime = timeline->_timeTotal._endTime;
			movingBlockTime->_startTime = timeline->_timeTotal._endTime - (blockEnd - blockStart);
		}

		// Draw block
		float cursorY = std::min(std::max(mouseWindowPos.y - timeline->_movingBlock->dragBodyYOffset, menubarHeight), ImGui::GetWindowHeight() - channelHeight * blockHeightRatio);
		ImGui::SetCursorPos(ImVec2(blockStartPos, cursorY));
		if (ImGui::Button(timeline->_movingBlock->visualName.c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * blockHeightRatio))) {}
	}
}
