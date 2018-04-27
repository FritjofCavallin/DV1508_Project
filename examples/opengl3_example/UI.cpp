#include "UI.h"

#include "Previewer.h"
#include "Properties.h"
#include "SolutionExplorer.h"
#include "Timelines.h"
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
			new Timelines())
	);
}


UI::~UI()
{
	for (auto& c : _containers)
		delete c;
}


void UI::draw(ImVec2 windowSize)
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("main"))
	{
		ImGui::MenuItem("blah", nullptr, nullptr);
		ImGui::MenuItem("bleh", nullptr, nullptr);
		ImGui::MenuItem("dfsdg", nullptr, nullptr);
		if (ImGui::BeginMenu("menu"))
		{
			ImGui::MenuItem("1", nullptr, nullptr);
			ImGui::MenuItem("2", nullptr, nullptr);
			ImGui::MenuItem("3", nullptr, nullptr);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("menu"))
	{
		ImGui::MenuItem("123", nullptr, nullptr);
		ImGui::MenuItem("456", nullptr, nullptr);
		ImGui::MenuItem("789", nullptr, nullptr);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("bar"))
	{
		ImGui::MenuItem("abc", nullptr, nullptr);
		ImGui::MenuItem("defghijk", nullptr, nullptr);
		ImGui::MenuItem("lmnopqrstuvwxyz", nullptr, nullptr);
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	for (auto& c : _containers)
		c->draw(ImVec2(0, 18), windowSize);
}
