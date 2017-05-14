#ifndef _LEVEL_UP_H_
#define _LEVEL_UP_H_
#include "cocos2d.h"
#include "TestStartPage.h"
//#include "HelloWorldScene.h"
using namespace cocos2d;

class LevelUp : public Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void restart(Ref *sender);

	void maxHpUp(Ref *sender);
	void speedUp(Ref *sender);
	bool soulisEnough;

	CREATE_FUNC(LevelUp);


};

#endif