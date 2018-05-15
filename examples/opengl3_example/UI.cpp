#include "UI.h"

#include "Previewer.h"
#include "Properties.h"
#include "SolutionExplorer.h"
#include "UITimelines.h"
#include "UIDivider.h"


UI::UI(Data* data)
{
	this->data = data;

	_containers.push_back(
		new UIDivider(UIDivider::DivisionDirection::VERTICAL, 0.45f, data,
			new UIDivider(UIDivider::DivisionDirection::HORIZONTAL, 0.6f, data,
				new Previewer(data),
				new UIDivider(UIDivider::DivisionDirection::VERTICAL, 0.3f, data,
					new SolutionExplorer(data),
					new Properties(data))),
			new UITimelines(data))
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
		c->draw(ImVec2(0, 18), ImVec2(windowSize.x, windowSize.y - 18));
}
