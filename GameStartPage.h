#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	void menuItem1Callback(cocos2d::Ref * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

class GameStartPage : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createNewScene();

	virtual bool init();

	void menuItemCallback(Ref * pSender);
	
	    //here is keyboard scene code from game from scratch.com
        virtual void update(float delta) override;
    
        bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	CREATE_FUNC(GameStartPage);
private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> keys;
};
#endif // __HELLOWORLD_SCENE_H__
