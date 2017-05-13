#include "WeaponBuff.h"

weaponBuff::weaponBuff() :Sprite(){
	extra_attack = 10;
}

weaponBuff::~weaponBuff(){
	
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