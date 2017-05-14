#include "Congratulation.h"
using namespace cocos2d;

Scene* Congratulation::createScene()
{
	auto scene = Scene::create();

	auto layer = Congratulation::create();

	scene->addChild(layer);

	return scene;
}

bool Congratulation::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto congra = Sprite::create("Congra.png");
	congra->setPosition(Vec2(screenSize.width / 2, screenSize.height - 50));
	this->addChild(congra);
	congra->runAction(jump);


	scheduleOnce(schedule_selector(Congratulation::showScore), 2);
	scheduleOnce(schedule_selector(Congratulation::showSoul), 2);

	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(60);
	auto restart = MenuItemFont::create("Restart", CC_CALLBACK_1(Congratulation::restart, this));
	auto mainmenu = MenuItemFont::create("Mainmene", CC_CALLBACK_1(Congratulation::mainmenu, this));
	auto menu = Menu::create(restart, mainmenu, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);
	
}

void Congratulation::showScore(float dt)
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	auto Score = Label::createWithSystemFont("Score: ", "Arial", 90);
	Score->setPosition(Vec2(screenSize.width / 2 - 100, screenSize.height / 2 - 100));
	this->addChild(Score);
	Score->runAction(jump);

	auto scorenumber = UserDefault::getInstance()->getIntegerForKey("score");
	auto number = std::to_string(scorenumber);
	auto ScoreNumber = Label::createWithSystemFont(number, "Arial", 90);
	ScoreNumber->setPosition(Vec2(screenSize.width / 2 + 100, screenSize.height / 2 - 100));
	this->addChild(ScoreNumber);
	ScoreNumber->runAction(jump);
}

void Congratulation::showSoul(float dt)
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	auto Soul = Sprite::create("soul.png");
	Soul->setPosition(Vec2(screenSize.width / 2 - 100, screenSize.height / 2 - 200));
	Soul->setScale(0.3);
	this->addChild(Soul);
	Soul->runAction(jump);

	auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soul");
	auto number = std::to_string(soulnumber);
	auto SoulNumber = Label::createWithSystemFont(number, "Arial", 90);
	SoulNumber->setPosition(Vec2(screenSize.width / 2 + 100, screenSize.height / 2 - 200));
	this->addChild(SoulNumber);
	SoulNumber->runAction(jump);

}

void Congratulation::restart(Ref *sender)
{
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);
}

void Congratulation::mainmenu(Ref *sender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);
}