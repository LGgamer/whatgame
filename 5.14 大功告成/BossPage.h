#pragma once
#ifndef _BOSSPAGE_H_
#define _BOSSPAGE_H_

#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class BossPage : public GameStartPage
{
public:

	int BossNum;

	static Scene* createBossScene();
	bool init();

	virtual void initMonster() override;

	virtual void nextScene(float dt) override;

	virtual void checkBullet() override;

	virtual void checkEnd() override;

	void delay(float dt);

	CREATE_FUNC(BossPage);
};

#endif // !_BOSSPAGE_H_
