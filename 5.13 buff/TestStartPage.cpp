#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "ui\UILoadingBar.h"
#include "RandomList.h"
#include "Monster.h"
#include "WeaponBuff.h"

USING_NS_CC;
/*
	Tag:
		0 : backgraund
		1 : player
		2 : monster
		3 : wall
		4 : UI/HUD
		5 : player bullet
		6 : monster bullet
		7 : buff
*/

Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();
	auto layer = GameStartPage::create();
	scene->addChild(layer, 1);
	return scene;
}

bool GameStartPage::init() {
    if (!Layer::init())
        return false;

	//character maincharacter;
	monsterNum = 1;
	//check if the game is over
	done = false;
	//initiate bullet and soul number
	BulletNumber = soulNumber = 0;

    MenuItemFont::setFontName("Times New Roman");
    MenuItemFont::setFontSize(86);

	auto screenSize = Director::getInstance()->getVisibleSize();

#if 1
	auto bg = Sprite::create("Map3_1.png");
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

	auto weaponbuff2 = weapon1::create("attackup.png");
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
#if 1
	auto testMonster = Sprite::create("vampire.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	testMonster->setScale(1);
	testMonster->setTag(3);
	__String* nameCC = __String::createWithFormat("Monster_%d", 1);
	std::string a = nameCC->getCString();

	testMonster->setName("Wall_6");
	this->addChild(testMonster);

	auto testMonster2 = Sprite::create("demon.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster2->setPosition(Vec2(screenSize.width / 2+40, screenSize.height / 2+1000));
	testMonster2->setScale(1);
	testMonster2->setTag(3);
	testMonster2->setName("Wall_5");
	this->addChild(testMonster2);

	auto testMonster3 = Sprite::create("pumpkin.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster3->setPosition(Vec2(screenSize.width / 2 + 1000, screenSize.height / 2 ));
	testMonster3->setScale(1);
	testMonster3->setTag(3);
	testMonster3->setName("Wall_4");
	this->addChild(testMonster3);

	auto testMonster4 = Sprite::create("pumpkin.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster4->setPosition(Vec2(screenSize.width / 2 + 100, screenSize.height / 2));
	testMonster4->setScale(1);
	testMonster4->setTag(3);
	testMonster4->setName("Wall_3");
	this->addChild(testMonster4);
#endif
#if 1
	auto wall_1 = Sprite::create("hpbar.png");
	wall_1->setPosition(Vec2(screenSize.width / 2 - 100, screenSize.height / 2 + 1000));
	wall_1->setTag(3);
	wall_1->setScale(1);
	wall_1->setName("Wall_1");
	this->addChild(wall_1);

	auto wall_2 = Sprite::create("pit.png");
	wall_2->setPosition(Vec2(screenSize.width / 2 - 1000, screenSize.height / 2 + 1000));
	wall_2->setTag(3);
	wall_2->setScale(1);
	wall_2->setName("Wall_2");
	this->addChild(wall_2);
#endif
	//initialize collision list
	
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
    this->scheduleUpdate();
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::monsterPatrol), 1);
	schedule(schedule_selector(GameStartPage::monsterAttack), 1, kRepeatForever,0.5);

    return true;
}

bool GameStartPage::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end())
        return true;
    return false;
}

