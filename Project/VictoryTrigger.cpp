#include "VictoryTrigger.h"

VictoryTrigger::VictoryTrigger(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order)
	: CollisionObject(_name, texture_name, _position, _size, 0, _scale, offset, texture_size, false, false, _sorting_order, 0, true)
{}

void VictoryTrigger::update() {

}


void VictoryTrigger::onTrigger(CollisionObject * other) {

	if (is_active) {
		if (Player * player = dynamic_cast<Player*>(other)) {
			player->changeHealth(10000);
			is_active = false;
			if (createMenuVictory_ptr != nullptr && level != nullptr) {
				(*level.*createMenuVictory_ptr)();
			}
		}
	}
}

bool VictoryTrigger::isMoving() {
	return true;
}


void VictoryTrigger::setCreateMenuVictory(void(Level::*_createMenuVictory)()) {
	createMenuVictory_ptr = _createMenuVictory;
}