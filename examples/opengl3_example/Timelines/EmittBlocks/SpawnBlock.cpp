#include "SpawnBlock.h"


InitialEmissionParams::InitialEmissionParams() :
	_initAmount(1), _endAmount(20),
	_minSize(0.4f, 0.4f),	_maxSize(0.5f, 0.5f),
	_emitOrigin(0.f), _emitDir(0,1.f,0),
	_minRotation(0), _maxRotation(3.14f*2),
	_minForce(0.5f), _maxForce(2.f)
{
}


SpawnBlock::SpawnBlock(TimeInterval t)
	: Block(t, type::Emitter), _params()
{
	visualName = "Amount";
	desc = "The amount of particles to spawn";
}

SpawnBlock::SpawnBlock(TimeInterval t, InitialEmissionParams &p) 
	: Block(t, type::Emitter), _params(p)
{
	visualName = "Amount";
	desc = "The amount of particles to spawn";
}

SpawnBlock::~SpawnBlock()
{
}
