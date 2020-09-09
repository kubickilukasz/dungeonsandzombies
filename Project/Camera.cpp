#include "Camera.h"


Camera::Camera() {

	float width = (float)SConfig::instance()->getInt("width");
	float height = (float)SConfig::instance()->getInt("height");

	view = sf::View({ 0,0,width, height });
	gui_view = sf::View({0,0,width, height});

	view.setViewport({ 0,0,1,1 });
	gui_view.setViewport({0,0,1,1});

	view.zoom(SConfig::instance()->getFloat("zoom"));
	//gui_view.zoom(SConfig::instance()->getFloat("zoom"));

}

void Camera::setPosition(VectorFloat _position) {

	view.setCenter({ _position.x, _position.y });
}

void Camera::setTarget(sf::RenderTarget & _target) {
	_target.setView(view);
}

void Camera::setTargetGUI(sf::RenderTarget & _target) {
	_target.setView(gui_view);
}

VectorFloat Camera::getPosition() {
	return VectorFloat(view.getCenter().x , view.getCenter().y);
}