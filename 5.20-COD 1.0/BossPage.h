#pragma once
#ifndef _BOSSPAGE_H_
#define _BOSSPAGE_H_

#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "ui\UILoadingBar.h"
#include "RandomList.h"
#include "Monster.h"
#include "WeaponBuff.h"
#include "BossPage.h"
#include "Congratulation.h"
#include "AppDelegate.h"
USING_NS_CC;


class BossPage : public GameStartPage
{
public:

	int BossNum;

	static Scene* createBossScene();
	
	bool isEffect = UserDefault::getInstance()->getBoolForKey("isEffect");

	bool init();

	virtual void initMonster() override;

	virtual void nextScene(float dt) override;

	virtual void checkBullet() override;

	virtual void checkEnd() override;

	void delay(float dt);
	

	CREATE_FUNC(BossPage);
};

#endif // !_BOSSPAGE_H_
