#include "ParticleManager.h"



ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{
}



void ParticleManager::update()
{

}



void ParticleManager::runEffect(Timeline *t)
{
	if (t->_type == Timeline::Effect)
		_effects.push_back(new ParticleEffect(t));
}
void ParticleManager::stopEffect(Timeline *t)
{
	if (t->_type == Timeline::Effect)
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