double GameStartPage::keyPressedDuration(EventKeyboard::KeyCode code) {
    if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously
    
    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::seconds>
    (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void GameStartPage::update(float delta) {


	
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
	keyEvent(delta);

	//update Monster status
	updateMonster(delta);

	//update HUD
	updateHUD();

	//kill the monsters
	checkBullet();

	//update score
	updateScore();

	if (currentMonsterNum <= 0)
	{
		
		scheduleOnce(schedule_selector(GameStartPage::createPortal), 0.1);
	}
	if (done)
	{
		unschedule(schedule_selector(GameStartPage::createPortal));
	}

}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;


// Function called in defualt scheduler
void GameStartPage::keyEvent(float delta) {
	auto screenSize2 = Director::getInstance()->getVisibleSize();
	auto sprite = this->getChildByTag(1);
	character* maincharacter = dynamic_cast<character*>(sprite);
	auto map = this->getChildByName("Map");

	//use the speed of the character, which can be changed later by buffs
	int speed = maincharacter->get_speed() * 2;

	//get the position of the sprite
	auto cpm = this->getChildByName("Map")->convertToNodeSpace(maincharacter->getPosition());
	auto cp = maincharacter->getPosition();
	auto playerP = maincharacter->getPosition();
	auto playerS = maincharacter->getContentSize();
	int pwith = maincharacter->getScale()*playerS.width;
	int pheig = playerS.height*maincharacter->getScale();

	auto remove = RemoveSelf::create();

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)
		) {
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(maincharacter->getPosition());
		if (cpm.x - pwith*0.5 <= 0)
			;
		else {
			cp = maincharacter->getPosition();
			updateCL();
			PandS hitted = checkCL(cp.x - delta* speed, cp.y, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				
				auto hittedSprite = this->getChildByName(hitted.name);

				// if it is an item
				if (hittedSprite->getTag() == 7)
				{
					if (hittedSprite->getName() == "attackup") {

						weapon1* weapon1buff = new  weapon1;
						weapon1buff->effect(maincharacter);
						delete weapon1buff;
					}
					else if (hittedSprite->getName() == "speedup") {

						weapon2 * weaponbuff2 = new weapon2;
						weaponbuff2->effect(maincharacter);
						delete weaponbuff2;
					}
					//hittedSprite = () hittedSprite;
					//hittedSprite->affect(sprite);

					//test
					hittedSprite->runAction(remove);
				}
				else
				{
					maincharacter->HpDown(10);
				
					auto monsterP = hittedSprite->getPosition();
					auto monsterS = hittedSprite->getContentSize();
					int mwith = hittedSprite->getScale()*monsterS.width;
					int mheig = monsterS.height*hittedSprite->getScale();

					//hittedSprite->runAction(remove);

					if (cp.y > monsterP.y)
						if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
							maincharacter->setPosition(Vec2(cp.x, cp.y + 5));
						}
						else { ; }

					else if (cp.y < monsterP.y)
						if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
							maincharacter->setPosition(Vec2(cp.x, cp.y - 5));
						}
						else { ; }
				}
			}
			else
			{
				if (cpm.x - screenO.x > screenSize2.width / 4 || screenO.x <= 0)
				{
					//sprite->setPosition(Vec2(cp.x - delta * speed, cp.y));
					maincharacter->setPositionX(cp.x - delta* speed);
				}
				else
				{
					//sprite->setPosition(Vec2(cp.x - delta * speed, cp.y));
					moveCL(delta * speed, 0);
					map->setPosition(Vec2(map->getPosition().x + delta * speed, map->getPosition().y));
					screenO.x -= delta * speed;
				}
			}
		}
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)
		) {
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(sprite->getPosition());
		if (cpm.x + pwith*0.5 >= map->getContentSize().width)
			;
		else {
			cp = maincharacter->getPosition();
			updateCL();
			PandS hitted = checkCL(cp.x + delta* speed, cp.y, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)
			{
				auto hittedSprite = this->getChildByName(hitted.name);
				if (hittedSprite->getTag() == 7)
				{
					if (hittedSprite->getName() == "attackup") {

						weapon1* weapon1buff = new  weapon1;
						weapon1buff->effect(maincharacter);
						delete weapon1buff;
					}
					else if (hittedSprite->getName() == "speedup") {

						weapon2 * weaponbuff2 = new weapon2;
						weaponbuff2->effect(maincharacter);
						delete weaponbuff2;
					}
					//hittedSprite = () hittedSprite;
					//hittedSprite->affect(sprite);

					//test
					hittedSprite->runAction(remove);
				}
				else
				{
					maincharacter->HpDown(10);
					//auto remove = RemoveSelf::create();

					auto monsterP = hittedSprite->getPosition();
					auto monsterS = hittedSprite->getContentSize();
					int mwith = hittedSprite->getScale()*monsterS.width;
					int mheig = monsterS.height*hittedSprite->getScale();

					//hittedSprite->runAction(remove);

					if (cp.y > monsterP.y)
						if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
							maincharacter->setPosition(Vec2(cp.x, cp.y + 5));
						}
						else { ; }

					else if (cp.y < monsterP.y)
						if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
							maincharacter->setPosition(Vec2(cp.x, cp.y - 5));
						}
						else { ; }
				}
			}
			else
			{
				if (cpm.x - screenO.x < screenSize2.width / 4 * 3 || screenO.x + screenSize2.width >= map->getContentSize().width)
				{
					maincharacter->setPosition(Vec2(cp.x + delta * speed, cp.y));
				}
				else
				{
					//sprite->setPosition(Vec2(cp.x + delta * speed, cp.y));
					moveCL(-delta * speed, 0);
					map->setPosition(Vec2(map->getPosition().x - delta * speed, map->getPosition().y));
					screenO.x += delta * speed;
				}
			}
		}
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)
		) {
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(maincharacter->getPosition());
		if (cpm.y - pheig*0.5 <= 0)
			;
		else {
			cp = maincharacter->getPosition();
			updateCL();
			PandS hitted = checkCL(cp.x, cp.y - delta* speed, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				auto hittedSprite = this->getChildByName(hitted.name);
				if (hittedSprite->getTag() == 7)
				{
					if (hittedSprite->getName() == "attackup") {

						weapon1* weapon1buff = new  weapon1;
						weapon1buff->effect(maincharacter);
						delete weapon1buff;
					}
					else if (hittedSprite->getName() == "speedup") {

						weapon2 * weaponbuff2 = new weapon2;
						weaponbuff2->effect(maincharacter);
						delete weaponbuff2;
					}
					//hittedSprite = () hittedSprite;
					//hittedSprite->affect(sprite);

					//test
					hittedSprite->runAction(remove);
				}
				else
				{
					maincharacter->HpDown(10);

					auto monsterP = hittedSprite->getPosition();
					auto monsterS = hittedSprite->getContentSize();
					int mwith = hittedSprite->getScale()*monsterS.width;
					int mheig = monsterS.height*hittedSprite->getScale();

					//hittedSprite->runAction(remove);

					if (cp.x > monsterP.x)
						if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
							maincharacter->setPosition(Vec2(cp.x + 5, cp.y));
						}
						else { ; }

					else if (cp.x < monsterP.x)
						if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
							maincharacter->setPosition(Vec2(cp.x - 5, cp.y));
						}
						else { ; }
				}
			}
			else
			{
				if (cpm.y - screenO.y > screenSize2.height / 4 || screenO.y <= 0)
				{
					maincharacter->setPosition(Vec2(cp.x, cp.y - delta * speed));
				}
				else
				{
					//sprite->setPosition(Vec2(cp.x , cp.y - delta * speed));
					moveCL(0, delta * speed);
					map->setPosition(Vec2(map->getPosition().x, map->getPosition().y + delta * speed));
					screenO.y -= delta * speed;
				}
			}
		}
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)
		) {
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(maincharacter->getPosition());
		if (cpm.y + pheig*0.5 >= map->getContentSize().height)
			;
		else {
			cp = maincharacter->getPosition();
			updateCL();
			PandS hitted = checkCL(cp.x, cp.y + delta* speed, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				auto hittedSprite = this->getChildByName(hitted.name);
				if (hittedSprite->getTag() == 7)
				{
					if (hittedSprite->getName() == "attackup") {

						weapon1* weapon1buff = new  weapon1;
						weapon1buff->effect(maincharacter);
						delete weapon1buff;
					}
					else if (hittedSprite->getName() == "speedup") {

						weapon2 * weaponbuff2 = new weapon2;
						weaponbuff2->effect(maincharacter);
						delete weaponbuff2;
					}
					//hittedSprite = () hittedSprite;
					//hittedSprite->affect(sprite);

					//test
					hittedSprite->runAction(remove);
				}
				else
				{
					maincharacter->HpDown(10);



					auto monsterP = hittedSprite->getPosition();
					auto monsterS = hittedSprite->getContentSize();
					int mwith = hittedSprite->getScale()*monsterS.width;
					int mheig = monsterS.height*hittedSprite->getScale();

					//hittedSprite->runAction(remove);
					if (cp.x > monsterP.x)
						if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
							maincharacter->setPosition(Vec2(cp.x + 5, cp.y));
						}
						else { ; }

					else if (cp.x < monsterP.x)
						if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
							maincharacter->setPosition(Vec2(cp.x - 5, cp.y));
						}
						else { ; }
				}
			}
			else
			{
				if (cpm.y - screenO.y < screenSize2.height * 3 / 4 || screenO.y + screenSize2.height >= map->getContentSize().height)
				{
					maincharacter->setPosition(Vec2(cp.x, cp.y + delta * speed));
				}
				else
				{
					//sprite->setPosition(Vec2(cp.x, cp.y + delta * speed));
					moveCL(0, -delta * speed);
					map->setPosition(Vec2(map->getPosition().x, map->getPosition().y - delta * speed));
					screenO.y += delta * speed;
				}
			}
		}
	}
}

