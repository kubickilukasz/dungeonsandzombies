#include "Mixture.h"

Mixture::Mixture(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const int _health, const int _damage)
	: CollisionObject(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, false, false, _sorting_order, 0, true), health(_health), damage(_damage)
{
	sprite.setOrigin({(float)width/2, (float)height});;
}

void Mixture::update() {

	if (to_delete) {
		remove(this);
	}else {
		if (is_player_near) {
			playAnimation("mixture_mark");
		}
		else {
			playAnimation("mixture_idle");
		}
		is_player_near = false;
	}
}


void Mixture::onTrigger(CollisionObject * other) {

	if (!to_delete) {
		if (Player * player = dynamic_cast<Player*>(other)) {

			is_player_near = true;		

			if (SInputManager::instance()->getE()) {
				player->changeHealth(player->getMaxHealth());
				player->updateHealthBar();
				to_delete = true;
			}
			else if (SInputManager::instance()->getQ()) {
				int prev_max_health = player->getMaxHealth();

				player->changeMaxHealth(prev_max_health + health);
				player->changeHealth((int)(player->getHealth()/(float)prev_max_health * player->getMaxHealth()));
				player->changeDamage(player->getDamage() + damage);
				player->updateHealthBar();
				to_delete = true;
			}
		}
	}else {
		playAnimation("mixture_idle");
	}
}

bool Mixture::isMoving() {
	return true;
}