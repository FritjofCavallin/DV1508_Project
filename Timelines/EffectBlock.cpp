#include "EffectBlock.h"
#include "misc/RandFunction.h"


EffectBlock::EffectBlock(Timeline *emitter, TimeInterval t)
	: Block(t), _emitter(emitter)
{
}


EffectBlock::~EffectBlock()
{
}