void GameStartPage::fire(float dt) {

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);
		BulletNumber++;
		bullet->setTag(5);
		auto str1 = std::to_string(BulletNumber);
		auto str2 = std::string("bullet");
		auto str = str2 + str1;
		bullet->setName(str);
		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() - Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, -500);

		auto duration = (startPos.y - endPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);
		BulletNumber++;
		bullet->setTag(5);
		auto str1 = std::to_string(BulletNumber);
		auto str2 = std::string("bullet");
		auto str = str2 + str1;
		bullet->setName(str);
		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, 500);

		auto duration = (endPos.y - startPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);
		BulletNumber++;
		bullet->setTag(5);
		auto str1 = std::to_string(BulletNumber);
		auto str2 = std::string("bullet");
		auto str = str2 + str1;
		bullet->setName(str);
		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(500, 0);

		auto duration = (endPos.x - startPos.x) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);
		BulletNumber++;
		bullet->setTag(5);
		auto str1 = std::to_string(BulletNumber);
		auto str2 = std::string("bullet");
		auto str = str2 + str1;
		bullet->setName(str);
		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() - Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(-500, 0);

		auto duration = (startPos.x - endPos.x) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	}
}

void GameStartPage::initCL()
{
	Vector<Node*> childList = this->getChildren();

	for (Node* i : childList)
	{
		//if it is player
		if (i->getTag() == 1)
			continue;
		//if it is monster or box
		else if (i->getTag() == 2)
		{
			PandS vampire;
			vampire.name = i->getName();
			vampire.x = i->getPosition().x;
			vampire.y = i->getPosition().y;
			vampire.height = i->getContentSize().height*i->getScale();
			vampire.width = i->getContentSize().width*i->getScale();
			cl.changed.push_back(vampire);
			//cl.changed.
		}
		//if it is wall
		else if (i->getTag() == 3)
		{
			PandS wall;
			wall.name = i->getName();
			wall.x = i->getPosition().x;
			wall.y = i->getPosition().y;
			wall.height = i->getContentSize().height*i->getScale();
			wall.width = i->getContentSize().width*i->getScale();
			cl.fixed.push_back(wall);
		}
		else if (i->getTag() == 7)
		{
			PandS item;
			item.name = i->getName();
			item.x = i->getPosition().x;
			item.y = i->getPosition().y;
			item.height = i->getContentSize().height*i->getScale();
			item.width = i->getContentSize().width*i->getScale();
			cl.items.push_back(item);
		}
	}
}

