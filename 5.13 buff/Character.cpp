#include "Character.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

character::character() {

	live = true;

	basic_health = 100;
	level = 1;
	gold = 0;
	basic_attack = 10;
	basic_defence = 5;
	basic_speed = 100;
	attack_coefficient = defence_coefficient = speed_coefficient = health_coefficient = gold_coefficient = 1.0;
}

character* character::create(const std::string& filename)
{
	character *sprite = new (std::nothrow) character();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

character::~character() {

}

int character::get_max_health() {
	return level * health_coefficient * 100;
}

int character::get_current_health() {
	return basic_health;
}

int character::get_attack() {
	return level * attack_coefficient * basic_attack;
	// related with strength
}

int character::get_defence() {
	return level * defence_coefficient * basic_defence;
}

int character::get_strength() {
	return level * strength_coefficient * basic_strength;
}

int character::get_agility() {
	return level * agility_coefficient * basic_agility;
}

int character::get_speed() {
	return level * speed_coefficient * basic_speed;
}

int character::get_experience() {
	return experience;
}

int character::get_gold() {
	return gold;
}

void character::HpDown(int point) {
	if (basic_health >= point) {
		basic_health = basic_health - point;
	}
	else {
		basic_health = 0;
		live = false;
	}
}

bool character::stillalive() {
	if (live == true) {
		return true;
	}
	else {
		return false;
	}
}
void character::attack_up(int points) {
	basic_attack = basic_attack + points;
}

void character::speed_up(int points) {
	basic_speed = basic_speed + points;
}