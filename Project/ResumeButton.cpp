#include "ResumeButton.h"

ResumeButton::ResumeButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, MenuInGame & _menu_in_game)
	: Clickable(_name, _position, _size, texture_name, color, hover_color), menu_in_game(_menu_in_game)
{

}

void ResumeButton::onClick() {
	menu_in_game.unactiving();
}

void ResumeButton::start() {

	Clickable::setText("RESUME");
	text->active = false;

}

void ResumeButton::update() {
	text->active = active;
}