#include "UI.h"

#include "Previewer.h"
#include "Properties.h"
#include "SolutionExplorer.h"
#include "UITimelines.h"
#include "UIDivider.h"


UI::UI()
{
	//_containers.reserve(4);
	//_containers.push_back(new Previewer());
	//_containers.push_back(new Properties());
	//_containers.push_back(new SolutionExplorer());
	//_containers.push_back(new Timelines());

	_containers.push_back(
		new UIDivider(UIDivider::DivisionDirection::VERTICAL, 0.45f, 
			new UIDivider(UIDivider::DivisionDirection::HORIZONTAL, 0.6f, 
				new Previewer(),
				new UIDivider(UIDivider::DivisionDirection::VERTICAL, 0.3f,
					new SolutionExplorer(),
					new Properties())),
			new UITimelines())
	);
}


UI::~UI()
{
	for (auto& c : _containers)
		delete c;
}


void UI::draw(ImVec2 windowSize)
{
	for (auto& c : _containers)
		c->draw(ImVec2(0, 26), windowSize);
}
