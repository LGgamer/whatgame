#pragma once
#ifndef _WEAPONBUFF_H_
#define _WEAPONBUFF _H _
#include "cocos2d.h"
USING_NS_CC;

class weaponBuff:public cocos2d::Sprite
{
public:
	static weaponBuff* create(const std::string& filename);
	weaponBuff();
	~weaponBuff();
	int get_extra_Attack();

private:
	int extra_attack;
};



#endif
