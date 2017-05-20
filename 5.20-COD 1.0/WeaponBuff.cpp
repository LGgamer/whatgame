//this is basically a collection of weapons

#include "WeaponBuff.h"

weaponBuff::weaponBuff() :Sprite() {
	extra_attack = 10;

}

weaponBuff::~weaponBuff() {

}

weaponBuff* weaponBuff::create(const std::string& filename) {
	weaponBuff *sprite = new (std::nothrow) weaponBuff();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

int weaponBuff::get_extra_Attack() {
	return extra_attack;
}

void weaponBuff::effect(character* & maincharacter) {
	maincharacter->attack_up(EXTRA_POINTS);
}
weapon1::weapon1() {
	EXTRA_ATTACK = 100;
}

weapon1::~weapon1() {

}

void  weapon1::effect(character* & maincharacter) {
	maincharacter->attack_up(EXTRA_ATTACK);
}

weapon2::weapon2() {
	EXTRA_SPEED = 100;
}

weapon2::~weapon2() {

}
void weapon2::effect(character* & maincharacter) {
	maincharacter->speed_up(EXTRA_SPEED);
}

weapon3::weapon3() {}

weapon3::~weapon3() {}

void weapon3::effect(character* & maincharacter) {
	maincharacter->attackM = 2;
}

