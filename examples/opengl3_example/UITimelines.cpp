
#define NOMINMAX
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <typeinfo>

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
}


UITimelines::~UITimelines()
{
}

void UITimelines::draw(ImVec2 pos, ImVec2 size)
{
	ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(2, 2));	// Reduce padding

	// Common stuff
	ImGui::Begin("Timelines", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse/*| ImGuiWindowFlags_NoTitleBar*/);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	// Adding info about emitters
	data->_blockInfos[0]->clear();
	std::string info;
	for (auto e : data->getEmitterTimelines())
	{
		info = "Length: " + std::to_string(e->_timeTotal.duration()) + " s\nChannels: " + std::to_string(e->_channel.size()) + "\nLinked particle:\n   ";
		if (e->_particleLink != nullptr)
			info += e->_particleLink->_name;
		else
			info += "None";
		data->_blockInfos[0]->push_back({ nullptr, e->_name, info, ImVec4() });
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

		ImGui::PushStyleColor(ImGuiCol_ChildBg, data->_bgColors[timeline->_type]);

		ImGui::BeginChild(timeline->_name.c_str(), ImVec2(timelineWidth, timelineHeight + (i == 0 ? 3.0f : 0.0f)), true, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse);

		if (ImGui::BeginMenuBar())
		{
			ImGui::Text(timeline->_name.c_str());

			std::string text;
			// Menu for linking particle to emitter
			if (timeline->_type == type::Emitter && _addingNewBlock != i && timeline->_movingBlock == nullptr)
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

			// Info text when moving a block
			if (timeline->_movingBlock != nullptr)
			{
				ImGui::SameLine(timelineWidth / 2 - 40);
				ImGui::Text("Drag here to delete block");
			}

			// Button for adding block
			if (timeline->_movingBlock == nullptr)
			{
				text = " Add block ";
				if (_addingNewBlock == i)
					text = "  Cancel   ";
				ImGui::SameLine(timelineWidth - 300);
				if (ImGui::Button(text.c_str()))
				{
					if (_addingNewBlock == i)
						_addingNewBlock = -1;
					else
						_addingNewBlock = i;
				}
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted("Add new block to the timeline");
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}
			}


			// Set timeline duration
			if (_addingNewBlock != i && timeline->_movingBlock == nullptr)
			{
				ImGui::SameLine(timelineWidth - 180);
				ImGui::Text("Time:");
				ImGui::PushItemWidth(50);
				if (ImGui::InputFloat("", &timeline->_timeTotal._endTime, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					timeline->_timeShown._startTime = 0.f;
					timeline->_timeShown._endTime = timeline->_timeTotal._endTime;
					// For every channel
					for (int c = timeline->_channel.size() - 1; c >= 0; --c)
					{
						// For every block in channel
						for (int b = timeline->_channel[c]->_data.size() - 1; b >= 0; --b)
						{
							Block* block = timeline->_channel[c]->_data[b];

							// Block is no longer within timeline
							if (block->_time._startTime > timeline->_timeTotal._endTime)
								timeline->_channel[c]->_data.erase(timeline->_channel[c]->_data.begin() + b);
							else
								block->_time._endTime = std::min(block->_time._endTime, timeline->_timeTotal._endTime);
						}
					}
				}
				ImGui::PopItemWidth();
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted("Set the duration of the timeline");
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				// Button for closing the timeline
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
		float channelHeight = std::fminf(std::max((int)(ImGui::GetContentRegionAvail().y / chCount), minChannelHeight), maxChannelHeight);

		// If the user has clicked to start adding a new block
		if (_addingNewBlock == i)
		{
			bool holdingButton = false;

			size_t blockTypes = data->_blockInfos[timeline->_type]->size();
			float startY = timelineHeight / 2 - BUTTON_WIDTH / 2;
			int count = 1;
			for (unsigned int b = 0; b < blockTypes; ++b)
			{
				// Choose start pos
				float startX = timelineWidth / 2 - (BUTTON_WIDTH + 15) * blockTypes / 2;
				if (_holdingBlockId == b)
					ImGui::SetCursorPos(ImVec2(startX + (BUTTON_WIDTH + 15) * b + _moveDist.x, startY + _moveDist.y));
				else
					ImGui::SetCursorPos(ImVec2(startX + (BUTTON_WIDTH + 15) * b, startY));

				// Create button
				ImVec4 color = ImVec4(1, 70 * count / 255.f, 0, 1);

				if (timeline->_type != type::Effect)
					color = data->_blockInfos[timeline->_type]->at(b)._color;
				else
					++count;

				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, color);
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, MC(color, 0.1f));
				ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, MC(color, 0.2f));
				ImGui::Button(data->_blockInfos[timeline->_type]->at(b)._name.c_str(), ImVec2(BUTTON_WIDTH, BUTTON_WIDTH));
				ImGui::PopStyleColor(3);

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
					std::string text = data->_blockInfos[timeline->_type]->at(b)._name + "\n---------\n" + data->_blockInfos[timeline->_type]->at(b)._desc;
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
				float start = timeline->_timeShown._startTime;
				float end = timeline->_timeShown._endTime;
				TimeInterval time = TimeInterval(start, end);
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
							timeline->_movingBlock = new EffectBlock(et, time);
							break;
						}
					}
					break;
				}
				case type::Emitter:
					switch (_holdingBlockId)
					{
					case 0:
						timeline->_movingBlock = new BoxVolumeBlock(time);
						break;
					case 1:
						timeline->_movingBlock = new SpawnBlock(time);
						break;
					case 2:
						timeline->_movingBlock = new TextureBlock(time, "", -1);
						break;
					}
					break;
				case type::Particle:
					switch (_holdingBlockId)
					{
					case 0:
						timeline->_movingBlock = new ColorBlock(time);
						break;
					case 1:
						timeline->_movingBlock = new ConstantForce(time);
						break;
					case 2:
						timeline->_movingBlock = new ForceBlock(time);
						break;
					case 3:
						timeline->_movingBlock = new GravityBlock(time);
						break;
					case 4:
						timeline->_movingBlock = new RotationBlock(time);
						break;
					case 5:
						timeline->_movingBlock = new ScaleBlock(time);
						break;
					case 6:
						timeline->_movingBlock = new TextureFadeBlock(time, -1);
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
			if (ImGui::IsWindowHovered() || timeline->_movingBlock)
			{
				float& start = timeline->_timeShown._startTime;
				float& end = timeline->_timeShown._endTime;
				float half = (end - start) / 2;
				if (io.KeyCtrl)  // Pressing CTRL
				{
					// Zooming
					float zoomSpeed = 0.9f;
					float center = start + half;
					if (io.MouseWheel > 0)  //Zooming in
					{
						half *= 0.93f;
						start = center - half;
						end = center + half;
					}
					else if (io.MouseWheel < 0)  //Zooming out
					{
						half *= 1.07f;
						start = std::max(center - half, 0.f);
						end = std::min(center + half, timeline->_timeTotal._endTime);
					}
				}
				else if (io.KeyShift && !io.KeyCtrl)
				{
					// Panning
					float speed = half / 9.f;
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
				else
				{
					if (io.MouseWheel > 0)
					{
						float startScroll = ImGui::GetScrollY();
						ImGui::SetScrollY(ImGui::GetScrollY() - channelHeight * 2.0f);
						float scroll = startScroll - channelHeight * 2.0f;
						if (scroll < 0) scroll = 0;
						if (scroll > ImGui::GetScrollMaxY()) scroll = ImGui::GetScrollMaxY();

						if (timeline->_movingBlock)
						{
							timeline->_movingBlock->dragBodyYOffset -= scroll - startScroll;
						}
					}
					else if (io.MouseWheel < 0)
					{
						float startScroll = ImGui::GetScrollY();
						ImGui::SetScrollY(ImGui::GetScrollY() + channelHeight * 2.0f);
						float scroll = startScroll + channelHeight * 2.0f;
						if (scroll < 0) scroll = 0;
						if (scroll > ImGui::GetScrollMaxY()) scroll = ImGui::GetScrollMaxY();

						if (timeline->_movingBlock)
						{
							timeline->_movingBlock->dragBodyYOffset -= scroll - startScroll;
						}
					}
				}
			}

			float timelineShownDuration = timeline->_timeShown.duration();

			int count = 1;
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
					ImVec4 color = ImVec4(1, 70 * count / 255.f, 0, 1);
					
					if (timeline->_type != type::Effect)
					{
						for (unsigned int n = 0; n < data->_blockInfos[timeline->_type]->size(); ++n)
						{
							if (typeid(*block) == typeid(*data->_blockInfos[timeline->_type]->at(n)._type))
								color = data->_blockInfos[timeline->_type]->at(n)._color;
						}
					}
					else
						++count;

					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, color);
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, MC(color, 0.15f));
					ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, MC(color, 0.3f));
					ImGui::SetCursorPos(ImVec2(blockStartPos, menubarHeight + channelHeight * c));
					if (ImGui::Button(block->visualName.c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * blockHeightRatio)))
					{
						data->_selectedBlock = block;
					}

					ImGui::PopStyleColor(3);
					if (ImGui::IsItemActive() && !timeline->_movingBlock)
					{
						if (dragDistance.x != 0.0f || dragDistance.y != 0.0f)
						{
							timeline->_movingBlock = timeline->removeBlock(block, false);
							block->dragBodyStart = blockStartPos;
							block->dragBodyYOffset = io.MousePos.y - ImGui::GetWindowPos().y - (menubarHeight + channelHeight * c);
						}
					}

					// Icon
					if (iconTextures.find(block->iconName) == iconTextures.end())
						createIconTexture(block->iconName);

					ImGui::SetCursorPos(ImVec2(blockStartPos + blockHandleWidth, menubarHeight + channelHeight * c));
					ImGui::Image(reinterpret_cast<ImTextureID>(iconTextures[block->iconName]), ImVec2(channelHeight * blockHeightRatio, channelHeight * blockHeightRatio), ImVec2(0, 0), ImVec2(1, 1));

					ImGui::PopID();
					ImGui::PopID();
					ImGui::PopID();
				}

				// For the last timeline, if it is empty, draw a dummy to ensure that it shows up in a timeline with vertical scrolling
				if (timeline->_channel[c]->_data.size() == 0 && c == timeline->_channel.size() - 1)
				{
					ImGui::SetCursorPos(ImVec2(0, menubarHeight + channelHeight * c));
					ImGui::Dummy(ImVec2(0, channelHeight));
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
				ImGui::SetCursorPos(ImVec2(x - pos.x - 5, timelineHeight - 15 - i + ImGui::GetScrollY()));
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

	float blockStartPos = ImGui::GetContentRegionAvail().x * (blockStart) / timelineShownDuration;
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
	mouseWindowPos.y = std::min(std::max(mouseWindowPos.y, 0.f), ImGui::GetWindowHeight());
	float hoveredChannel = ((mouseWindowPos.y - menubarHeight + ImGui::GetScrollY()) / (timeline->_channel.size() * channelHeight - menubarHeight)) * timeline->_channel.size();
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
		draw_list->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) - ImGui::GetScrollY()),
			ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) - ImGui::GetScrollY()), ImGui::GetColorU32(ImGuiCol_Button), 4.0f);
	}
	// Draw a line over the channel being inserted into
	else if (timeline->_movingBlock)
	{
		draw_list->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) + channelHeight * 0.5f - ImGui::GetScrollY()),
			ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + menubarHeight + channelHeight * ((int)hoveredChannel) + channelHeight * 0.5f - ImGui::GetScrollY()), ImGui::GetColorU32(ImGuiCol_Button), channelHeight);
	}
	draw_list->PopClipRect();

	// If mouse button is not held
	if (timeline->_movingBlock && io.MouseDownDuration[0] < 0.0f)
	{
		// Delete block if the mouse cursor is on the menu bar
		if (_onMenuBar)
		{
			delete timeline->_movingBlock;
			timeline->channelCleanup();
		}
		// Place block. If placement fails, restore its position
		else if (!timeline->addBlock(timeline->_movingBlock, (int)hoveredChannel, insertChannel))
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
		float cursorY = std::min(std::max(mouseWindowPos.y - timeline->_movingBlock->dragBodyYOffset, 0.f), ImGui::GetWindowHeight() + ImGui::GetScrollMaxY() - channelHeight * blockHeightRatio - 3);
		ImGui::SetCursorPos(ImVec2(blockStartPos, cursorY));
		if (mouseWindowPos.y < 21)
		{
			_onMenuBar = true;
			ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(1, 0, 0, 1));
			if (ImGui::Button(timeline->_movingBlock->visualName.c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * blockHeightRatio))) {}
			ImGui::PopStyleColor();
		}
		else
		{
			_onMenuBar = false;
			if (ImGui::Button(timeline->_movingBlock->visualName.c_str(), ImVec2(std::max(blockWidth, minBlockWidth), channelHeight * blockHeightRatio))) {}
		}

		// Icon
		if (iconTextures.find(timeline->_movingBlock->iconName) == iconTextures.end())
			createIconTexture(timeline->_movingBlock->iconName);

		ImGui::SetCursorPos(ImVec2(blockStartPos + blockHandleWidth, cursorY));
		ImGui::Image(reinterpret_cast<ImTextureID>(iconTextures[timeline->_movingBlock->iconName]), ImVec2(channelHeight * blockHeightRatio, channelHeight * blockHeightRatio), ImVec2(0, 0), ImVec2(1, 1));
	}
}

void UITimelines::createIconTexture(std::string iconName)
{
	std::string path("Icons\\");
	path += iconName;
	unsigned texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{

	}
	stbi_image_free(data);

	iconTextures[iconName] = texture;
}
