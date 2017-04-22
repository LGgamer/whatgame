#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	void menuItem1Callback(cocos2d::Ref * pSender);
	void menuItem2Callback(cocos2d::Ref * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};


class GameStartPage : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createNewScene();

	virtual bool init();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void menuItemCallback(Ref * pSender);

	CREATE_FUNC(GameStartPage);

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
};

class OptionPage : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createNewScene();

	virtual bool init();
	
	void menuItemCallback(Ref * pSender);

	CREATE_FUNC(OptionPage);
};
/*
class StartGame : public cocos2d::LayerColor
{
pubilc:
	static cocos2d::Scene* createNewScene();

	virtual bool init();

	void menuItemCallback(Ref * pSender);

	CREATE_FUNC(StartGame);
};
*/



#endif // __HELLOWORLD_SCENE_H__
