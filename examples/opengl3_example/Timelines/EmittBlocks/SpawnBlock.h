#pragma once
#include "../Block.h"

/* Spawn block parameters
*/
struct InitialEmissionParams
{
	InitialEmissionParams();

	float _initAmount, _endAmount;
	glm::vec2 _minSize, _maxSize;
	glm::vec3 _emitOrigin, _emitDir; //Normalized direction!
	float _minRotation, _maxRotation;
	float _minForce, _maxForce;
};

class SpawnBlock :
	public Block
{
public:

	type::Timeline _type;
	InitialEmissionParams _params;


	SpawnBlock(TimeInterval t);
	SpawnBlock(TimeInterval t, InitialEmissionParams &p);
	virtual ~SpawnBlock();
};

