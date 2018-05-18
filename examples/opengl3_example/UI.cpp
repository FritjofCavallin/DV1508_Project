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
	if (ImGui::BeginMenu("Colors"))
	{
		ImGui::Text("CONFIGURE COLORS");
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Text("***** Effect *****");
		ImGui::Separator();
		ImGui::Text("Blocks");
		int count = 1;
		for (auto& e : data->getEmitterTimelines())
		{
			ImVec4 color = ImVec4(1, 70 * count / 255.f, 0, 1);
			ImGui::ColorEdit3(e->_name.c_str(), (float*)&color);
			++count;
		}
		ImGui::Text("Background");
		ImGui::ColorEdit3("##0", (float*)&data->_bgColors[0]);
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Text("***** Emitters *****");
		ImGui::Separator();
		ImGui::Text("Blocks");
		for (unsigned int j = 0; j < data->_blockInfos[1]->size(); ++j)
		{
			std::string name = data->_blockInfos[1]->at(j)._name;
			for (int i = name.length() - 1; i >= 0; --i)
			{
				if (name[i] == ' ')
					name.erase(i, 1);
				else if (name[i] == '\n')
				{
					name.erase(i, 1);
					name.insert(name.begin() + i, ' ');
				}
			}
			ImGui::ColorEdit3(name.c_str(), (float*)&data->_blockInfos[1]->at(j)._color);
		}
		ImGui::Text("Background");
		ImGui::ColorEdit3("##1", (float*)&data->_bgColors[1]);
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Text("***** Particles *****");
		ImGui::Separator();
		ImGui::Text("Blocks");
		for (unsigned int j = 0; j < data->_blockInfos[2]->size(); ++j)
		{
			std::string name = data->_blockInfos[2]->at(j)._name;
			for (int i = name.length() - 1; i >= 0; --i)
			{
				if (name[i] == ' ')
					name.erase(i, 1);
				else if (name[i] == '\n')
				{
					name.erase(i, 1);
					name.insert(name.begin() + i, ' ');
				}
			}
			ImGui::ColorEdit3(name.c_str(), (float*)&data->_blockInfos[2]->at(j)._color);
		}
		ImGui::Text("Background");
		ImGui::ColorEdit3("##2", (float*)&data->_bgColors[2]);
		ImGui::Separator();
		ImGui::Separator();

		ImGui::EndMenu();
	}
	
	ImGui::EndMainMenuBar();

	for (auto& c : _containers)
		c->draw(ImVec2(0, 18), ImVec2(windowSize.x, windowSize.y - 18));
}
