#pragma once
#include "GUIElement.h"
#include "Text.h"

#ifndef BUTTON
#define BUTTON

class Clickable : public GUIElement{

	sf::Color basic_color;
	sf::Color hover_color;

protected:

	

public:
	
	Text * text;
	bool is_clickable = true;

	Clickable(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color);

	void click();

	virtual void onClick() = 0;

	void setHover(bool is_hover);

	void setText(std::string content);

	void setColor(sf::Color _new_color);

	bool isMouseInButton(VectorFloat position_mouse);

};

#endif

