#include <iostream>

#include "Data.h"
#include "../Test/TestParticles.h"
#include "../Particles/ParticleManager.h"
#include "../Window/PreviewWindow.h"

#include "EmittBlocks/BoxVolumeBlock.h"
#include "EmittBlocks/SpawnBlock.h"
#include "EmittBlocks/TextureBlock.h"
#include "ParticleBlocks/ColorBlock.h"
#include "ParticleBlocks/ConstantForce.h"
#include "ParticleBlocks/ForceBlock.h"
#include "ParticleBlocks/GravityBlock.h"
#include "ParticleBlocks/RotationBlock.h"
#include "ParticleBlocks/ScaleBlock.h"
#include "ParticleBlocks/TextureFadeBlock.h"
#include "EffectBlock.h"

Data::Data()
	: effectPlayer(new ParticleManager()), previewWindow(new PreviewWindow(this))
{
	effectTimeline = nullptr;

	// Effect blocks
	_blockInfos[0] = new std::vector<BlockInfo>();  // The items are added dynamically each frame

	// Emitter blocks
	_blockInfos[1] = new std::vector<BlockInfo>();
	std::vector<Block*> temp;
	temp.push_back(new BoxVolumeBlock({ 0, 0 }));
	temp.push_back(new SpawnBlock({ 0, 0 }));
	temp.push_back(new TextureBlock({ 0, 0 }, "", -1));
	ImVec4 colors[] = { C(102, 255, 204), C(0, 204, 153), C(0, 153, 153) };
	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		_blockInfos[1]->push_back({ temp[i], temp[i]->visualName, temp[i]->desc, temp[i]->iconName, colors[i] });
	}
	temp.clear();

	// Particle blocks
	_blockInfos[2] = new std::vector<BlockInfo>();
	temp.push_back(new ColorBlock({ 0, 0 }, *this));
	temp.push_back(new ConstantForce({ 0, 0 }));
	temp.push_back(new ForceBlock({ 0, 0 }));
	temp.push_back(new GravityBlock({ 0, 0 }));
	temp.push_back(new RotationBlock({ 0, 0 }));
	temp.push_back(new ScaleBlock({ 0, 0 }));
	temp.push_back(new TextureFadeBlock({ 0, 0 }, -1));
	ImVec4 colors2[] = {
		C(102, 204, 255),
		C(0, 153, 255),
		C(51, 51, 255),
		C(102, 0, 255),
		C(51, 102, 204),
		C(153, 153, 255),
		C(204, 153, 255) };
	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		_blockInfos[2]->push_back({ temp[i], temp[i]->visualName, temp[i]->desc, temp[i]->iconName, colors2[i] });
	}
	temp.clear();
	
	_bgColors[0] = ImVec4(0, 0, 0.3f, 1);
	_bgColors[1] = ImVec4(0, 0.2f, 0.3f, 1);
	_bgColors[2] = ImVec4(0.1f, 0, 0.2f, 1);
}

Data::~Data()
{
	for (auto p : particleTimelines)
		delete p;
	for (auto e : emitterTimelines)
		delete e;

	delete effectTimeline;

	if (effectPlayer)
		delete effectPlayer;

	for (unsigned int i = 0; i < 3; ++i)
		delete _blockInfos[i];
}

int Data::getParticleCount()
{
	return particleTimelines.size();
}

int Data::getEmitterCount()
{
	return emitterTimelines.size();
}

int Data::getOpenCount()
{
	return openTimelines.size();
}

void Data::addParticleTimeline(Timeline* particleTimeline, int index)
{
	addTimeline(particleTimeline, index, particleTimelines, type::Particle);
}

void Data::addEmitterTimeline(Timeline* emitterTimeline, int index)
{
	addTimeline(emitterTimeline, index, emitterTimelines, type::Emitter);
}

void Data::setEffect(Timeline* effectTimeline)
{
	//Swap out old effect
	Timeline *old = this->effectTimeline;
	if (old)
		effectPlayer->stopEffect(old);
	// Run new
	this->effectTimeline = effectTimeline;
	effectPlayer->runEffect(effectTimeline);
	// Delete
	delete old;
}

void Data::removeParticleTimeline(int index)
{
	removeTimeline(index, particleTimelines);
}

void Data::removeEmitterTimeline(int index)
{
	removeTimeline(index, emitterTimelines);
}

std::list<Timeline*>& Data::getParticleTimelines()
{
	return particleTimelines;
}

std::list<Timeline*>& Data::getEmitterTimelines()
{
	return emitterTimelines;
}

Timeline* Data::getEffectTimeline()
{
	return effectTimeline;
}

ParticleManager *Data::getPlayer()
{
	return effectPlayer;
}

PreviewWindow *Data::getPreview()
{
	return previewWindow;
}

Timeline* Data::getOpenTimeline(int index)
{
	auto it = openTimelines.begin();
	for (int i = 0; i < index; ++i)
		++it;

	return *it;
}

Timeline* Data::getTimelineOfSelectedBlock(){
	for(int i = 0; i < openTimelines.size(); ++i){
		Timeline* currT = openTimelines.at(i);
		for(int j = 0; j < currT->_channel.size(); ++j){
			Channel* currC = currT->_channel.at(j);
			for(int k = 0; k < currC->_data.size(); ++k){
				Block* currB = currC->_data.at(k);

				if(currB == _selectedBlock){
					return currT;
				}
			}
		}
	}

	std::cout << "If you see this, the program will crash shortly" << std::endl;
	return nullptr;
}

void Data::openTimeline(Timeline* timeline)
{
	if (timeline == effectTimeline ||
		std::find(particleTimelines.begin(), particleTimelines.end(), timeline) != particleTimelines.end() ||
		std::find(emitterTimelines.begin(), emitterTimelines.end(), timeline) != emitterTimelines.end())
	{
		// Only open closed timelines
		if (std::find(openTimelines.begin(), openTimelines.end(), timeline) == openTimelines.end())
			openTimelines.push_back(timeline);
	}
}

void Data::closeTimeline(Timeline* timeline)
{
	auto it = std::find(openTimelines.begin(), openTimelines.end(), timeline);

	if (it != openTimelines.end())
	{
		openTimelines.erase(it);
	}
}

void Data::closeTimeline(int index)
{
	auto it = openTimelines.begin();
	for (int i = 0; i < index; ++i)
		++it;

	openTimelines.erase(it);
}

void Data::addTimeline(Timeline* timeline, int index, std::list<Timeline*>& list, type::Timeline type)
{
	if (timeline->_type != type)
	{
		std::cerr << "Tried to add the wrong type of timeline!\n";
		return;
	}

	if (index < 0)
		list.insert(list.end(), timeline);
	else
	{
		auto it = list.begin();
		for (int i = 0; i < index; ++i)
			++it;

		list.insert(it, timeline);
	}
}

void Data::removeTimeline(int index, std::list<Timeline*>& list)
{
	if (list.size() <= 0)
	{
		std::cerr << "Tried to remove timeline from an empty list!\n";
		return;
	}

	auto it = list.begin();
	for (int i = 0; i < index; ++i)
		++it;

	list.erase(it);
}
