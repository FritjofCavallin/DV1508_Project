#include "TestParticles.h"
#include "Timelines/EmittBlocks/SpawnBlock.h"
#include "Timelines/EffectBlock.h"
#include "Timelines/ParticleBlocks/ScaleBlock.h"

Timeline *simpleEffect()
{
	TimeInterval time(0, 3);

	// Create an particle
	Timeline *p = new Timeline(type::Particle, "P0", time);
	ScaleBlock *scale = new ScaleBlock(time);
	scale->_scaleBegin = glm::vec2(0.1f, 0.1f);
	scale->_scaleEnd = glm::vec2(2.f, 2.f);
	p->addBlock(scale, 0);


	// Create an emitter
	Timeline *e = new Timeline(type::Emitter, "E0", time);
	e->addBlock(new SpawnBlock(TimeInterval(0, 2)), 0);
	e->_particleLink = p; //Set particle

	// Create effect timeline
	Timeline *t = new Timeline(type::Effect, "Effect", time);
	t->addBlock(new EffectBlock(e, time), 0);

	return t;
}

/* Test case when no particle is linked to emitter
*/
Timeline *noParticle()
{
	TimeInterval time(0, 3);
	
	// Create an emitter
	Timeline *e = new Timeline(type::Emitter, "E0", time);
	e->addBlock(new SpawnBlock(time), 0);

	// Create effect timeline
	Timeline *t = new Timeline(type::Effect, "Effect", time);
	t->addBlock(new EffectBlock(e, time), 0);

	return t;
}