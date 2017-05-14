#include "GameOver.h"
using namespace cocos2d;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	
	auto layer = GameOver::create();

	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto gameover = Sprite::create("GameOver.png");
	auto screenSize = Director::getInstance()->getVisibleSize();
	gameover->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200));	
	auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
	this->addChild(gameover);
	gameover->runAction(jump);

	scheduleOnce(schedule_selector(GameOver::showScore), 2);
	scheduleOnce(schedule_selector(GameOver::showSoul), 2);

	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(60);
	auto restart = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOver::restart, this));
	auto mainmenu = MenuItemFont::create("Main Menu", CC_CALLBACK_1(GameOver::mainmenu, this));
	auto menu = Menu::create(restart, mainmenu, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);

}

void GameOver::showScore(float dt)
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

void GameOver::showSoul(float dt)
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

void GameOver::restart(Ref *sender)
{
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);
}

void GameOver::mainmenu(Ref *sender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);
}