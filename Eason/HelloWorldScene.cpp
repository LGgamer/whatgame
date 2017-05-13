#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Character.h"


USING_NS_CC;

character maincharacter;

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
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	/////////////////////////////
	// 3. add your codes below...
	// add a label shows "Hello World"
	// create and initialize a label
	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));
	// add the label as a child to this layer
	this->addChild(label, 1);
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(sprite, 0
	*/

	auto screenSize = Director::getInstance()->getWinSize();
	auto player = Sprite::create("HelloWorld.png");
	player->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	this->addChild(player);


	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Start",
		CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));

	/*
	MenuItemAtlasFont * item2 = MenuItemAtlasFont::create("Help",
	"weixin.png", 48, 65, ' ',
	CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	item2->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - 10));
	this->addChild(item2);
	*/

	Menu * mn = Menu::create(item1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);


	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuItem1Callback(Ref * pSender) {

	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);

}

void GameStartPage::menuItemCallback(Ref * pSender) {

	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);
}


Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();

	auto layer = GameStartPage::create();

	scene->addChild(layer);

	return scene;
}

bool GameStartPage::init() {
	if (!LayerColor::initWithColor(Color4B(255, 0, 0, 255)))
		return false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	/*
	//another menu
	auto item1 = MenuItemFont::create("Back",
	CC_CALLBACK_1(GameStartPage::menuItemCallback, this));
	*/

	//first sprite in game start page
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto  sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	sprite->setScale(0.3);
	this->addChild(sprite);
	sprite->setTag(1);

	////the weapon sprite
	//auto weaponSprite = Sprite::create("qq.png");
	//weaponSprite->setScale(0.3);
	//this->addChild(weaponSprite);
	//weaponSprite->setTag(2);
	//

	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);
	schedule(schedule_selector(GameStartPage::fire), 0.5);

	auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("bgmusic.mp3");
	audioengine->playBackgroundMusic("bgmusic.mp3");

	auto HpBar = cocos2d::ui::LoadingBar::create("HealthBar.png");
	HpBar->setPosition(Vec2(300, screenSize.height - 100));
	HpBar->setScale9Enabled(true);
	HpBar->setPercent(20);
	this->addChild(HpBar);


	auto eventListener = EventListenerKeyboard::create();

	
	label = cocos2d::Label::createWithSystemFont("Press the CTRL Key", "Arial", 32);
	label->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	//addChild(label);

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

int GameStartPage::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
		return 0;  // Not pressed, so no duration obviously

				   // Return the amount of time that has elapsed between now and when the user
				   // first started holding down the key in milliseconds
				   // Obviously the start time is the value we hold in our std::map keys
	return (std::chrono::duration_cast<std::chrono::seconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count() / 1);
}

void GameStartPage::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	auto screenSize2 = Director::getInstance()->getVisibleSize();
	auto sprite = this->getChildByTag(1);
	int speed = maincharacter.get_speed();
	//    auto sprite2 = this ->getChildByTag(2);
	//auto weaponSprite = this->getChildByTag(2);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)
		&& sprite->getPositionX() >= 0) {

		sprite->setPositionX(sprite->getPositionX() - delta * speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)
		&& sprite->getPositionX() <= screenSize2.width) {

		sprite->setPositionX(sprite->getPositionX() + delta * speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)
		&& sprite->getPositionY() >= 0) {

		sprite->setPositionY(sprite->getPositionY() - delta * speed);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)
		&& sprite->getPositionY() <= screenSize2.height) {

		sprite->setPositionY(sprite->getPositionY() + delta * speed);
	}
	
	/*
	Node::update(delta);
	if(isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL)) {
	std::stringstream ss;
	ss << "Control key has been pressed for " <<
	keyPressedDuration(EventKeyboard::KeyCode::KEY_CTRL) << " ms";
	label->setString(ss.str().c_str());
	}    else {
	label->setString("Press the CTRL Key");
	}
	*/
}

void GameStartPage::fire(float dt) {

	if ( isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() - Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, -500);

		auto duration = (startPos.y - endPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	} else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(0, sprite->getContentSize().height / 10);
		auto endPos = startPos + Point(0, 500);

		auto duration = (endPos.y - startPos.y) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	} else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

		auto sprite = this->getChildByTag(1);

		auto startPos = sprite->getPosition() + Point(sprite->getContentSize().width / 10, 0);
		auto endPos = startPos + Point(500, 0);

		auto duration = (endPos.x - startPos.x) / 1000;

		bullet->setPosition(startPos);

		this->addChild(bullet);

		auto fire = MoveTo::create(duration, endPos);
		auto remove = RemoveSelf::create();
		bullet->runAction(Sequence::create(fire, remove, NULL));
	} else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.2);

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

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;
