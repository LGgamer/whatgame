#include "LevelUp.h"

using namespace cocos2d;

Scene* LevelUp::createScene()
{
	auto scene = Scene::create();

	auto layer = LevelUp::create();
	
	scene->addChild(layer);

	return scene;
}

bool LevelUp::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto screenSize = Director::getInstance()->getVisibleSize();
	auto soul = Sprite::create("soul.png");
	soul->setScale(0.3);
	soul->setPosition(Vec2(100, screenSize.height - 100));
	this->addChild(soul);

	auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soulForAll");
	auto number = std::to_string(soulnumber);
	auto SoulNumber = Label::createWithSystemFont(number, "Arial", 90);
	SoulNumber->setPosition(Vec2(250, screenSize.height - 100));
	SoulNumber->setTag(99);
	this->addChild(SoulNumber);

	auto Heart = Sprite::create("HealthUp.png");
	Heart->setScale(0.3);
	Heart->setPosition(Vec2(screenSize.width / 2 - 200, screenSize.height / 2 + 120));
	this->addChild(Heart);

	auto Speed = Sprite::create("SpeedUp.png");
	Speed->setScale(0.3);
	Speed->setPosition(Vec2(screenSize.width / 2 + 200, screenSize.height / 2 + 110));
	this->addChild(Speed);

	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(60);
	auto item1 = MenuItemFont::create("HealthUp", CC_CALLBACK_1(LevelUp::maxHpUp, this));
	auto item2 = MenuItemFont::create("SpeedUp", CC_CALLBACK_1(LevelUp::speedUp, this));
	auto menu2 = Menu::create(item1, item2, NULL);
	menu2->alignItemsHorizontallyWithPadding(150);
	this->addChild(menu2);

	auto xone = Label::create("x30", "Arial", 60);
	xone->setPosition(Vec2(screenSize.width / 2 - 180, screenSize.height / 2 - 80));
	auto xtwo = Label::create("x30", "Arial", 60);
	xtwo->setPosition(Vec2(screenSize.width / 2 + 240, screenSize.height / 2 - 80));
	this->addChild(xone);
	this->addChild(xtwo);

	auto soul1 = Sprite::create("soul.png");
	soul1->setPosition(Vec2(screenSize.width / 2 - 300, screenSize.height / 2 - 80));
	auto soul2 = Sprite::create("soul.png");
	soul2->setPosition(Vec2(screenSize.width / 2 + 120, screenSize.height / 2 - 80));
	soul1->setScale(0.2);
	soul2->setScale(0.2);
	this->addChild(soul1);
	this->addChild(soul2);

	auto restart = MenuItemFont::create("Restart", CC_CALLBACK_1(LevelUp::restart, this));
	//restart->setPosition(Vec2(screenSize.width, 100));
	auto menu3 = Menu::create(restart, NULL);
	
	menu3->setPosition(Vec2(screenSize.width/2,screenSize.height/2-200));
	this->addChild(menu3);

	return true;
}

void LevelUp::maxHpUp(Ref *sender)
{
	if (UserDefault::getInstance()->getIntegerForKey("soulForAll") >= 30) {
		UserDefault::getInstance()->setIntegerForKey("hpUp", UserDefault::getInstance()->getIntegerForKey("hpUp") + 10);
		UserDefault::getInstance()->setIntegerForKey("soulForAll", UserDefault::getInstance()->getIntegerForKey("soulForAll") - 30);
		log("Yes");
		auto SoulNumber = this->getChildByTag(99);
		auto remove = RemoveSelf::create();
		SoulNumber->runAction(remove);
		auto screenSize = Director::getInstance()->getVisibleSize();
		auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soulForAll");
		auto number = std::to_string(soulnumber);
		auto Snumber = Label::createWithSystemFont(number, "Arial", 90);
		Snumber->setPosition(Vec2(250, screenSize.height - 100));
		Snumber->setTag(99);
		this->addChild(Snumber);
	}
	else {
		soulisEnough = false;
		auto SoulNumber = this->getChildByTag(99);
		auto remove = RemoveSelf::create();
		SoulNumber->runAction(remove);
		auto screenSize = Director::getInstance()->getVisibleSize();
		auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soulForAll");
		auto number = std::to_string(soulnumber);
		auto Snumber = Label::createWithSystemFont(number, "Arial", 90);
		Snumber->setPosition(Vec2(250, screenSize.height - 100));
		Snumber->setTag(99);
		this->addChild(Snumber);
		if (soulisEnough == false) {
			auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
			Snumber->runAction(jump);
			soulisEnough = true;
		}
	}
}

void LevelUp::speedUp(Ref *sender)
{
	if (UserDefault::getInstance()->getIntegerForKey("soulForAll") >= 30) {
		UserDefault::getInstance()->setIntegerForKey("speedUp", UserDefault::getInstance()->getIntegerForKey("speedUp") + 20);
		UserDefault::getInstance()->setIntegerForKey("soulForAll", UserDefault::getInstance()->getIntegerForKey("soulForAll") - 30);
		auto SoulNumber = this->getChildByTag(99);
		auto remove = RemoveSelf::create();
		SoulNumber->runAction(remove);
		auto screenSize = Director::getInstance()->getVisibleSize();
		auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soulForAll");
		auto number = std::to_string(soulnumber);
		auto Snumber = Label::createWithSystemFont(number, "Arial", 90);
		Snumber->setPosition(Vec2(250, screenSize.height - 100));
		Snumber->setTag(99);
		this->addChild(Snumber);
	}
	else {
		soulisEnough = false;
		auto SoulNumber = this->getChildByTag(99);
		auto remove = RemoveSelf::create();
		SoulNumber->runAction(remove);
		auto screenSize = Director::getInstance()->getVisibleSize();
		auto soulnumber = UserDefault::getInstance()->getIntegerForKey("soulForAll");
		auto number = std::to_string(soulnumber);
		auto Snumber = Label::createWithSystemFont(number, "Arial", 90);
		Snumber->setPosition(Vec2(250, screenSize.height - 100));
		Snumber->setTag(99);
		this->addChild(Snumber);
		if (soulisEnough == false) {
			auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
			Snumber->runAction(jump);
			soulisEnough = true;
		}
	}
}

void LevelUp::restart(Ref *sender) 
{
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->replaceScene(sc);
}
