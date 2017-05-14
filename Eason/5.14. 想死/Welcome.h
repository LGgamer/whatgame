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

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExit() override;
	virtual void onExitTransitionDidStart() override;
	virtual void cleanup() override;
};

class DryDew : public cocos2d::Layer
{
public:
	static Scene* createDDScene();

	virtual bool init() override;

	void turnGame();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {};

	CREATE_FUNC(DryDew);

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExit() override;
	virtual void onExitTransitionDidStart() override;
	virtual void cleanup() override;
};
#endif // !_WELCOME_H_

