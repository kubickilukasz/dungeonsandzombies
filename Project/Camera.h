#pragma once
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Singleton.h"
#include "Vector.h"

#ifndef CAMERA
#define CAMERA

class Camera
{
	sf::View view;

	sf::View gui_view;

public:

	Camera();

	void setPosition(VectorFloat _position);

	void setTarget(sf::RenderTarget & _target);

	void setTargetGUI(sf::RenderTarget & _target);

	VectorFloat getPosition();

};

typedef Singleton<Camera> SCamera;

#endif

