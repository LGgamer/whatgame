#include "Welcome.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* Welcome::createWhatGameScene()
{
	auto scene = Scene::create();

	auto layer = Welcome::create();

	scene->addChild(layer);

	return scene;
}

bool Welcome::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto wg = Sprite::create("whatgame.png");
	wg->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	this->addChild(wg);
	wg->runAction(jump);

	scheduleOnce(schedule_selector(Welcome::turnDD), 1);

	return true;
}

void Welcome::turnDD(float dt)
{
	auto dd = DryDew::createDDScene();
	//auto tran = TransitionFade::create(2, DryDew::createDDScene());
	
	Director::getInstance()->replaceScene(dd);
	//Director::getInstance()->popScene();
}



Scene* DryDew::createDDScene()
{
	auto scene = Scene::create();

	auto layer = DryDew::create();

	scene->addChild(layer);

	return scene;
}

bool DryDew::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto dd = Sprite::create("drydew.png");
	dd->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	//auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	this->addChild(dd);
	//wg->runAction(jump);

	scheduleOnce(schedule_selector(DryDew::turnGame), 2);

	return true;
}

void DryDew::turnGame(float dt)
{
	//auto t = HelloWorld::createScene();
	auto t = TransitionFade::create(2, HelloWorld::createScene());
	Director::getInstance()->pushScene(t);
}
