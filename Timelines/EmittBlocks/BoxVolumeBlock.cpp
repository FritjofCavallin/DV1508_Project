#include "BoxVolumeBlock.h"
#include "misc/RandFunction.h"


BoxVolumeBlock::BoxVolumeBlock()
{
}


BoxVolumeBlock::~BoxVolumeBlock()
{
}

void BoxVolumeBlock::applyEmitter(Particle &part, GPUParticle &gpuPart)
{
	gpuPart._position.x += randomFloat(-1, 1) * _volumeSize.x;
	gpuPart._position.y += randomFloat(-1, 1) * _volumeSize.y;
	gpuPart._position.z += randomFloat(-1, 1) * _volumeSize.z;
}