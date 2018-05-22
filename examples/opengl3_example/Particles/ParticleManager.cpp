#include "ParticleManager.h"
#include <iostream>
#include "../Timelines/EffectBlock.h"

ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{
	for (ParticleEffect *e : _effects)
		delete e;
}



void ParticleManager::update()
{
	for (ParticleEffect *e : _effects)
		e->update();
}


void ParticleManager::render(Camera *cam)
{
	for (ParticleEffect *e : _effects)
		e->render(cam);

}


void ParticleManager::printInfo()
{
	for (ParticleEffect *e : _effects)
		std::cout << e->getStatus();

}
void ParticleManager::deleteBlock(Block * b)
{
	EffectBlock * eB = dynamic_cast<EffectBlock*>(b);
	if (eB)
	{
		for (ParticleEffect *e : _effects)
			e->remove(eB);
	}
}


void ParticleManager::runEffect(Timeline *t)
{
	if (t->_type == type::Effect)
		_effects.push_back(new ParticleEffect(t));
}
void ParticleManager::stopEffect(Timeline *t)
{
	//Don't call during update!!!
	
	if (t->_type == type::Effect)
	{
		for (size_t i = 0; i < _effects.size(); i++)
		{
			if (_effects[i]->_timeline == t)
			{
				ParticleEffect *e = _effects[i];
				_effects.erase(_effects.begin() + i);
				delete e;
				return;
			}
		}
	}
}