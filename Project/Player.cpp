#include "Player.h"


Player::Player(const std::string _name, const std::string texture_name, VectorFloat _position, VectorFloat _size, const float _rotation, VectorFloat _scale, VectorInt offset, VectorInt texture_size, const int _sorting_order, const float _speed)
	: Character(_name, texture_name, _position, _size, _rotation, _scale, offset, texture_size, false, false, _sorting_order, _speed , false , 60 , 60 , 5)
{
	size_collider.x = size.x / 3;
	size_collider.y = size.y / 5;
	offset_collider.y += size.y / 2.5;

}

void Player::start(){

	Object * object = create(std::shared_ptr<Object>(new AttackDirectionObject("attack_direction", "attack_direction", position + offset_collider, { size.x , size.y }, 0, { scale.x/2 , scale.y }, false, false, getSortingOrder() - 1, getSpeed() , this)));
	attack_direction = dynamic_cast<AttackDirectionObject *>(object);

	int screen_width = SConfig::instance()->getInt("width");
	int width_bar = (int)(screen_width * 0.5);
	int pos_bar_x = screen_width/ 2 - width_bar/2;

	health_bar_back = createGUI(std::shared_ptr<GUIElement>(new GUIElement("back_bar", { pos_bar_x,10 }, { width_bar,width_bar/6 }, "back_health_bar", sf::Color(255, 255, 255, 255))));
	health_bar = createGUI(std::shared_ptr<GUIElement>(new GUIElement("back_bar", { pos_bar_x,10 }, { width_bar,width_bar/6 }, "fill_health_bar", sf::Color(255, 255, 255, 255))));
	lock_attack = SInputManager::instance()->getMouseLeft();

}
void Player::setCreateMenuDeath(void(Level::*_createMenuDeath)()) {
	createMenuDeath_ptr = _createMenuDeath;
}

void Player::createMenuDeath() {
	if (level != nullptr && createMenuDeath_ptr != nullptr) {
		(*level.*createMenuDeath_ptr)();
	}
}


void Player::update() {

	VectorFloat _direction = SInputManager::instance()->getKeyboardAxis().Normalize();
	attack_direction->changePosition((position.x + offset_collider.x), position.y + offset_collider.y - 6);

	if (!is_dead) {
		if (!is_attack) {

			if (_direction.length() != 0) {
				playAnimation("hero_run");
			}else {
				playAnimation("hero_idle");
			}

			is_attack = SInputManager::instance()->getMouseLeft() && Time::time_scale != 0;
			if (!is_attack) {
				lock_attack = false;
			}else if (lock_attack) {
				is_attack = false;
			}

			if (is_attack) {

				current_direction_attack = attack_direction->getDirection();
				current_direction_attack = current_direction_attack * 0.7;

				if (getFlipX() && current_direction_attack.x > 0) {
					changeFlipX(false);
				}
				else if (!getFlipX() && current_direction_attack.x < 0) {
					changeFlipX(true);
				}
			}else {
				if (getFlipX() && _direction.x > 0) {
					changeFlipX(false);
				}
				else if (!getFlipX() && _direction.x < 0) {
					changeFlipX(true);
				}
			}
		}else {

			playAnimation("hero_attack");
			_direction = current_direction_attack;
			if (current_animation.getIndexFrame() >= 3) {
				// attack
				is_hitting = true;
				if (current_animation.getIndexFrame() >= 6) {
					is_attack = false;
					is_hitting = false;
				}
			}
		}

		this->changeDirection(_direction);
		SCamera::instance()->setPosition(position);
		hit_timer += Time::getElapsedTime();

		if (hit_timer <= hit_time) {
			hit_timer += Time::getElapsedTime();
		}
		else {
			sprite.setColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void Player::onCollision(std::vector<CollisionObject*> others) {


}

void Player::onHit(Character * hitter) {
	if (!is_dead) {
		updateHealthBar();
		hit_timer = 0;
		sprite.setColor(sf::Color(255, 125, 125, 255));
	}
}

void Player::updateHealthBar() {
	if (!is_dead) {
		float real_width = (health / (float)max_health);
		health_bar->setTextureRect({ 0,0 }, { (int)ceil(real_width * (health_bar->getSizeTexture().x)) , health_bar->getSizeTexture().y });
		health_bar->setSize({ (int)ceil(real_width * (health_bar->getStartSize().x)) , health_bar->getStartSize().y });
	}
}

void Player::onDeath() {
	
	playAnimation("hero_death");
	removeGUI(health_bar);
	removeGUI(health_bar_back);
	remove(attack_direction);
	sprite.setColor(sf::Color(255, 255, 255, 255));
	changeDirection(VectorFloat());
	createMenuDeath();
}

bool Player::isAttack() {
	return is_attack;
}

bool Player::isHitting() {
	return is_hitting;
}

VectorFloat Player::getCurrentDirectionAttack() {
	return current_direction_attack;
}