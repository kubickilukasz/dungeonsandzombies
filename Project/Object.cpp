#include "Object.h"

Object::Object(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation , VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order)
	: name(_name), rotation(_rotation), scale(_scale), flipX(_flipX), flipY(_flipY), sorting_order(_sorting_order) , texture(Singleton<AssetManager>::instance()->getTexture(texture_name))
{

	width = (int)texture.getSize().x;
	height = (int)texture.getSize().y;

	width = width <= 0 ? 1 : width;
	height = height <= 0 ? 1 : height;

	sprite.setTexture(texture);

	sprite.setOrigin(width / 2, height / 2);

	this->changePosition(_position.x, _position.y);
	this->changeRotation(rotation);
	this->changeSize(_size.x, _size.y);


}

Object::Object(const std::string _name,const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order)
	: Object(_name, texture_name , _position, _size,_rotation,_scale, _flipX , _flipY, _sorting_order)
{

	width = (int)texture_size.x;
	height = (int)texture_size.y;

	width = width <= 0 ? 1 : width;
	height = height <= 0 ? 1 : height;
	
	sprite.setTextureRect({ (int)offset.x, (int)offset.y , (int)texture_size.x , (int)texture_size.y});
	sprite.setOrigin(width / 2, height / 2);
	this->changeSize(_size.x, _size.y);


}

void Object::changePosition(const float x,const float y) {

	position.x = x;
	position.y = y;

}

void Object::changeRotation(const float rot) {

	rotation = rot;
	sprite.setRotation(rotation);

}

void Object::changeSize(const float x,const float y) {

	size.x = x;
	size.y = y;

	sprite.setScale(scale.x * (size.x / width) * (flipX ? -1 : 1), scale.y * (size.y / height) * (flipY ? -1 : 1));
}

void Object::changeScale(const float x,const float y) {

	scale.x = x;
	scale.y = y;

	this->changeSize(size.x , size.y);
}

void Object::changeFlipX(bool _flip) {

	if (flipX != _flip) {
		flipX = _flip;
		changeSize(size.x , size.y);
	}

}

void Object::changeFlipY(bool _flip) {

	if (flipY != _flip) {
		flipY = _flip;
		changeSize(size.x, size.y);
	}
}

void Object::setLevel(Level * _level) {
	level = _level;
}

void Object::setCreateFunction(void(Level::*_create)(std::shared_ptr<Object>)) {
	create_ptr = _create;
}

void Object::setRemoveFunction(void(Level::*_remove)(Object*)) {
	remove_ptr = _remove;
}

void Object::setCreateGUIFunction(void(Level::*_create)(std::shared_ptr<GUIElement>)) {
	create_gui_ptr = _create;
}

void Object::setRemoveGUIFunction(void(Level::*_remove)(GUIElement*)) {
	remove_gui_ptr = _remove;
}


bool Object::getFlipX() {
	return flipX;
}

bool Object::getFlipY() {
	return flipY;
}

int Object::getSortingOrder() {
	return sorting_order;
}

std::string Object::getName() {
	return name;
}

VectorFloat Object::getPosition() {
	return position;
}

sf::Sprite & Object::getSprite(){

	if(position.x != sprite.getPosition().x || position.y != sprite.getPosition().y)
		sprite.setPosition(position.x, position.y);

	if (current_animation.haveFrames()) {

		Frame & current_frame = current_animation.getFrame();

		int width = (int)current_frame.width;
		int height = (int)current_frame.height;

		sprite.setOrigin(width/2, height/2);

		sprite.setTextureRect({current_frame.posX , current_frame.posY , current_frame.width , current_frame.height});

	}

	return sprite;
}

void Object::start() {



}

void Object::update() {

	
	
}

void  Object::update_animation() {
	current_animation.update(Time::getElapsedTime());
}

void Object::playAnimation(const std::string _name) {

	if (current_animation.getName() != _name) {
		current_animation = Singleton<AssetManager>::instance()->getAnimation(_name);
	}
}

Object* Object::create(std::shared_ptr<Object> new_object) {

	if (level != nullptr && create_ptr != nullptr) {
		(*level.*create_ptr)(new_object);
	}

	return new_object.get();

}

void Object::remove(Object * object_to_remove) {

	if (level != nullptr && remove_ptr != nullptr) {
		(*level.*remove_ptr)(object_to_remove);
	}

}


GUIElement* Object::createGUI(std::shared_ptr<GUIElement> new_gui) {
	if (level != nullptr && create_gui_ptr != nullptr) {
		(*level.*create_gui_ptr)(new_gui);
	}

	return new_gui.get();
}

void Object::removeGUI(GUIElement * gui_element) {
	if (level != nullptr && remove_ptr != nullptr) {
		(*level.*remove_gui_ptr)(gui_element);
	}
}

