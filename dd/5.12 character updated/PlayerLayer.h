#ifndef _PLAYERLAYER_H_
#define _PLAYERLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class PlayerLayer : public Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

//	void keyEvent(float delta);
//	//here is keyboard scene code from game from scratch.com
//	virtual void update(float delta) override;
//
//	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
//	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
//
//	
//private:
//	static std::map<cocos2d::EventKeyboard::KeyCode,
//		std::chrono::high_resolution_clock::time_point> keys;
//	cocos2d::Label * label;

	CREATE_FUNC(PlayerLayer);
};

#endif