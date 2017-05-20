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
	auto dd = TransitionFade::create(2.0f, DryDew::createDDScene());
	
	Director::getInstance()->replaceScene(dd);
}

void Welcome::onEnter()
{
	Layer::onEnter();
}
void Welcome::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void Welcome::onExit()
{
	Layer::onExit();
}
void Welcome::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}
void Welcome::cleanup()
{
	Layer::cleanup();
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
	
	auto background = Sprite::create("blackbackground.png");
	background->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(background, -1);

	auto dd = Sprite::create("drydew.png");
	dd->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2 + 150));
	this->addChild(dd);

	//press any key to continue
	auto pak = Sprite::create("PAKTC.png");
	pak->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2 - 150));
	auto blink = Blink::create(4, 3);
	auto r = RepeatForever::create(blink);
	this->addChild(pak);
	pak->runAction(r);

	auto kblistener = EventListenerKeyboard::create();
	kblistener->onKeyPressed = CC_CALLBACK_2(DryDew::onKeyPressed, this);
	kblistener->onKeyReleased = CC_CALLBACK_2(DryDew::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(kblistener, this);

	return true;
}

void DryDew::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	turnGame();
}

void DryDew::turnGame()
{
	auto t = TransitionFadeTR::create(2.0f, HelloWorld::createScene());
	Director::getInstance()->replaceScene(t);
}
void DryDew::onEnter()
{
	Layer::onEnter();
}
void DryDew::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void DryDew::onExit()
{
	Layer::onExit();
}
void DryDew::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}
void DryDew::cleanup()
{
	Layer::cleanup();
}