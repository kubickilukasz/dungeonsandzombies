#include "ChangeLevelButton.h"


ChangeLevelButton::ChangeLevelButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, GameManager & _game_manager, const int _id_level, std::string content)
	: Clickable(_name, _position, _size, texture_name, color, hover_color), game_manager(_game_manager) , id_level(_id_level), text_content(content)
{

}

void ChangeLevelButton::onClick() {
	game_manager.loadLevel(id_level);
	Time::time_scale = 1;
}

void ChangeLevelButton::start() {

	setText(text_content);

}

