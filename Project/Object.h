#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "Vector.h"
#include "Animation.h"
#include "Logger.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Time.h"
#include "GUIElement.h"



#ifndef OBJECT
#define OBJECT

class Level;

typedef std::unordered_map<std::string, Animation> animations_type;

class Object {

	bool flipX;
	bool flipY;

	void (Level::*create_ptr)(std::shared_ptr<Object>);
	void (Level::*remove_ptr)(Object *);
	void (Level::*create_gui_ptr)(std::shared_ptr<GUIElement>);
	void (Level::*remove_gui_ptr)(GUIElement *);

protected:

	Level * level;

	const std::string name;

	int width;
	int height;

	VectorFloat position;
	float rotation;
	VectorFloat size;
	VectorFloat scale;

	int sorting_order = 0;

	sf::Texture & texture;
	sf::Sprite sprite;

	Animation current_animation;

public: 

	Object(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, const bool _flipX, const bool _flipY, const int _sorting_order);

	Object(const std::string _name, const std::string texture_name, VectorFloat _position , VectorFloat _size , const float _rotation, VectorFloat _scale, VectorInt offset , VectorInt texture_size, const bool _flipX, const bool _flipY, const int _sorting_order);

	void changePosition(const float x, const  float y);
	void changeRotation(float rot);

	void changeSize(const float x, const float y);
	void changeScale(const float x, const float y);

	void changeFlipX(bool _flip);
	void changeFlipY(bool _flip);

	void setLevel(Level * _level);

	void setCreateFunction(void(Level::*_create)(std::shared_ptr<Object>));
	void setRemoveFunction(void(Level::*_remove)(Object*));

	void setCreateGUIFunction(void(Level::*_create)(std::shared_ptr<GUIElement>));
	void setRemoveGUIFunction(void(Level::*_remove)(GUIElement*));

	bool getFlipX();
	bool getFlipY();

	int getSortingOrder();

	std::string getName();

	VectorFloat getPosition();

	sf::Sprite & getSprite();

	virtual void start();
	virtual void update();
	void update_animation();

	void playAnimation(const std::string _name);

	Object* create(std::shared_ptr<Object> new_object);
	void remove(Object *);

	GUIElement* createGUI(std::shared_ptr<GUIElement> new_gui);
	void removeGUI(GUIElement * gui_element);

};

#endif