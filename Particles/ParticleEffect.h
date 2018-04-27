#pragma once

#include "Timelines/Timeline.h"

/* Displayed particle effect constantly updated.
*/
class ParticleEffect
{
public:

	/* Effect timeline. */
	Timeline * _timeline;
	float _time;

	ParticleEffect(Timeline *timeline);
	~ParticleEffect();


	void update();

private:


	void applyEffectTimeline();
};

