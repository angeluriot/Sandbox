#ifndef MENU_HPP
#define MENU_HPP

#include "libraries.hpp"

/**
 * @brief The window to edit the settings of the Simulator::
 */
class Menu
{
public:

	static bool active; // True if you clicked on the menu, false otherwise.

	/**
	 * @brief Show the title of a part of the menu.
	 *
	 * @param text the title text
	 */
	static void title(const std::string& text);

	/**
	 * @brief Show centered buttons
	 *
	 * @param texts the text of the buttons
	 * @param buttons_height the height of the buttons
	 * @param spaces_size the size of the space between the buttons
	 * @return an array of booleans that are true if the corresponding button was clicked
	 */
	static std::vector<bool> centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size);

	/**
	 * @brief Show the settings.
	 */
	static void display();
};

#endif
