#include "BossPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "ui\UILoadingBar.h"
#include "RandomList.h"
#include "Monster.h"
#include "WeaponBuff.h"
#include "BossPage.h"
#include "Congratulation.h"
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

	sprite = character::create("MainCharacter.png");
	
	sprite->attackM = UserDefault::getInstance()->getIntegerForKey("player_attackM");
	sprite->basic_attack = UserDefault::getInstance()->getIntegerForKey("player_attack");
	sprite->attackRange = UserDefault::getInstance()->getIntegerForKey("player_attackRange");
	sprite->attackSpeed = UserDefault::getInstance()->getIntegerForKey("player_attackSpeed");
	sprite->basic_speed = UserDefault::getInstance()->getIntegerForKey("player_Speed");
	sprite->basic_health = UserDefault::getInstance()->getIntegerForKey("player_HP");
	MAXhealth = UserDefault::getInstance()->getIntegerForKey("player_MAXHP");

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
	schedule(schedule_selector(GameStartPage::fire), 0.4);
	schedule(schedule_selector(GameStartPage::monsterPatrol), 1);
	schedule(schedule_selector(GameStartPage::monsterAttack), 1, kRepeatForever, 0.65);
}

void BossPage::initMonster()
{
	auto boss = Boss_monster::create("boss.png");
	boss->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height / 2+1000));
	boss->setTag(2);
	boss->setName("boss");
	this->addChild(boss);
	BossNum++;

	//boss->health = 50;
}

void BossPage :: nextScene(float dt)
{
	write();
	unscheduleAllSelectors();
	auto sc = Congratulation::createScene();
	auto t = TransitionFade::create(2.0, sc);
	//auto t = TransitionFade::create(2.0f, sc);

	Director::getInstance()->replaceScene(t);
}

void BossPage::checkEnd()
{
	if (BossNum <= 0 && cround == totalRound)
	{
		scheduleOnce(schedule_selector(GameStartPage::createPortal), 0.1);
	}
	else if (BossNum <= 0 && cround < totalRound)
	{

		auto mn = random(cround + 1, cround + 2);
		monsterNum = mn;
		scheduleOnce(schedule_selector(GameStartPage::nextLevel), 3);

	}
	if (done)
	{
		unschedule(schedule_selector(GameStartPage::createPortal));
		auto portal = this->getChildByName("portal");
		auto player = this->getChildByTag(1);
		//if player is in the portal
		if (player->getPosition().x < portal->getPosition().x + portal->getContentSize().width / 2 * portal->getScale() && player->getPosition().x > portal->getPosition().x - portal->getContentSize().width / 2 * portal->getScale() && player->getPosition().y < portal->getPosition().y + portal->getContentSize().height / 2 * portal->getScale() && player->getPosition().y > portal->getPosition().y - portal->getContentSize().height / 2 * portal->getScale())
		{

			scheduleOnce(schedule_selector(GameStartPage::nextScene), 3);
		}

	}
}

void BossPage::checkBullet()
{
	character* maincharacter = static_cast<character*> (this->getChildByTag(1));
	//maincharacter =  (maincharacter);
	Vector<Node* >  childList = this->getChildren();
	Vector<Node*> bulletsByPlayerList;
	Vector<Node*> bulletsByMonsterList;
	for (Node* i : childList)
	{
		//if it is a bullet by player
		if (i->getTag() == 5) {
			bulletsByPlayerList.pushBack(i);
		}

		//if it is a bullet by monsters
		if (i->getTag() == 6) {
			bulletsByMonsterList.pushBack(i);
		}
	}

	for (Node* i : bulletsByPlayerList)
	{
		auto bulletS = i->getContentSize();
		int pwith = i->getScale()*bulletS.width;
		int pheig = bulletS.height*i->getScale();
		auto cp = i->getPosition();
		auto remove1 = RemoveSelf::create();
		updateCL();
		PandS hitted = checkCL(cp.x, cp.y, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			if (hittedSprite->getTag() == 2)
			{
				auto monster = static_cast<Monster*> (this->getChildByName(hitted.name));
				monster->health -= 50;
				if (monster->getHealth() <= 0)
				{
					//drop items
					if (Monster::isDropItem(0.1))
					{
						auto position = monster->getPosition();
						dropSoul(position);
					}
					monster->runAction(remove1);
					GameStartPage::getScore(monster->getScore());
					if (monster->getName().find("boss") != std::string::npos)
						BossNum--;
					else
					{
						currentMonsterNum--;
					}
					
				}
			}
			else if (hittedSprite->getTag() == 8)
			{
				if (Monster::isDropItem(0.1))
				{
					auto position = hittedSprite->getPosition();
					dropBuff(position);
				}
				hittedSprite->runAction(remove1);
			}
			auto remove2 = RemoveSelf::create();
			i->runAction(remove2);
		}
	}

	auto player = this->getChildByTag(1);

	for (Node* i : bulletsByMonsterList)
	{
		auto bulletS = i->getContentSize();
		int pwith = i->getScale()*bulletS.width;
		int pheig = bulletS.height*i->getScale();
		auto cp = i->getPosition();
		auto remove1 = RemoveSelf::create();
		updateCL();
		PandS hitted = checkWall(cp.x, cp.y, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			if (hittedSprite->getTag() == 3)
				i->runAction(remove1);
		}
		else if (CollisionTest::isCollision(player->getPosition().x, player->getPosition().y, player->getContentSize().width*player->getScale(), player->getContentSize().height*player->getScale(), cp.x, cp.y, pwith, pheig))
		{
			//log("1111111");
			std::string name = i->getName();
			int ind = name.find_first_of("-");
			std::string damageS = name.substr(0, ind + 1);

			int damage = atoi(damageS.c_str());
			log("%d", damage);
			maincharacter->HpDown(damage);
			i->runAction(remove1);
		}
	}
}