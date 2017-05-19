#pragma once
#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

class SettingPage :public cocos2d::Layer {
public:
	virtual bool init() override;
	static cocos2d::Scene* createNewScene();
	void goToStartPage(Ref* pSender);
	void menuSoundToggleCallback(Ref* pSender);

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExit() override;
	virtual void onExitTransitionDidStart() override;
	virtual void cleanup() override;
private:
	CREATE_FUNC(SettingPage);
};


#endif