#include "TestParticles.h"
#include "../Timelines/Data.h"
#include "glm/geometric.hpp"
#include "../Timelines/EmittBlocks/SpawnBlock.h"
#include "../Timelines/EmittBlocks/BoxVolumeBlock.h"
#include "../Timelines/EmittBlocks/TextureBlock.h"
#include "../Timelines/EffectBlock.h"
#include "../Timelines/ParticleBlocks/ScaleBlock.h"
#include "../Timelines/ParticleBlocks/ColorBlock.h"
#include "../Timelines/ParticleBlocks/RotationBlock.h"
#include "../Timelines/ParticleBlocks/ForceBlock.h"
#include "../Timelines/ParticleBlocks/ConstantForce.h"
#include "../Timelines/ParticleBlocks/GravityBlock.h"
#include "../Timelines/ParticleBlocks/TextureFadeBlock.h"

void simpleEffect(Data &data)
{
	TimeInterval time(0, 3);

	// Create an particle
	Timeline *p = new Timeline(type::Particle, "Particle0", time);
	ScaleBlock *scale = new ScaleBlock(time);
	scale->_scaleBegin = glm::vec2(0.2f, 0.2f);
	scale->_scaleEnd = glm::vec2(1.f, 1.f);
	p->addBlock(scale, 0);

	ColorBlock *color = new ColorBlock(time);
	color->_colorBegin = glm::vec4(0.f, 0, 0, 1);
	color->_colorEnd = glm::vec4(1.f, 0.f, 0.5f, 0.5f);
	p->addBlock(color, 1);

	RotationBlock * rot = new RotationBlock(time);
	p->addBlock(rot, 2);
	ConstantForce *gravity = new ConstantForce(time);
	p->addBlock(gravity, 3);

	// Create an emitter
	Timeline *e = new Timeline(type::Emitter, "Emitter0", time);
	InitialEmissionParams sParam;
	sParam._emitDir = glm::normalize(glm::vec3(-1, 1, 0));
	sParam._emitOrigin = glm::vec3(2, 0.1f, 0);
	sParam._minForce = 9.f;
	sParam._maxForce = 15.f;
	sParam._minSize = glm::vec2(0.1, 0.2f);
	sParam._maxSize = glm::vec2(0.3, 0.33f);
	e->addBlock(new SpawnBlock(TimeInterval(0, 2), sParam), 0);
	e->_particleLink = p; //Set particle


	BoxVolumeBlock *spread = new BoxVolumeBlock(time);
	spread->_volumeSize = glm::vec3(0.5f, 0.1f, 0.5f);
	e->addBlock(spread, 1);


	/* Create second particle emitter
	*/

	Timeline *p2 = new Timeline(type::Particle, "Particle1", time);
	scale = new ScaleBlock(time);
	scale->_scaleBegin = glm::vec2(1.f, 1.f);
	scale->_scaleEnd = glm::vec2(0.1f, 0.1f);
	p2->addBlock(scale, 0);
	rot = new RotationBlock(time);
	rot->_angVelocityBegin = PI * 2.f;
	rot->_angVelocityEnd = PI *16.f;
	p2->addBlock(rot, 1);

	ForceBlock *f1 = new ForceBlock(TimeInterval(0.4f, 0.6f), glm::vec3(1.f,0,0), 5.f);
	ForceBlock *f2 = new ForceBlock(TimeInterval(1.f, 1.2f), glm::vec3(-1.f, 0, 0), 5.f);
	p2->addBlock(f1, 2);
	p2->addBlock(f2, 2);

	TextureFadeBlock *texFade = new TextureFadeBlock(time, 0);
	p2->addBlock(texFade, 3);

	Timeline *e2 = new Timeline(type::Emitter, "Emitter1", time);
	sParam._initAmount = 5;
	sParam._endAmount = 5;
	sParam._minForce = 1.f;
	sParam._maxForce = 2.f;
	sParam._emitDir = glm::normalize(glm::vec3(0, 1, 0.1f));
	sParam._emitOrigin = glm::vec3(0, 0.1f, 0);
	sParam._minSize = glm::vec2(0.6f, 1.2f);
	sParam._maxSize = glm::vec2(0.6f, 1.2f);
	e2->addBlock(new SpawnBlock(time, sParam), 0);

	spread = new BoxVolumeBlock(time);
	spread->_volumeSize = glm::vec3(0.5f, 0.1f, 0.5f);
	e2->addBlock(spread, 1);

	TextureBlock *tex = new TextureBlock(time, "Content/Effect.png", 0);
	e2->addBlock(tex, 2);
	e2->_particleLink = p2; //Set particle




	// Create effect timeline
	Timeline *t = new Timeline(type::Effect, "Effect", time);
	t->addBlock(new EffectBlock(e, time), 0);
	t->addBlock(new EffectBlock(e2, time), 1);

	data.addParticleTimeline(p);
	data.addParticleTimeline(p2);
	data.addEmitterTimeline(e);
	data.addEmitterTimeline(e2);
	data.setEffect(t);
	data.openTimeline(p);
	data.openTimeline(e);
	data.openTimeline(p2);
	data.openTimeline(e2);
	data.openTimeline(t);

}

/* Test case when no particle is linked to emitter
*/
void noParticle(Data &data)
{
	TimeInterval time(0, 3);
	
	// Create an emitter
	Timeline *e = new Timeline(type::Emitter, "E0", time);
	e->addBlock(new SpawnBlock(time), 0);

	// Create effect timeline
	Timeline *t = new Timeline(type::Effect, "Effect", time);
	t->addBlock(new EffectBlock(e, time), 0);

}



void oldTest(Data &data)
{

	// Add test data
	Timeline* ptm = new Timeline(type::Particle, "Cool Particle Timeline", TimeInterval(0.0f, 5.0f));
	ptm->addBlock(new ForceBlock(TimeInterval(0.1f, 1.099f)), 0);
	ptm->addBlock(new ForceBlock(TimeInterval(1.1f, 1.9f)), 0);
	ptm->addBlock(new ForceBlock(TimeInterval(2.0f, 3.5f)), 0);
	ptm->addBlock(new ForceBlock(TimeInterval(3.61f, 5.0f)), 0);
	Timeline* ptm2 = new Timeline(type::Particle, "Cool Particle Timeline 2", TimeInterval(0.0f, 5.0f));
	ptm2->addBlock(new ForceBlock(TimeInterval(1.0f, 3.5f)), 0);
	Timeline* ptm3 = new Timeline(type::Particle, "Cool Particle Timeline 3", TimeInterval(0.0f, 5.0f));
	ptm3->addBlock(new ForceBlock(TimeInterval(1.0f, 3.5f)), 0);
	Timeline* mtm = new Timeline(type::Emitter, "My Emitter Timeline", TimeInterval(0.0f, 5.0f));
	mtm->addBlock(new BoxVolumeBlock(TimeInterval(1.0f, 3.5f)), 0);
	Timeline* ftm = new Timeline(type::Effect, "Effect Timeline", TimeInterval(0.0f, 5.0f));
	data.addParticleTimeline(ptm);
	data.addParticleTimeline(ptm2);
	data.addParticleTimeline(ptm3);
	data.addEmitterTimeline(mtm);
	data.setEffect(ftm);

	data.openTimeline(ptm);
	data.openTimeline(ptm2);
	data.openTimeline(ptm3);
	data.openTimeline(mtm);
	data.openTimeline(ftm);
}