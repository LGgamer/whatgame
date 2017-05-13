#pragma once
#ifndef _HUDLAYER_H_
#define _HUDLAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class HUDLayer : public Layer
{
public:

	virtual bool init();

	void addToMiniMap(Node* sprite, Vec2 screenO, std::string fileName);
	void clearMiniMap();

	CREATE_FUNC(HUDLayer);
};

#endif // !_HUDLAYER_H_

