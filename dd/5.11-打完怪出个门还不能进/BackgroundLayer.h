#pragma once
#ifndef _BACKGROUNDLAYER_H_
#define _BACKGROUNDLAYER_H_

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually

	CREATE_FUNC(BackgroundLayer);

};
#endif // !_BACKGROuNDLAYER_H_


