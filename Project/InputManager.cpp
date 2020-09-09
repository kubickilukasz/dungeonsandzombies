#include "InputManager.h"

InputManager::InputManager() {
	mouse_x = sf::Mouse::getPosition().x;
	mouse_y = sf::Mouse::getPosition().y;
}

VectorFloat InputManager::getMousePosition() {

	float x;
	float y;

	if (relativeWindow == nullptr) {
		x = sf::Mouse::getPosition().x;
		y = sf::Mouse::getPosition().y;
	}else {
		x = sf::Mouse::getPosition(*relativeWindow).x;
		y = sf::Mouse::getPosition(*relativeWindow).y;
	}

	return VectorFloat(x,y);

}


bool InputManager::getMouseLeft() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InputManager::getQ() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

bool InputManager::getE() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::E);
}

VectorFloat InputManager::getMouseAxis() {

	float x = sf::Mouse::getPosition().x - mouse_x;
	float y = sf::Mouse::getPosition().y - mouse_y;

	mouse_x = sf::Mouse::getPosition().x;
	mouse_y = sf::Mouse::getPosition().y;

	return VectorFloat(x, y);

}

VectorFloat InputManager::getKeyboardAxis() {

	int x = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ? -1 : 0;
	x = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ? x < 0 ? 0 : 1 : x;

	int y = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ? -1 : 0;
	y = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ? y < 0 ? 0 : 1 : y;

	return VectorFloat(x, y);

}

bool InputManager::getEscape() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !blocked_escape;
}
void InputManager::blockEscape(const bool _blocked) {
	blocked_escape = _blocked;
}


void InputManager::setRelativeWindow(sf::RenderWindow & _realtiveWindow) {
	relativeWindow = &_realtiveWindow;
}