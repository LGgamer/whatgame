#pragma once
#ifndef _BACKGROUNDLAYER_H_
#define _BACKGROUNDLAYER_H_

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	
	CREATE_FUNC(BackgroundLayer);

};
#endif // !_BACKGROuNDLAYER_H_


