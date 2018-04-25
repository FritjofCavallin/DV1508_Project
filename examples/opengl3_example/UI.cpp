#include "UI.h"

#include "Previewer.h"
#include "Properties.h"
#include "SolutionExplorer.h"


UI::UI()
{
	_containers.reserve(4);
	_containers.push_back(new Previewer());
	_containers.push_back(new Properties());
	_containers.push_back(new SolutionExplorer());
}


UI::~UI()
{
	for (auto& c : _containers)
		delete c;
}


void UI::draw()
{
	for (auto& c : _containers)
		c->draw();
}
