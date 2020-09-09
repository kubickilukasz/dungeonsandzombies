#include "GUIElement.h"

GUIElement::GUIElement(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color)
	: name(_name), texture(Singleton<AssetManager>::instance()->getTexture(texture_name))
{
	
	shape = sf::RectangleShape({ (float)_size.x , (float)_size.y });
	shape.setTexture(&texture);
	shape.setPosition({(float)_position.x, (float)_position.y});

	width_screen = (float)SConfig::instance()->getInt("width");
	height_screen = (float)SConfig::instance()->getInt("height");

	start_size = _size;

}

void GUIElement::setTextureRect(VectorInt _offset, VectorInt _size) {
	shape.setTextureRect({_offset.x, _offset.y, _size.x , _size.y});
}

void GUIElement::setSize(VectorInt _size) {
	shape.setSize({ (float)_size.x , (float)_size.y });
}

void GUIElement::setColor(sf::Color _new_color) {
	shape.setFillColor(_new_color);
}

void GUIElement::start() {

}

void GUIElement::update() {

}

VectorInt GUIElement::getSizeTexture() {
	return VectorInt(texture.getSize().x , texture.getSize().y);
}

VectorInt GUIElement::getStartSize() {
	return start_size;
}

sf::Drawable & GUIElement::getRectangleShape() {
	return shape;
}

void GUIElement::setLevel(Level * _level) {
	level = _level;
}

void GUIElement::setCreateFunction(void(Level::*_create)(std::shared_ptr<Object>)) {
	create_ptr = _create;
}

void GUIElement::setRemoveFunction(void(Level::*_remove)(Object*)) {
	remove_ptr = _remove;
}

void GUIElement::setCreateGUIFunction(void(Level::*_create)(std::shared_ptr<GUIElement>)) {
	create_gui_ptr = _create;
}

void GUIElement::setRemoveGUIFunction(void(Level::*_remove)(GUIElement*)) {
	remove_gui_ptr = _remove;
}


Object* GUIElement::create(std::shared_ptr<Object> new_object) {

	if (level != nullptr && create_ptr != nullptr) {
		(*level.*create_ptr)(new_object);
	}

	return new_object.get();
}

void GUIElement::remove(Object * object_to_remove) {

	if (level != nullptr && remove_ptr != nullptr) {
		(*level.*remove_ptr)(object_to_remove);
	}

}

GUIElement* GUIElement::createGUI(std::shared_ptr<GUIElement> new_gui) {
	if (level != nullptr && create_gui_ptr != nullptr) {
		(*level.*create_gui_ptr)(new_gui);
	}

	return new_gui.get();
}

void GUIElement::removeGUI(GUIElement * gui_element) {
	if (level != nullptr && remove_ptr != nullptr) {
		(*level.*remove_gui_ptr)(gui_element);
	}
}

