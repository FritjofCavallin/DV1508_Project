#include "TestParticles.h"
#include "Timelines/EmittBlocks/SpawnBlock.h"


Timeline *simpleEffect()
{
	Timeline *t = new Timeline(type::Effect);


	t->addBlock(new SpawnBlock(), 0);

	return t;
}