#include "simulation.h"
#include "button.h"
#include <iostream>

Simulation simulation;

int main()
{
	// Initialisation de la fenêtre en fonction de l'écran

	int width;
	int height;

	if (sf::VideoMode::getDesktopMode().width > (16. / 9.) * sf::VideoMode::getDesktopMode().height)
	{
		height = (sf::VideoMode::getDesktopMode().height * 3) / 4;
		width = (height * 16) / 9;
	}

	else if (sf::VideoMode::getDesktopMode().width < (16. / 9.) * sf::VideoMode::getDesktopMode().height)
	{
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4;
		height = (width * 9) / 16;
	}

	else
	{
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4;
		height = (sf::VideoMode::getDesktopMode().height * 3) / 4;
	}

	screen_width = width;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Sandbox", sf::Style::Close | sf::Style::Titlebar, settings);

	sf::Image icon;
	icon.loadFromFile("dependencies/resources/icon.png");

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Initialisation du menu

	std::vector<Variable> variables;
	variables.push_back(Variable("Taille des pixels", Int, 5, 1, 20));
	variables.push_back(Variable("FPS (0 = pas de limite)", Int, 0, 0, 1000));
	
	Menu menu = Menu(variables, sf::Color(20, 20, 200), width, height);
	menu.init_names(50, 750, sf::Color::White, 350);
	menu.init_lines(700, 15, 1200, sf::Color(75, 75, 255));
	menu.init_circles(20, sf::Color::White);
	menu.init_values(40, 50, sf::Color::White);
	menu.init_boxes(45, 600, sf::Color::White);
	menu.init_start(150, 1920 - 150, 1080 - 150, sf::Color::White);

	Restart restart_button = Restart(150, 1920 - 150, 1080 - 150, sf::Color::White, width, height);

	bool simulation_end = false;
	bool end = false;

	Cursor_type cursor_type = arrow;
	Cursor_type temp = cursor_type;
	sf::Vector2i mouse_position;
	sf::Vector2i previous_mouse_position;
	int whell_move = 0;

	sf::Mouse mouse;
	sf::Keyboard keyboard;
	sf::Cursor cursor;
	sf::Event sf_event;
	sf::Clock clock;
	sf::Clock clock_2;

	clock.restart();
	clock_2.restart();

	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	Button_list button_list;

	// lancement du menu

	while (window.isOpen() and !end)
	{
		while (!menu.end and !end)
		{
			while (window.pollEvent(sf_event))
			{
				switch (sf_event.type)
				{

				case sf::Event::Closed:

					window.close();
					end = true;
					break;
				}
			}

			previous_mouse_position = mouse_position;
			mouse_position = mouse.getPosition(window);

			menu.update(previous_mouse_position, mouse_position, mouse.isButtonPressed(mouse.Left), cursor, cursor_type, window);
			menu.draw(window);
		}

		cursor.loadFromSystem(sf::Cursor::Wait);
		window.setMouseCursor(cursor);

		menu.end = false;
		menu.grabbed = false;
		menu.grab_forbiden = false;

		simulation.restart(menu);
		button_list.init();

		if (restart_button.is_in(sf::Vector2f(mouse_position)))
			cursor.loadFromSystem(sf::Cursor::Hand);

		else
			cursor.loadFromSystem(sf::Cursor::Arrow);

		window.setMouseCursor(cursor);

		// lancement de la simulation

		while (!simulation_end and !end)
		{
			while (window.pollEvent(sf_event))
			{
				switch (sf_event.type)
				{

				case sf::Event::Closed:

					window.close();
					end = true;
					break;

				case sf::Event::MouseWheelMoved:

					whell_move += sf_event.mouseWheel.delta;
					break;
			
				}
			}

			// pour limiter le nombre de fps
			
			if (menu.variables[1].int_value != 0)
			{
				if (clock.getElapsedTime() >= sf::seconds(1. / (double)menu.variables[1].int_value))
				{
					clock.restart();
					simulation.update(mouse.isButtonPressed(sf::Mouse::Left), sf::Vector2i(mouse_position.x - (SIZE_BUTTON + 2. * DISTANCE_BUTTON_X), mouse_position.y));
				}
			}

			else
			{
				clock.restart();
				simulation.update(mouse.isButtonPressed(sf::Mouse::Left), sf::Vector2i(mouse_position.x - (SIZE_BUTTON + 2. * DISTANCE_BUTTON_X), mouse_position.y));
			}

			previous_mouse_position = mouse_position;
			mouse_position = mouse.getPosition(window);

			// Affichage et boutons

			if (clock_2.getElapsedTime().asMilliseconds() > 10)
			{
				window.clear(sf::Color::Black);

				temp = cursor_type;
				cursor_type = arrow;

				button_list.update(mouse_position, mouse.isButtonPressed(mouse.Left), cursor, cursor_type, window, whell_move, simulation.brush);
				whell_move = 0;
				simulation_end = restart_button.update(mouse_position, mouse.isButtonPressed(mouse.Left), cursor, cursor_type, window);

				button_list.draw(window);
				simulation.draw(window);
				restart_button.draw(window);

				window.display();

				clock_2.restart();

				if (temp != cursor_type)
				{
					if (cursor_type == arrow)
						cursor.loadFromSystem(sf::Cursor::Arrow);

					if (cursor_type == hand)
						cursor.loadFromSystem(sf::Cursor::Hand);

					window.setMouseCursor(cursor);
				}
			}
		}

		simulation_end = false;
		restart_button.grabbed = false;
		restart_button.grab_forbiden = false;
	}

	return 0;
}