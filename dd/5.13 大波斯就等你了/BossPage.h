#pragma once
#ifndef _BOSSPAGE_H_
#define _BOSSPAGE_H_

#include "TestStartPage.h"
USING_NS_CC;

class BossPage : public GameStartPage
{
public:
	static Scene* createBossScene();
	bool init();

	virtual void initMonster() override;

	virtual void nextScene(float dt) override;

	CREATE_FUNC(BossPage);
};

#endif // !_BOSSPAGE_H_
