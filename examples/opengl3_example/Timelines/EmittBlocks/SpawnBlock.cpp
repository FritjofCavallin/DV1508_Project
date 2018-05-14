#include "SpawnBlock.h"


InitialEmissionParams::InitialEmissionParams() :
	_initAmount(1), _endAmount(1),
	_minSize(0.4f, 0.4f),	_maxSize(0.5f, 0.5f),
	_emitOrigin(0.f), _emitDir(0,1.f,0),
	_minRotation(0), _maxRotation(3.14*2),
	_minForce(1.f), _maxForce(2.f)
{
}


SpawnBlock::SpawnBlock(TimeInterval t)
	: Block(t, type::Emitter), _params()
{
}

SpawnBlock::SpawnBlock(TimeInterval t, InitialEmissionParams &p) 
	: Block(t, type::Emitter), _params(p)
{
}

SpawnBlock::~SpawnBlock()
{
}