void GameStartPage::updateCL()
{
	cl.changed.clear();
	cl.fixed.clear();
	cl.items.clear();
	Vector<Node*> childList = this->getChildren();
	for (Node* i : childList)
	{
		//if it is monster or box
		if (i->getTag() == 2)
		{
			PandS vampire;
			vampire.name = i->getName();
			vampire.x = /*i->convertToWorldSpace*/(i->getPosition()).x;
			vampire.y = /*i->convertToWorldSpace*/(i->getPosition()).y;
			vampire.height = i->getContentSize().height*i->getScale();
			vampire.width = i->getContentSize().width*i->getScale();
			cl.changed.push_back(vampire);
			//cl.changed.push_back
			//cl.changed.
		}
		else if (i->getTag() == 3)
		{
			PandS wall;
			wall.name = i->getName();
			wall.x = i->getPosition().x;
			wall.y = i->getPosition().y;
			wall.height = i->getContentSize().height*i->getScale();
			wall.width = i->getContentSize().width*i->getScale();
			cl.fixed.push_back(wall);
		}
		else if (i->getTag() == 7)
		{
			PandS item;
			item.name = i->getName();
			item.x = i->getPosition().x;
			item.y = i->getPosition().y;
			item.height = i->getContentSize().height*i->getScale();
			item.width = i->getContentSize().width*i->getScale();
			cl.items.push_back(item);
		}
	}
}

