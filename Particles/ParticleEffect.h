#pragma once

#include "Timelines/Timeline.h"
#include <map>


class Emission;

const float EMIT_STEP = 0.016f;
const float MAX_DURATION = 100.f;

/* Displayed particle effect constantly updated.
*/
class ParticleEffect
{
public:

	/* Effect timeline. */
	Timeline * _timeline;
	float _time, _loopTime;

	float elapsedSince(float t) { return _time < t ? _loopTime - t + _time : _time - t; }

	ParticleEffect();
	ParticleEffect(Timeline *timeline);
	~ParticleEffect();


	void update();

private:



	void incrementTime(float step);
	std::map<Timeline*, Emission*> _emitters;
};

