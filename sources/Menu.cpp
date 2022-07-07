#include "Menu.hpp"
#include "Simulator.hpp"

bool Menu::visible	= true;
bool Menu::active	= false;

void Menu::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Key::F1)
		visible = !visible;
}

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
	if (visible)
	{
		ImGui::Begin("Settings (F1 to hide)");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

		ImGui::NewLine();
		ImGui::Text("The resolution of the grid:");

		if (ImGui::SliderInt("##resolution", &Simulator::world_size.x, 100, 1000))
		{
			Simulator::world_size.y = std::floor((float)Simulator::world_size.x / (16.f / 9.f));
			Simulator::reset();
		}

		int nature = (int)Simulator::brush_type->nature - 1;

		if (nature == -1)
		{
			if (Simulator::brush_type->fire_level > 0)
				nature = Material::materials.size() - 1;
			else
				nature = Material::materials.size();
		}

		ImGui::NewLine();
		ImGui::Text("The type of the brush:");

		if (ImGui::Combo("##brush_type", &nature, "Wood\0Sand\0Water\0Oil\0Salt\0Ash\0Coal\0Stone\0Lava\0Vapor\0Ice\0Snow\0Acid\0Fire\0Eraser"))
		{
			if (nature == Material::materials.size() - 1)
			{
				Simulator::brush_type = Material::materials[0]->build();
				Simulator::brush_type->fire_level = Material::fire_max;
			}

			else if (nature == Material::materials.size())
				Simulator::brush_type = Material::materials[0]->build();

			else
				Simulator::brush_type = Material::materials[nature + 1]->build();
		}

		ImGui::NewLine();
		ImGui::Text("The size of the brush:");
		ImGui::SliderInt("##brush_size", &Simulator::brush_size, 1, 10);

		active = ImGui::IsWindowFocused();

		ImGui::End();
	}
}