PandS GameStartPage::checkCL(float x1, float y1, int w1, int h1)
{
	/*auto cp = sprite->getPosition();
	auto playerP = sprite->getPosition();
	auto playerS = sprite->getContentSize();
	int pwith = sprite->getScale()*playerS.width;
	int pheig = playerS.height*sprite->getScale();*/
	PandS tem;
	tem.height = -1;
	tem.name = "-1";
	tem.width = -1;
	tem.x = -1;
	tem.y = -1;
	for (PandS i : cl.changed)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{
			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	for (PandS i : cl.fixed)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{

			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	for (PandS i : cl.items)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{

			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	return tem;
}

PandS GameStartPage::checkCL(float x1, float y1, int w1, int h1,std::string monsterName)
{
	PandS tem;
	tem.height = -1;
	tem.name = "-1";
	tem.width = -1;
	tem.x = -1;
	tem.y = -1;
	for (PandS i : cl.changed)
	{
		if (i.name == monsterName)
			continue;
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{

			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	for (PandS i : cl.fixed)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{

			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	return tem;
}

void GameStartPage::moveCL(float dx,float dy)
{
	for (Node* i : this->getChildren())
	{
		int tag = i->getTag();
		if (tag == 1 || tag == 0 || tag == 4)
			continue;
		else
			i->setPosition(Vec2(i->getPosition().x + dx, i->getPosition().y + dy));
	}
}

void GameStartPage::initMonster()
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto map = this->getChildByName("Map");

	auto mapSize = map->getContentSize();
	
	std::vector<int> xList = RandomList::randmInt(10, monsterNum);
	std::vector<int> yList = RandomList::randmInt(10, monsterNum);
	const int INTERVAL = 50;
	for (int i = 0; i < monsterNum; i++)
	{
		auto testMonster = Monster::create("vampire_1.png");
		initMstatus(testMonster);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster->setPosition(Vec2(xList[i] * INTERVAL, mapSize.height / 2 - 1000 + yList[i] * INTERVAL));
		testMonster->setScale(1);
		testMonster->setTag(2);
		//__String* nameCC = __String::createWithFormat("vampire_%d", i);
		std::string name = "vampire_";
		std::string a = name.append(std::to_string(i));
		testMonster->setName(a);
		this->addChild(testMonster);
		currentMonsterNum++;

		auto testMonster2 = Monster::create("demon.png");
		initMstatus(testMonster2);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster2->setPosition(Vec2(-(mapSize.width / 2 - 1500) + xList[i] * INTERVAL, yList[i] * INTERVAL));
		testMonster2->setScale(1);
		testMonster2->setTag(2);
		//nameCC = __String::createWithFormat("demon_%d", i);
		//a = nameCC->getCString();
		name = "demon_";
		a = name.append(std::to_string(i));
		testMonster2->setName(a);
		this->addChild(testMonster2);
		currentMonsterNum++;

		auto testMonster3 = Fly_monster::create("pumpkin.png");
		//initMstatus(testMonster3);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster3->setPosition(Vec2(mapSize.width / 2 - 500 + xList[i] * INTERVAL, yList[i] * INTERVAL));
		testMonster3->setScale(1);
		testMonster3->setTag(2);
		/*nameCC = __String::createWithFormat("pumpkin_%d", i);
		a = nameCC->getCString();*/
		name = "pumpkin_";
		 a = name.append(std::to_string(i));
		testMonster3->setName(a);
		this->addChild(testMonster3);
		currentMonsterNum++;

		auto testMonster4 = Monster::create("skeleton.png");
		initMstatus(testMonster4);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster4->setPosition(Vec2(xList[i] * INTERVAL, -(mapSize.height / 2-1500) + yList[i] * INTERVAL));
		testMonster4->setScale(1);
		testMonster4->setTag(2);
		//nameCC = __String::createWithFormat("skeleton_%d", i);
		//a = nameCC->getCString();
		name = "skeleton_";
		a = name.append(std::to_string(i));
		testMonster4->setName(a);
		this->addChild(testMonster4);
		currentMonsterNum++;
	}
}

void GameStartPage::initMstatus(Monster* & m)
{
	//m->isFindEnemy = false;
	//m->health = 100;
	//m->lv = 1;
	//m->gold = 10;
	//m->damage = 10;
	//m->moveSpeed = 100;
	//m -> scoutRange = 500;
	//m -> attackRange = 200;
	//m->description = std::string("A father monster");
	////texture_path = std::string("HelloMonster.png");
	//m->damage_coefficient = m->speed_coefficient = m->health_coefficient = m->gold_coefficient = 1;
}

void GameStartPage::updateMonster(float delta)
{
	updateCL();
	auto player = this->getChildByTag(1);
	for (PandS i : cl.changed)
	{
		auto monster = static_cast<Monster*> (this->getChildByName(i.name));
		if (i.name.find("pumpkin_") != std::string::npos)
		{
			monster = (Fly_monster*) (monster);
		}
		else;
			monster = static_cast<Monster*> (this->getChildByName(i.name));

		PandS hitted = checkCL(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width*monster->getScale(), monster->getContentSize().height*monster->getScale(), monster->getName());

		//If monster touches player anyway
		if (CollisionTest::isCollision(player->getPosition().x, player->getPosition().y, player->getContentSize().width*player->getScale(), player->getContentSize().height*player->getScale(), monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width*monster->getScale(), monster->getContentSize().height*monster->getScale()))
		{
			;
			//maincharacter.HpDown(10);
		}
		monster->behavior(player, delta, hitted);
	}
}
	
void GameStartPage::updateHP()
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto HpBar = cocos2d::ui::LoadingBar::create("hp.png");
	HpBar->setPosition(Vec2(200, screenSize.height - 100));
	int percent = maincharacter.get_current_health();
	auto remove = RemoveSelf::create();
	HpBar->setPercent(percent);
	this->getChildByName("HUD")->addChild(HpBar);
	HpBar->runAction(remove);
}

void GameStartPage::checkBullet()
{
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
					currentMonsterNum--;
					monster->runAction(remove1);

					//drop items
					auto position = monster->getPosition();
					dropSoul(position);
					GameStartPage::getScore(10);
				}
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
		if (CollisionTest::isCollision(player->getPosition().x, player->getPosition().y, player->getContentSize().width*player->getScale(), player->getContentSize().height*player->getScale(), cp.x, cp.y, pwith, pheig))
		{
			std::string name = i->getName();
			int ind = name.find_first_of("-");
			std::string damageS = name.substr(0, ind + 1);
			int damage = atoi(damageS.c_str());
			maincharacter.HpDown(damage);
			i->runAction(remove1);
		}
	}
}

PandS GameStartPage::checkWall(float x1, float y1, int w1, int h1)
{
	PandS tem;
	tem.height = -1;
	tem.name = "-1";
	tem.width = -1;
	tem.x = -1;
	tem.y = -1;
	for (PandS i : cl.fixed)
	{
		if (CollisionTest::isCollision(x1, y1, w1, h1, i.x, i.y, i.width, i.height))
		{

			tem.height = i.height;
			tem.name = i.name;
			tem.width = i.width;
			tem.x = i.x;
			tem.y = i.y;
			return tem;
		}
	}
	return tem;
}

void GameStartPage::monsterPatrol(float dt)
{
	updateCL();
	auto player = this->getChildByTag(1);
	for (PandS i : cl.changed)
	{
		auto monster = static_cast<Monster*> (this->getChildByName(i.name));
		if (!monster->isFindEnemy)
		{
			PandS hitted = checkWall(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width*monster->getScale(), monster->getContentSize().height*monster->getScale());
			if (hitted.width > 0 && hitted.height > 0)
			{
				Vec2 d = monster->getPosition() - Vec2(hitted.x, hitted.y);
				monster->setPosition(Vec2(monster->getPosition().x + d.x / monster->moveSpeed, monster->getPosition().y + d.y / monster->moveSpeed));
			}
			else
				monster->patrol(player);
		}
	}
	updateCL();

}

void GameStartPage::monsterAttack(float delta)
{
	//updateCL();
	auto player = this->getChildByTag(1);
	auto childList = this->getChildren();


	for (Node* i : childList)
	{
		if (i->getTag() == 2)
		{
			auto monster = static_cast<Monster*> (i);
			if (i->getName().find("pumpkin_") != std::string::npos)
			{
				monster = (Fly_monster*) monster;
			}
			else
			{
				monster = static_cast<Monster*> (monster);
			}
			if (monster->isAttack)
				monster->attack(player, delta);
		}
		
	}
}

void GameStartPage::createPortal(float dt)
{
	auto portal = Sprite::create("portal.png");
	portal->setName("portal");
	portal->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(portal);
	done = true;
}

void GameStartPage::updateScore()
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto number = std::to_string(score);
	auto scoreNumber = Label::createWithSystemFont(number, "Arial", 80);
	scoreNumber->setPosition(Vec2(screenSize.width - 150, screenSize.height - 180));
	scoreNumber->setTag(4);
	auto remove = RemoveSelf::create();
	this->addChild(scoreNumber);
	scoreNumber->runAction(remove);

}

int GameStartPage::getScore(int number)
{
	score = score + number;
	return score;
}

void GameStartPage::dropSoul(Vec2 position)
{
	auto soul = Sprite::create("soul.png");
	soul->setScale(0.2);
	soul->setPosition(position);
	soul->setTag(7);
	soulNumber++;
	auto str1 = std::to_string(soulNumber);
	auto str2 = std::string("soul");
	auto str = str2 + str1;
	soul->setName(str);
	this->addChild(soul);
}

void GameStartPage::updateHUD()
{
	//update HP
	updateHP();
	hud->clearMiniMap();
	//update minimap;
	for (Node* i : this->getChildren())
	{
		if (i->getTag() == 1)
			hud->addToMiniMap(i, screenO,"pink.png");
		else if (i->getTag() == 2)
		{
			hud->addToMiniMap(i, screenO,"wall.png");
		}
	}
}