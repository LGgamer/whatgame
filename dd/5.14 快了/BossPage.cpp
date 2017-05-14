#include "BossPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "ui\UILoadingBar.h"
#include "RandomList.h"
#include "Monster.h"
#include "WeaponBuff.h"
#include "BossPage.h"
USING_NS_CC;

Scene* BossPage::createBossScene()
{
	auto scene = Scene::create();

	auto layer = BossPage::create();

	scene->addChild(layer);

	return scene;
}

bool BossPage::init()
{
	if (!Layer::init())
	{
		return false;
	}
	unscheduleUpdate();
	//character maincharacter;
	monsterNum = 1;
	totalRound = 1;
	cround = 1;
	//check if the game is over
	done = false;
	//initiate bullet and soul number
	BulletNumber =  0;

	score = GameStartPage::readScore();

	soulNumber = GameStartPage::readSoul();

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	auto screenSize = Director::getInstance()->getVisibleSize();

#if 1
	auto bg = Sprite::create("Map4.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(-0.5*bg->getContentSize().width + Director::getInstance()->getVisibleSize().width*0.5, -0.5*bg->getContentSize().height + Director::getInstance()->getVisibleSize().height*0.5));
	bg->setTag(0);
	bg->setName("Map");
	this->addChild(bg, -1);
#endif

	hud = HUDLayer::create();
	hud->setName("HUD");
	hud->setTag(4);
	this->addChild(hud);

#if 1
	auto weaponbuff = weaponBuff::create("attackup2.png");
	weaponbuff->setPosition(Vec2(200, screenSize.height / 2));
	weaponbuff->setScale(0.2);
	this->addChild(weaponbuff);
	weaponbuff->setTag(7);
	weaponbuff->setName("attackup");

	auto weaponbuff2 = weapon1::create("attackup2.png");
	weaponbuff2->setPosition(Vec2(300, screenSize.height / 2));
	weaponbuff2->setScale(0.2);
	this->addChild(weaponbuff2);
	weaponbuff2->setTag(7);
	weaponbuff2->setName("speedup");

#endif

	screenO = (Vec2(0.5*bg->getContentSize().width - Director::getInstance()->getVisibleSize().width*0.5, 0.5*bg->getContentSize().height - Director::getInstance()->getVisibleSize().height*0.5));


#if 1
	//first sprite in game start page

	auto sprite = character::create("MainCharacter.png");
	sprite->setPosition(Vec2(40, screenSize.height / 2));
	sprite->setScale(0.3);
	this->addChild(sprite);
	sprite->setTag(1);

#endif

	auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("bgmusic.mp3");
	audioengine->playBackgroundMusic("bgmusic.mp3");


	currentMonsterNum = 0;
	initMonster();


	//initialize wall
	//initWall();

	//create a keyboard listener to move the object.
	auto eventListener = EventListenerKeyboard::create();

	//here is implementation of keyboard scene from game from scratch
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


	initCL();

	//schedules in this layer
	
	scheduleOnce(schedule_selector(BossPage::delay), 2);
	

	return true;
}

void BossPage::delay(float dt)
{
	this->scheduleUpdate();
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::monsterPatrol), 1);
	schedule(schedule_selector(GameStartPage::monsterAttack), 1, kRepeatForever, 0.5);
}

void BossPage::initMonster()
{
	auto boss = Boss_monster::create("boss.png");
	boss->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height / 2+1000));
	boss->setTag(2);
	boss->setName("boss");
	this->addChild(boss);
	currentMonsterNum++;
}

void BossPage :: nextScene(float dt)
{
	write();
	unscheduleAllSelectors();
	auto sc = BossPage::createBossScene();
	auto t = TransitionFade::create(2.0, sc);
	//auto t = TransitionFade::create(2.0f, sc);

	Director::getInstance()->replaceScene(t);
}