#pragma once
#include <vector>
#include <list>

#include "Timeline.h"

class ParticleManager;
class PreviewWindow;

/* Database containing timelines in the project
*/
class Data
{
public:
	Data();
	~Data();

	int getParticleCount();
	int getEmitterCount();
	int getOpenCount();

	// Add a particle timeline. If index >= 0, insert at specified index and push existing timelines back. If index < 0, insert at end.
	void addParticleTimeline(Timeline* particleTimeline, int index = -1);
	// Add an emitter timeline. If index >= 0, insert at specified index and push existing timelines back. If index < 0, insert at end.
	void addEmitterTimeline(Timeline* emitterTimeline, int index = -1);
	// Deletes the current effect timeline and replaces it
	void setEffect(Timeline* effectTimeline);

	void removeParticleTimeline(int index);
	void removeEmitterTimeline(int index);

	std::list<Timeline*>& getParticleTimelines();
	std::list<Timeline*>& getEmitterTimelines();
	Timeline* getEffectTimeline();
	Timeline* getOpenTimeline(int index);
	ParticleManager *getPlayer();
	PreviewWindow *getPreview();

	// Adds a timeline to the open list. The timeline must be part of the database.
	void openTimeline(Timeline* timeline);
	// Removes a timeline from the open list
	void closeTimeline(Timeline* timeline);
	// Removes a timeline from the open list. Index refers to position in open list
	void closeTimeline(int index);

private:
	std::list<Timeline*> particleTimelines;
	std::list<Timeline*> emitterTimelines;
	Timeline* effectTimeline;

	// List of timelines open in the UI
	std::list<Timeline*> openTimelines;
	/* Effect player
	*/
	ParticleManager * effectPlayer;
	PreviewWindow *previewWindow;

	void addTimeline(Timeline* particleTimeline, int index, std::list<Timeline*>& list, type::Timeline type);
	void removeTimeline(int index, std::list<Timeline*>& list);

};