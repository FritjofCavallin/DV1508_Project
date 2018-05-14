#pragma once

#include "../Timelines/Timeline.h"
#include <map>
#include "Constants.h"
#include <string>
#include "../Other/GLFuncs.h"

class Emission;

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
	void render();
	
	std::string getStatus();

private:

	GLuint _partShaderProgram;

	void incrementTime(float step);
	std::map<Timeline*, Emission*> _emitters;
};

