#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "AssetManager.h"
#include "InputManager.h"
#include "Vector.h"

#ifndef GUIELEMENT
#define GUIELEMENT

class Level;
class Object;

class GUIElement{

	void (Level::*create_ptr)(std::shared_ptr<Object>);
	void (Level::*remove_ptr)(Object *);
	void (Level::*create_gui_ptr)(std::shared_ptr<GUIElement>);
	void (Level::*remove_gui_ptr)(GUIElement *);

	Level * level;

protected:

	std::string name;
	sf::RectangleShape shape;
	sf::Texture & texture;

	VectorInt start_size;

	int width_screen;
	int height_screen;

public:

	bool active = true;

	GUIElement() = delete;
	GUIElement(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color);

	void setTextureRect(VectorInt _offset, VectorInt _size);

	void setSize(VectorInt _size);

	void setColor(sf::Color _new_color);

	virtual void start();
	virtual void update();

	VectorInt getSizeTexture();

	VectorInt getStartSize();

	virtual sf::Drawable & getRectangleShape();

	void setLevel(Level * _level);

	void setCreateFunction(void(Level::*_create)(std::shared_ptr<Object>));
	void setRemoveFunction(void(Level::*_remove)(Object*));

	void setCreateGUIFunction(void(Level::*_create)(std::shared_ptr<GUIElement>));
	void setRemoveGUIFunction(void(Level::*_remove)(GUIElement*));

	Object* create(std::shared_ptr<Object> new_object);
	void remove(Object *);

	GUIElement* createGUI(std::shared_ptr<GUIElement> new_gui);
	void removeGUI(GUIElement * gui_element);

};

#endif

