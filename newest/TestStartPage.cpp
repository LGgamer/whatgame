#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "ui\UILoadingBar.h"
//#include "BackgroundLayer.h"
#include "RandomList.h"
#include "Monster.h"

USING_NS_CC;

//void GameStartPage::menuItemCallback(Ref * pSender) {
//    
//    auto sc = HelloWorld::createScene();
//    Director::getInstance()->pushScene(sc);
//}


Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();

	//auto bg = GameStartPage::create();

	auto layer = GameStartPage::create();

	//scene->addChild(bg,0);
	scene->addChild(layer, 1);

	return scene;
}

bool GameStartPage::init() {
    if (!Layer::init())
        return false;

	//character maincharacter;
	//每种怪的数量
	monsterNum = 7;

    MenuItemFont::setFontName("Times New Roman");
    MenuItemFont::setFontSize(86);

	auto screenSize = Director::getInstance()->getVisibleSize();


	//create the map
#if 1
	auto bg = Sprite::create("Map3_1.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(-0.5*bg->getContentSize().width + Director::getInstance()->getVisibleSize().width*0.5, -0.5*bg->getContentSize().height + Director::getInstance()->getVisibleSize().height*0.5));
	bg->setTag(10);
	bg->setName("Map");
	this->addChild(bg, -1);
#endif

	//create the hp bar
#if 1
	//血条
	auto HpBackground = Sprite::create("hpbg.png");
	HpBackground->setPosition(Vec2(200, screenSize.height - 100));
	this->addChild(HpBackground);
	screenO = (Vec2(0.5*bg->getContentSize().width - Director::getInstance()->getVisibleSize().width*0.5, 0.5*bg->getContentSize().height - Director::getInstance()->getVisibleSize().height*0.5));
#endif

	//create the main character
#if 1
    //first sprite in game start page

    auto sprite = Sprite::create("MainCharacter.png");
    sprite->setPosition(Vec2(40, screenSize.height / 2));
    sprite->setScale(0.3);
    this->addChild(sprite);
    sprite->setTag(1);

#endif
   
    auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioengine->preloadBackgroundMusic("bgmusic.mp3");
    audioengine->playBackgroundMusic("bgmusic.mp3");

	initMonster();
#if 1
	auto testMonster = Sprite::create("vampire.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	testMonster->setScale(0.1);
	testMonster->setTag(3);
	__String* nameCC = __String::createWithFormat("Monster_%d", 1);
	std::string a = nameCC->getCString();

	testMonster->setName("Monster_1");
	this->addChild(testMonster);

	auto testMonster2 = Sprite::create("demon.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster2->setPosition(Vec2(screenSize.width / 2+40, screenSize.height / 2+1000));
	testMonster2->setScale(0.1);
	testMonster2->setTag(3);
	testMonster2->setName("Monster_2");
	this->addChild(testMonster2);

	auto testMonster3 = Sprite::create("pumpkin.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster3->setPosition(Vec2(screenSize.width / 2 + 1000, screenSize.height / 2 ));
	testMonster3->setScale(0.1);
	testMonster3->setTag(3);
	testMonster3->setName("Monster_3");
	this->addChild(testMonster3);

	auto testMonster4 = Sprite::create("pumpkin.png");
	//testMonster->setAnchorPoint(Vec2(0, 0));
	testMonster4->setPosition(Vec2(screenSize.width / 2 + 100, screenSize.height / 2));
	testMonster4->setScale(0.1);
	testMonster4->setTag(3);
	testMonster4->setName("Monster_4");
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
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);

    //create a keyboard listener to move the object.
    
    
    
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
    // Let cocos know we have an update function to be called.
    // No worries, ill cover this in more detail later on
    this->scheduleUpdate();
    
    
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


	updateHP();
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
	keyEvent(delta);

	//update Monster status
	updateMonster(delta);

	//kill the monsters
	killMonsters();
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;

void GameStartPage::keyEvent(float delta) {
	auto screenSize2 = Director::getInstance()->getVisibleSize();
	auto sprite = this->getChildByTag(1);
	auto map = this->getChildByName("Map");

	//use the speed of the character, which can be changed later by buffs
	int speed = maincharacter.get_speed() * 2;

	//get the position of the sprite
	auto cpm = this->getChildByName("Map")->convertToNodeSpace(sprite->getPosition());
	auto cp = sprite->getPosition();
	auto playerP = sprite->getPosition();
	auto playerS = sprite->getContentSize();
	int pwith = sprite->getScale()*playerS.width;
	int pheig = playerS.height*sprite->getScale();

	auto remove = RemoveSelf::create();

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)
		) {
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(sprite->getPosition());
		if (cpm.x - pwith*0.5 <= 0)
			;
		else {
			cp = sprite->getPosition();
			updateCL();
			PandS hitted = cheakCL(cp.x - delta* speed, cp.y, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				auto hittedSprite = this->getChildByName(hitted.name);
				maincharacter.HpDown(10);
				log("%d", maincharacter.get_current_health());
				log("no");
				
				auto monsterP = hittedSprite->getPosition();
				auto monsterS = hittedSprite->getContentSize();
				int mwith = hittedSprite->getScale()*monsterS.width;
				int mheig = monsterS.height*hittedSprite->getScale();

				//hittedSprite->runAction(remove);

				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						sprite->setPosition(Vec2(cp.x, cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
					if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
						sprite->setPosition(Vec2(cp.x, cp.y - 5));
					}
					else { ; }
			}
			else
			{
				if (cpm.x - screenO.x > screenSize2.width / 4 || screenO.x <= 0)
				{
					//sprite->setPosition(Vec2(cp.x - delta * speed, cp.y));
					sprite->setPositionX(cp.x - delta* speed);
					log("yes");
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
			cp = sprite->getPosition();
			updateCL();
			PandS hitted = cheakCL(cp.x + delta* speed, cp.y, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)
			{
				auto hittedSprite = this->getChildByName(hitted.name);

				maincharacter.HpDown(10);
				log("%d", maincharacter.get_current_health());
				log("no");
				//auto remove = RemoveSelf::create();
				
				auto monsterP = hittedSprite->getPosition();
				auto monsterS = hittedSprite->getContentSize();
				int mwith = hittedSprite->getScale()*monsterS.width;
				int mheig = monsterS.height*hittedSprite->getScale();

				//hittedSprite->runAction(remove);

				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						sprite->setPosition(Vec2(cp.x, cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
					if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
						sprite->setPosition(Vec2(cp.x, cp.y - 5));
					}
					else { ; }
			}
			else
			{
				if (cpm.x - screenO.x < screenSize2.width / 4 * 3 || screenO.x + screenSize2.width >= map->getContentSize().width)
				{
					sprite->setPosition(Vec2(cp.x + delta * speed, cp.y));
					log("yes");
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
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(sprite->getPosition());
		if (cpm.y - pheig*0.5 <= 0)
			;
		else {
			cp = sprite->getPosition();
			updateCL();
			PandS hitted = cheakCL(cp.x, cp.y - delta* speed, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				auto hittedSprite = this->getChildByName(hitted.name);
				maincharacter.HpDown(10);
				log("%d", maincharacter.get_current_health());
				log("no");
				
				auto monsterP = hittedSprite->getPosition();
				auto monsterS = hittedSprite->getContentSize();
				int mwith = hittedSprite->getScale()*monsterS.width;
				int mheig = monsterS.height*hittedSprite->getScale();

				//hittedSprite->runAction(remove);

				if (cp.x > monsterP.x)
					if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
						sprite->setPosition(Vec2(cp.x + 5, cp.y));
					}
					else { ; }

				else if (cp.x < monsterP.x)
					if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
						sprite->setPosition(Vec2(cp.x - 5, cp.y));
					}
					else { ; }
			}
			else
			{
				if (cpm.y - screenO.y > screenSize2.height / 4 || screenO.y <= 0)
				{
					sprite->setPosition(Vec2(cp.x, cp.y - delta * speed));
					log("yes");
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
		cpm = this->getChildByName("Map")->convertToNodeSpaceAR(sprite->getPosition());
		if (cpm.y + pheig*0.5 >= map->getContentSize().height)
			;
		else {
			cp = sprite->getPosition();
			updateCL();
			PandS hitted = cheakCL(cp.x, cp.y + delta* speed, pwith, pheig);
			if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
			{
				auto hittedSprite = this->getChildByName(hitted.name);

				maincharacter.HpDown(10);
				log("%d", maincharacter.get_current_health());
				log("no");
				
				
				auto monsterP = hittedSprite->getPosition();
				auto monsterS = hittedSprite->getContentSize();
				int mwith = hittedSprite->getScale()*monsterS.width;
				int mheig = monsterS.height*hittedSprite->getScale();

				//hittedSprite->runAction(remove);
				if (cp.x > monsterP.x)
					if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
						sprite->setPosition(Vec2(cp.x + 5, cp.y));
					}
					else { ; }

				else if (cp.x < monsterP.x)
					if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
						sprite->setPosition(Vec2(cp.x - 5, cp.y));
					}
					else { ; }
			}
			else
			{
				if (cpm.y - screenO.y < screenSize2.height * 3 / 4 || screenO.y + screenSize2.height >= map->getContentSize().height)
				{
					sprite->setPosition(Vec2(cp.x, cp.y + delta * speed));
					log("yes");
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

//enable firing bullets, whose tags are 5 and names to be "%dbullet", bulletnumber
void GameStartPage::fire(float dt) {

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);
		BulletNumber++;
		log("%d", BulletNumber);
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
		log("%d", BulletNumber);
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
		log("%d", BulletNumber);
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
		log("%d", BulletNumber);
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

void GameStartPage::killMonsters() {
	Vector<Node* >  childList = this->getChildren();
	Vector<Node*> bulletsList;
	for (Node* i : childList)
	{
		//if it is a bullet
		if (i->getTag() == 5) {
			bulletsList.pushBack(i);
		}
	}
	
	for (Node* i : bulletsList)
	{
		auto bulletS = i->getContentSize();
		int pwith = i->getScale()*bulletS.width;
		int pheig = bulletS.height*i->getScale();
		auto cp = i->getPosition();
		auto remove1 = RemoveSelf::create();
		updateCL();
		PandS hitted = cheakCL(cp.x, cp.y, pwith, pheig);
		if (hitted.height > 0 && hitted.width > 0)//, monsterP.x, monsterP.y, mwith, mheig))
		{
			auto hittedSprite = this->getChildByName(hitted.name);
			if (hittedSprite->getTag() == 2)
			{
				auto monster = static_cast<Monster*> (this->getChildByName(hitted.name));
				monster->health -= 50;
				if (monster->getHealth() <= 0)
					monster->runAction(remove1);
			}
			auto remove2 = RemoveSelf::create();
			i->runAction(remove2);
		}
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
			log("name %s", vampire.name);
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
		/*for (PandS i : cl.changed)
		{
			log("mx %f", i.x);
			log("my %f", i.y);
			log("mw %d", i.width);
			log("mh %d", i.height);
		}*/
	}
}

void GameStartPage::updateCL()
{
	cl.changed.clear();
	cl.fixed.clear();
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
	}
}

PandS GameStartPage::cheakCL(float x1, float y1, int w1, int h1)
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
			log("mx %f", i.x);
			log("my %f", i.y);
			log("mw %d", i.width);
			log("mh %d", i.height);
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
			log("mx %f", i.x);
			log("my %f", i.y);
			log("mw %d", i.width);
			log("mh %d", i.height);
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
	for (PandS i : cl.fixed)
	{
		auto element = this->getChildByName(i.name);
		element->setPosition(Vec2(element->getPosition().x+dx, element->getPosition().y+dy));
	}
	for (PandS i : cl.changed)
	{
		auto element = this->getChildByName(i.name);
		element->setPosition(Vec2(element->getPosition().x+dx, element->getPosition().y+dy));
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
		testMonster->setPosition(Vec2(xList[i] * INTERVAL, mapSize.height / 2 - 500 + yList[i] * INTERVAL));
		testMonster->setScale(0.1);
		testMonster->setTag(2);
		//__String* nameCC = __String::createWithFormat("vampire_%d", i);
		std::string name = "vampire_";
		std::string a = name.append(std::to_string(i));
		testMonster->setName(a);
		this->addChild(testMonster);

		auto testMonster2 = Monster::create("demon.png");
		initMstatus(testMonster2);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster2->setPosition(Vec2(-(mapSize.width / 2 - 1000) + xList[i] * INTERVAL, yList[i] * INTERVAL));
		testMonster2->setScale(0.1);
		testMonster2->setTag(2);
		//nameCC = __String::createWithFormat("demon_%d", i);
		//a = nameCC->getCString();
		name = "demon_";
		a = name.append(std::to_string(i));
		testMonster2->setName(a);
		this->addChild(testMonster2);

		auto testMonster3 = Monster::create("pumpkin.png");
		initMstatus(testMonster3);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster3->setPosition(Vec2(mapSize.width / 2 - 500 + xList[i] * INTERVAL, yList[i] * INTERVAL));
		testMonster3->setScale(0.1);
		testMonster3->setTag(2);
		/*nameCC = __String::createWithFormat("pumpkin_%d", i);
		a = nameCC->getCString();*/
		name = "pumpkin_";
		 a = name.append(std::to_string(i));
		testMonster3->setName(a);
		this->addChild(testMonster3);

		auto testMonster4 = Monster::create("skeleton.png");
		initMstatus(testMonster4);
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster4->setPosition(Vec2(xList[i] * INTERVAL, -(mapSize.height / 2-1000) + yList[i] * INTERVAL));
		testMonster4->setScale(0.1);
		testMonster4->setTag(2);
		//nameCC = __String::createWithFormat("skeleton_%d", i);
		//a = nameCC->getCString();
		name = "skeleton_";
		a = name.append(std::to_string(i));
		testMonster4->setName(a);
		this->addChild(testMonster4);
	}
}

void GameStartPage::initMstatus(Monster* & m)
{
	m->isFindEnemy = false;
	m->health = 100;
	m->lv = 1;
	m->gold = 10;
	m->damage = 10;
	m->moveSpeed = 100;
	m -> scoutRange = 210;
	m -> attackRange = 100;
	m->description = std::string("A father monster");
	//texture_path = std::string("HelloMonster.png");
	m->damage_coefficient = m->speed_coefficient = m->health_coefficient = m->gold_coefficient = 1;
}

void GameStartPage::updateMonster(float delta)
{
	updateCL();
	auto player = this->getChildByTag(1);
	for (PandS i : cl.changed)
	{
		auto monster = static_cast<Monster*> (this->getChildByName(i.name));
		
		if (Monster::isInRange(player->getPosition(), monster->getPosition(), monster->scoutRange) || monster->isFindEnemy)
		{
			monster->isFindEnemy = true;
			monster->move(player,delta);
		}
		
		
	}
}

void GameStartPage::updateHP()
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto HpBar = cocos2d::ui::LoadingBar::create("Hp.png");
	HpBar->setPosition(Vec2(200, screenSize.height - 100));
	int percent = maincharacter.get_current_health();
	auto remove = RemoveSelf::create();
	HpBar->setPercent(percent);
	this->addChild(HpBar);
	HpBar->runAction(remove);
}

