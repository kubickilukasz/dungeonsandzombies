#pragma once
#include "GUIElement.h"

#ifndef TEXT
#define TEXT

class Text :public GUIElement{

protected:

	sf::Text text;

public:

	Text(const std::string name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, std::string content);

	sf::Drawable & getRectangleShape();

	sf::Text & getText();

	void setColor(sf::Color _new_color);

};

#endif

