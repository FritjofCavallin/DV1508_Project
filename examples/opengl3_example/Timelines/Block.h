#pragma once
#include <string>

#include "TimelineType.h"
#include "../Particles/Particle.h"
#include "TimeInterval.h"
#include "imgui.h"

/* Block in the timeline that affects a certain param in the effect. 
*/
class Block
{
public:

	Block(TimeInterval t, type::Timeline type);
	virtual ~Block();

	/* Time interval in absolute values related to parented timelines. */
	TimeInterval _time;
	type::Timeline _type;

	// Returns true if the time intervals of the two blocks overlap.
	bool overlaps(Block* other);

	// Returns true if the time interval of this contains the time interval of other.
	bool contains(Block* other);

	/* The timeline type the block is associated with
	*/
	type::Timeline typeFit() { return _type; };

	virtual void applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart) {};
	virtual void applyEmitter(Particle &part, GPUParticle &gpuPart) {};

	//should be pure virtual
	virtual void DrawProperties(ImVec2 pos, ImVec2 size){};
	void DrawPropertiesHeader(ImVec2 pos, ImVec2 size);

	// Used by UI
	bool draggingLeft = false;
	bool draggingRight = false;
	float dragHandleStart = 0.0f;
	float dragBodyStart = 0.0f;
	float dragBodyYOffset = 0.0f;
	std::string visualName = "CHANGE THIS!";
	std::string desc = "CHANGE THIS!";
	std::string iconName = "testicon.png";
};

