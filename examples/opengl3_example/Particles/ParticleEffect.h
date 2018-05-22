#pragma once

#include "../Timelines/Timeline.h"
#include <map>
#include "../Other/Constants.h"
#include <string>
#include "../Other/GLFuncs.h"
#include "ParticleShader.h"
#include "../camera.h"

class Emission;
class EffectBlock;

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
	void render(Camera *cam);
	
	std::string getStatus();

	Emission* getEmission(EffectBlock *block);

	void remove(EffectBlock *eblock);
	
private:

	ParticleShader _shader;


	void incrementTime(float step);
	std::map<EffectBlock*, Emission*> _emitters;
};

