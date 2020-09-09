#include "Text.h"

Text::Text(const std::string name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, std::string content)
	: GUIElement(name, _position, _size, texture_name, color)
{

	text = sf::Text(content, Singleton<AssetManager>::instance()->getFont() , _size.x);
	text.setFillColor(color);
	text.setPosition({(float)_position.x, (float)_position.y});

}

sf::Drawable & Text::getRectangleShape() {
	return text;
}

sf::Text & Text::getText(){
	return text;
}

void Text::setColor(sf::Color _new_color) {
	text.setFillColor(_new_color);
}