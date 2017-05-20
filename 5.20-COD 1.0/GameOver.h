#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "cocos2d.h"
#include "TestStartPage.h"
#include "HelloWorldScene.h"
#include "LevelUp.h"
using namespace cocos2d;

class GameOver : public Layer
{
public :

	static cocos2d::Scene* createScene();

	virtual bool init();

	void showScore(float dt);
	void showSoul(float dt);

	void restart(Ref *sender);
	void mainmenu(Ref *sender);

	CREATE_FUNC(GameOver);

};

#endif
