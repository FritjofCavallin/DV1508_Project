#pragma once
#include "../Block.h"

/* Spawn block parameters
*/
struct InitialEmissionParams
{
	float _initAmount, _endAmount;
	glm::vec2 _minSize, _maxSize;
	float _minRotation, _maxRotation;
	float _minForce, _maxForce;
};

class SpawnBlock :
	public Block
{
public:

	InitialEmissionParams _params;

	SpawnBlock();
	virtual ~SpawnBlock();


	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() { return type::Emitter; }
};

