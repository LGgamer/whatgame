#pragma once
#ifndef _WEAPONBUFF_H_
#define _WEAPONBUFF _H _
#include "cocos2d.h"
#include "character.h"
USING_NS_CC;

class weaponBuff :public cocos2d::Sprite

{
public:
	const int EXTRA_POINTS = 10;
public:
	static weaponBuff* create(const std::string& filename);
	weaponBuff();
	~weaponBuff();
	int get_extra_Attack();
	virtual void effect(character* & maincharacter);

private:
	int extra_attack;
};

class weapon1 :public weaponBuff {
public:
	weapon1();
	~weapon1();
	int EXTRA_ATTACK = 100;
	virtual void effect(character* & maincharacter);
};

class weapon2 :public weaponBuff {
public:
	weapon2();
	~weapon2();
	int EXTRA_SPEED = 100;
	virtual void effect(character* & maincharacter);
};

class weapon3 :public weaponBuff {
public:
	weapon3();
	~weapon3();
	virtual void effect(character* & maincharacter);
};


#endif
