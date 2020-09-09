#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <algorithm> // find

#include "Player.h"
#include "Zombie.h"
#include "Magus.h"
#include "Mixture.h"
#include "VictoryTrigger.h"
#include "Vector.h"
#include "Singleton.h"
#include "Config.h"
#include "Vector.h"
#include "Time.h"
#include "Logger.h"
#include "Camera.h"
#include "Wall.h"
#include "Clickable.h"
#include "MenuInGame.h"
#include "ChangeLevelButton.h"
#include "ExitButton.h"
#include "GameManager.h"
#include "MenuDeath.h"
#include "MenuVictory.h"
#include "Text.h"


#ifndef LEVEL
#define LEVEL

typedef std::shared_ptr<Object> Object_ptr;
typedef std::list<Object_ptr> object_list;
typedef std::vector<std::vector<std::list<CollisionObject*>>> collision_object_ptrs;
typedef std::list<std::shared_ptr<GUIElement>> gui_elements_list;

class GameManager;

class Level {

private:

	const int id_level = 0;

	const std::string name = "default";

	object_list objects;
	gui_elements_list gui_elements;

	object_list::iterator iterator_objects;

	sf::View view;

	collision_object_ptrs collision_objects;

	VectorInt max_collision_width;
	VectorInt max_collision_height;
	const int square_collision;

	GameManager & game_manager;

	array_position_collision getPositionsCollision(CollisionObject * object);

	void deletePositionsCollision(CollisionObject * object);


public:

	Level() = delete;

	Level(const int & id_level,const std::string name, GameManager & _game_manager);

	~Level();

	int getId();

	void load();

	void deleteObjects();

	void deleteGUIElements();

	void clear();

	void createObject(std::shared_ptr<Object> new_object);

	void removeObject(Object * object_to_remove);

	void createGUI(std::shared_ptr<GUIElement> gui_element);

	void removeGUI(GUIElement * gui_element);

	void createMenuDeath();

	void createMenuVictory();

	void createFloor(VectorFloat left_up_corner, VectorFloat right_down_corner);

	void draw(sf::RenderWindow & window);

};

#endif