#include "SpawnBlock.h"


InitialEmissionParams::InitialEmissionParams() :
	_initAmount(5), _endAmount(5),
	_minForce(5), _maxForce(5),
	_minRotation(0), _maxRotation(3.14*2),
	_minSize(1, 1),	_maxSize(1.5f, 1.5f)
{
}


SpawnBlock::SpawnBlock(TimeInterval t)
	: Block(t), _params()
{
}

SpawnBlock::SpawnBlock(TimeInterval t, InitialEmissionParams &p)
	: Block(t), _params(p)
{
}

SpawnBlock::~SpawnBlock()
{
}
