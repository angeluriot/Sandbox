#include <dim/dimension3D.hpp>
#include "Simulator.hpp"
#include "Menu.hpp"

int main()
{
	dim::Window::open("Sandbox", 0.75f, "resources/icons/icon.png");
	dim::Window::get_window().setFramerateLimit(144);
	dim::Scene::add("Simulation");
	Simulator::init();

	while (dim::Window::running)
	{
		// Check the events.
		sf::Event sf_event;
		while (dim::Window::poll_event(sf_event))
		{
			dim::Window::check_events(sf_event);
			dim::Scene::check_all_events(sf_event);
		}

		dim::Window::clear(dim::Color::black);
		dim::Window::update();

		dim::Scene::clear_all();
		dim::Scene::update_all();

		Simulator::inputs();
		Simulator::update();
		Simulator::draw();

		Menu::display();
		dim::Scene::display_all();
		dim::Window::display();
	}

	return EXIT_SUCCESS;
}
