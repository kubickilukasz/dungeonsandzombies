#pragma once
#include "Vector.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>

#ifndef INPUTMANAGER
#define INPUTMANAGER

class InputManager{

	float mouse_x;
	float mouse_y;

	sf::RenderWindow * relativeWindow;

	bool blocked_escape = false;

public:

	InputManager();

	VectorFloat getMousePosition();

	bool getMouseLeft();

	bool getQ();
	bool getE();

	VectorFloat getMouseAxis();

	VectorFloat getKeyboardAxis();

	bool getEscape();

	void blockEscape(const bool _blocked);

	void setRelativeWindow(sf::RenderWindow & _realtiveWindow);


};

typedef Singleton<InputManager> SInputManager;

#endif // !INPUTMANAGER