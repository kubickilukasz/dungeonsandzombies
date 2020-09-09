#include "MenuDeath.h"


MenuDeath::MenuDeath(std::string _name, GameManager * _game_manager)
	: GUIElement(_name, { 0,0 }, { 0,0 }, "_none", sf::Color(255, 255, 255, 255)), game_manager(_game_manager)
{}

void MenuDeath::start() {

	float mn_x = width_screen / 1920.0;
	float mn_y = height_screen / 1080.0;

	VectorInt _position = VectorInt(width_screen / 2 - 425 * mn_x, -20);

	background = createGUI(std::shared_ptr<GUIElement>(new GUIElement("_back_menu", _position, { (int)(850 * mn_x), height_screen }, "back_menu", sf::Color(255, 255, 255, 0))));

	_position.y += 250 * mn_y;
	_position.x += 250 * mn_x;

	menu_game_text = dynamic_cast<Text*>(createGUI(std::shared_ptr<GUIElement>(new Text("_back_menu_title", _position, { (int)(24 * mn_x), 0 }, "back_menu", sf::Color(255, 255, 255, 255), "YOU ARE DEAD"))));

	_position.y += 100 * mn_y;
	_position.x -= 50 * mn_x;

	try_again = dynamic_cast<ChangeLevelButton*>(createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_menu", _position, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button"
		, sf::Color(255, 255, 255, 0), sf::Color(120, 120, 120, 255), *game_manager, 1, "TRY AGAIN"))));
	try_again->is_clickable = false;
	try_again->text->setColor(sf::Color(255,255,255,0));


	_position.y += 160 * mn_y;

	button_exit = dynamic_cast<ChangeLevelButton*>(createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_menu", _position, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button"
		, sf::Color(255, 255, 255, 0), sf::Color(120, 120, 120, 255), *game_manager, 0, "BACK TO MENU"))));
	button_exit->is_clickable = false;
	button_exit->text->setColor(sf::Color(255, 255, 255, 0));

	SInputManager::instance()->blockEscape(true);

}

void MenuDeath::update() {

	if (timer < time_to_show) {

		if (timer >= time_to_end_death) {

			Time::time_scale = 0;

			int alpha = ((timer - time_to_end_death) / (time_to_show - time_to_end_death)) * 255;
			if (alpha > 255) {
				alpha = 255;
			}

			sf::Color new_color(255, 255, 255, alpha);

			background->setColor(new_color);
			try_again->setColor(new_color);
			try_again->text->setColor(new_color);
			button_exit->setColor(new_color);
			button_exit->text->setColor(new_color);

		}else {
			background->setColor(sf::Color(255, 255, 255, 0));
		}
		timer += Time::getUnscaledElapsedTime();

	}else {

		try_again->is_clickable = true;
		button_exit->is_clickable = true;
		sf::Color new_color(255, 255, 255, 255);
		background->setColor(new_color);
		try_again->setColor(new_color);
		try_again->text->setColor(new_color);
		button_exit->setColor(new_color);
		button_exit->text->setColor(new_color);

	}

	

}



