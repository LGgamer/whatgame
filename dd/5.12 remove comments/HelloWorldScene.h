#if 1
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class HelloWorld : public cocos2d::Layer//Color
{
public:
	cocos2d::Vec2 screenO;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	//virtual bool initWithColor();
	void setViewPointCenter(cocos2d::Point position);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void mydefine(Ref* who);
	void mydefine2(Ref *sender);
	bool isHold(cocos2d::EventKeyboard::KeyCode code);
	bool onTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	int hold;
    // implement the "static create()" method manually

    CREATE_FUNC(HelloWorld);

	static std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
	cocos2d::Sprite *_player;
};

#endif // __HELLOWORLD_SCENE_H__

#endif

