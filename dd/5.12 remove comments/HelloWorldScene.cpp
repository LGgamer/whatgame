#if 1
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CollisionTest.h"
#include "TestStartPage.h"
#include "PlayerLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
		if (!Layer::init())//WithColor(ccc4(0,255,255,255)))
		{
			return false;
		}
		screenO = Director::getInstance()->getVisibleOrigin();

		CCSize screensize = CCDirector::sharedDirector()->getVisibleSize();
		auto player = CCSprite::create("testball.png");
		player->setPosition(ccp(0 + 40, screensize.height / 2));
		player->setTag(1);
		auto bg = Sprite::create("Map.png");
		bg->setAnchorPoint(Vec2(0,0));
		bg->setPosition(Vec2(0,0));
		this->addChild(bg,-1);
		this->addChild(player);
		auto item1 = MenuItemAtlasFont::create("100", "wall.png", 16, 24, '.');
		MenuItemFont::setFontName("Arial");
		MenuItemFont::setFontSize(86);
		auto item2 = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::mydefine2,this));
		auto menu = Menu::create(item1, item2, NULL);
		menu->alignItemsVerticallyWithPadding(10);
		this->addChild(menu);
#if 1
		auto kblistener = EventListenerKeyboard::create();
		kblistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
		kblistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(kblistener, this);
#endif

#if 1
		auto testMonster = Sprite::create("vampire.png");
		//testMonster->setAnchorPoint(Vec2(0, 0));
		testMonster->setPosition(Vec2(screensize.width / 2, screensize.height / 2));
		testMonster->setScale(1);
		testMonster->setName("vampire");
		this->addChild(testMonster);
#endif		
}

bool HelloWorld::isHold(EventKeyboard::KeyCode code)
{

	// Check if the key is currently pressed by seeing it it's in the std::map keys

	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?

	if (keys.find(code) != keys.end())
		return true;
	return false;

}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	auto screensize = Director::getInstance()->getVisibleSize();
	auto player = this->getChildByTag(1);
	auto cp = player->getPosition();
	auto testMonster = this->getChildByName("vampire");
	auto playerP = player->getPosition();
	auto playerS = player->getContentSize();
	int pwith = player->getScale()*playerS.width;
	int pheig = playerS.height*player->getScale();
	auto monsterP = testMonster->getPosition();
	auto monsterS = testMonster->getContentSize();
	int mwith = testMonster->getScale()*monsterS.width;
	int mheig = monsterS.height*testMonster->getScale();
	const float d = 100;
	hold = 1;
	switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			{
				screensize = Director::getInstance()->getVisibleSize();
				cp = player->getPosition();
				if (CollisionTest::isCollision(cp.x, cp.y + d, pwith, pheig, monsterP.x, monsterP.y, mwith,mheig))
				{
					log("no");
					if (cp.x > monsterP.x )
						if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
							player->setPosition(Vec2(cp.x + 5, cp.y));
						}
						else { ; }
					else if (cp.x < monsterP.x)
						if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
							player->setPosition(Vec2(cp.x - 5, cp.y));
						}
						else { ; }
				}
				else
				{
					if (cp.y - screenO.y < screensize.height / 4 * 3)
					{
						player->setPosition(Vec2(cp.x, cp.y + d));
						log("yes");
					}
					else
					{
						player->setPosition(Vec2(cp.x, cp.y + d));
						this->setPosition(Vec2(this->getPosition().x, this->getPosition().y - d));
						screenO.y += d;
					}
				}
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			log("down");
			cp = player->getPosition();
			screensize = Director::getInstance()->getVisibleSize();
			if (CollisionTest::isCollision(cp.x, cp.y - d, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.x > monsterP.x)
					if (cp.x + 0.5*pwith > monsterP.x + 0.5*mwith) {
						player->setPosition(Vec2(cp.x + 5, cp.y));
					}
					else { ; }

				else if (cp.x < monsterP.x)
					if (cp.x - 0.5*pwith < monsterP.x - 0.5*mwith) {
						player->setPosition(Vec2(cp.x - 5, cp.y));
					}
					else { ; }
			}
			else
			{
				if (cp.y - screenO.y > screensize.height / 4 )
				{
					player->setPosition(Vec2(cp.x, cp.y - d));
					log("yes");
				}
				else
				{
					player->setPosition(Vec2(cp.x, cp.y - d));
					this->setPosition(Vec2(this->getPosition().x, this->getPosition().y + d));
					screenO.y -= d;
				}
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			log("down");
			screensize = Director::getInstance()->getVisibleSize();
			cp = player->getPosition();
			if (CollisionTest::isCollision(cp.x-d, cp.y, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						player->setPosition(Vec2(cp.x , cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
						if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
							player->setPosition(Vec2(cp.x, cp.y - 5));
						}
						else { ; }
			}
			else
			{
				if (cp.x - screenO.x > screensize.width/ 4)
				{
					player->setPosition(Vec2(cp.x -d, cp.y));
					log("yes");
				}
				else
				{
					player->setPosition(Vec2(cp.x - d, cp.y));
					this->setPosition(Vec2(this->getPosition().x + d, this->getPosition().y));
					screenO.x -= d;
				}
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			log("down");
			screensize = Director::getInstance()->getVisibleSize();
			cp = player->getPosition();
			if (CollisionTest::isCollision(cp.x + d, cp.y, pwith, pheig, monsterP.x, monsterP.y, mwith, mheig))
			{
				log("no");
				if (cp.y > monsterP.y)
					if (cp.y + 0.5*pheig > monsterP.y + 0.5*mheig) {
						player->setPosition(Vec2(cp.x, cp.y + 5));
					}
					else { ; }

				else if (cp.y < monsterP.y)
					if (cp.y - 0.5*pheig < monsterP.y - 0.5*mheig) {
						player->setPosition(Vec2(cp.x, cp.y - 5));
					}
					else { ; }
			}
			else
			{
				if (cp.x - screenO.x < screensize.width / 4*3)
				{
					player->setPosition(Vec2(cp.x+d, cp.y));
					log("yes");
				}
				else
				{
					player->setPosition(Vec2(cp.x + d, cp.y));
					this->setPosition(Vec2(this->getPosition().x - d, this->getPosition().y));
					screenO.x += d;
				}
			}
			break;
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	hold = 0;
	log("THere");
}
	

bool HelloWorld::onTouchBegan(CCTouch *pTouch, CCEvent *event)
{
	CCSize screensize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint locInView = pTouch->getLocationInView();
	CCPoint loc = CCDirector::sharedDirector()->convertToGL(locInView);
	auto bullet = CCSprite::create("testball.png");
	bullet -> setScale(0.1);
	bullet->setPosition(ccp(0 + 40, screensize.height / 2));
	this->addChild(bullet);
	auto move = CCMoveTo::create(2, ccp(loc.x,loc.y));
	auto actionRemove = RemoveSelf::create();
	bullet -> runAction(Sequence::create(move,actionRemove, NULL));
	return true;
}

void HelloWorld::mydefine2(Ref *sender)
{
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);
}

void HelloWorld::mydefine(Ref* who)
{
	Sprite* sprite = static_cast<Sprite*>(who);
	sprite ->setPosition(ccp(300, 80));
	sprite ->setScale(2);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);
	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> HelloWorld::keys;
#endif


