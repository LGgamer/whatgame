#pragma once
#ifndef _WELCOME_H_
#define _WELCOME_H_
#include "cocos2d.h"
USING_NS_CC;

class Welcome : public cocos2d::Layer
{
public:
	static Scene* createWhatGameScene();

	virtual bool init() override;

	void turnDD(float dt);

	CREATE_FUNC(Welcome);
};

class DryDew : public cocos2d::Layer
{
public:
	static Scene* createDDScene();

	virtual bool init() override;

	void turnGame(float dt);

	CREATE_FUNC(DryDew);
};
#endif // !_WELCOME_H_

