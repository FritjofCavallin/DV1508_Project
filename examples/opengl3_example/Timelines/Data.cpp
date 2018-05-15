#include <iostream>

#include "Data.h"
#include "../Test/TestParticles.h"
#include "../Particles/ParticleManager.h"
#include "../Window/PreviewWindow.h"

Data::Data()
	: effectPlayer(new ParticleManager()), previewWindow(new PreviewWindow(this))
{
	effectTimeline = nullptr;

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
