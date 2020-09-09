#include "Clickable.h"

Clickable::Clickable(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color )
	: GUIElement(name, _position, _size, texture_name, color) , basic_color(color) , hover_color(hover_color)
{

}

void Clickable::click() {
	onClick();
}


void Clickable::setHover(const bool is_hover) {
	if (is_hover) {
		shape.setFillColor(hover_color);
	}else {
		shape.setFillColor(basic_color);
	}
}

void Clickable::setText(std::string _content) {

	text = dynamic_cast<Text*>(createGUI(std::shared_ptr<GUIElement>(new Text(name + "_text", {0, 0}, { 20, 0 }, "button", sf::Color(255, 255, 255, 255), _content))));
	float width = text->getText().findCharacterPos(_content.size() - 1).x - text->getText().findCharacterPos(0).x;
	float height = text->getText().getGlobalBounds().height;
	text->getText().setPosition({ (float)(shape.getPosition().x + (shape.getGlobalBounds().width - width) / 2), (float)(shape.getPosition().y + shape.getGlobalBounds().height/2) });
}

void Clickable::setColor(sf::Color _new_color) {
	basic_color = _new_color;
	shape.setFillColor(basic_color);
}

bool Clickable::isMouseInButton(VectorFloat position_mouse) {

	return position_mouse.x >= (shape.getPosition().x) && position_mouse.x <= (shape.getPosition().x + shape.getSize().x) &&
		position_mouse.y >= (shape.getPosition().y) && position_mouse.y <= (shape.getPosition().y + shape.getSize().y);
}
