#ifndef _CONTRAGULATION_H_
#define _CONGRATULATION_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "TestStartPage.h"
using namespace cocos2d;

class Congratulation : public Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void showScore(float dt);
	void showSoul(float dt);

	void restart(Ref *sender);
	void mainmenu(Ref *sender);

};
#endif 
