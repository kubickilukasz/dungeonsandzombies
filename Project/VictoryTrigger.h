#pragma once
#include "CollisionObject.h"
#include "Player.h"

#ifndef VICTORYTRIGGER
#define VICTORYTRIGGER

class VictoryTrigger :public CollisionObject {


	void(Level::*createMenuVictory_ptr)();

	bool is_active = true;


public:

	VictoryTrigger(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order);

	void update();

	void onTrigger(CollisionObject * other);

	bool isMoving();

	void setCreateMenuVictory(void(Level::*_createMenuVictory)());


};

#endif // !VICTORYTRIGGER
