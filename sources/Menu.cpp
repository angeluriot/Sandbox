#include "Menu.hpp"
#include "Simulator.hpp"
#include "materials/Air.hpp"
#include "materials/Stone.hpp"
#include "materials/Sand.hpp"
#include "materials/Water.hpp"
#include "materials/Salt.hpp"
#include "materials/Wood.hpp"
#include "materials/Coal.hpp"
#include "materials/Oil.hpp"
#include "materials/Gas.hpp"
#include "materials/Lava.hpp"
#include "materials/Ice.hpp"
#include "materials/Snow.hpp"
#include "materials/Acid.hpp"

bool Menu::active = false;

void Menu::title(const std::string& text)
{
	float window_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.data()).x;

	ImGui::NewLine();
	ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
	ImGui::Text(text.data());
	ImGui::Separator();
}

std::vector<bool> Menu::centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size)
{
	float window_width = ImGui::GetWindowSize().x;
	float buttons_widths = (window_width - ((texts.size() + 2) * spaces_size)) / texts.size();
	std::vector<bool> result(texts.size());

	ImGui::NewLine();
	ImGui::NewLine();

	for (int i = 0; i < texts.size(); i++)
	{
		ImGui::SameLine();
		ImGui::SetCursorPosX(spaces_size + buttons_widths * i + spaces_size * i);
		ImGui::Text("");
		ImGui::SameLine();
		result[i] = ImGui::Button(texts[i].data(), ImVec2(buttons_widths, buttons_height));
	}

	return result;
}

void Menu::display()
{
	ImGui::Begin("Settings");
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

	ImGui::NewLine();
	ImGui::Text("The resolution of the grid:");

	if (ImGui::SliderInt("##resolution", &Simulator::world_size.x, 50, 500))
		Simulator::reset();

	static int selected = 0;

	ImGui::NewLine();
	ImGui::Text("The type of the brush:");

	if (ImGui::Combo("##brush_type", &selected, "Stone\0Sand\0Water\0Salt\0Wood\0Coal\0Oil\0Gas\0Fire\0Lava\0Ice\0Snow\0Acid\0Eraser"))
	{
		switch (selected)
		{
			case 0: Simulator::brush_type = new Stone(); break;
			case 1: Simulator::brush_type = new Sand(); break;
			case 2: Simulator::brush_type = new Water(); break;
			case 3: Simulator::brush_type = new Salt(); break;
			case 4: Simulator::brush_type = new Wood(); break;
			case 5: Simulator::brush_type = new Coal(); break;
			case 6: Simulator::brush_type = new Oil(); break;
			case 7: Simulator::brush_type = new Gas(); break;
			case 8:
				Simulator::brush_type = new Air();
				Simulator::brush_type->fire_level = Material::fire_max;
				break;
			case 9: Simulator::brush_type = new Lava(); break;
			case 10: Simulator::brush_type = new Ice(); break;
			case 11: Simulator::brush_type = new Snow(); break;
			case 12: Simulator::brush_type = new Acid(); break;
			case 13:
				Simulator::brush_type = new Air();
				break;
		}
	}

	ImGui::NewLine();
	ImGui::Text("The size of the brush:");
	ImGui::SliderInt("##brush_size", &Simulator::brush_size, 1, 20);

	ImGui::NewLine();
	ImGui::Text("Clear the grid:");

	if (ImGui::Button("Clear", ImVec2(ImGui::GetWindowSize().x * 0.9f, 0.f)))
		Simulator::reset();

	active = ImGui::IsWindowFocused();

	ImGui::End();
}
