#include "EffectBlock.h"
#include "../Other/RandFunction.h"


EffectBlock::EffectBlock(Timeline *emitter, TimeInterval t)
	: Block(t, type::Effect), _emitter(emitter)
{
	visualName = emitter->_name;
}


EffectBlock::~EffectBlock()
{
}