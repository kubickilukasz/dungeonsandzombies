#include "ExitButton.h"

ExitButton::ExitButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, GameManager & _game_manager)
	: Clickable(_name, _position, _size, texture_name, color, hover_color), game_manager(_game_manager)
{

}

void ExitButton::onClick() {
	game_manager.endGame();
	Time::time_scale = 1;
}

void ExitButton::start() {

	setText("EXIT");
	text->active = true;

}
