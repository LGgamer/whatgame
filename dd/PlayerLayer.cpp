#include "PlayerLayer.h"
//#include "SimpleAudioEngine.h"
//#include "character.h"
//#include "CollisionTest.h"

USING_NS_CC;

//void GameStartPage::menuItemCallback(Ref * pSender) {
//    
//    auto sc = HelloWorld::createScene();
//    Director::getInstance()->pushScene(sc);
//}

bool PlayerLayer::init() {
	if (!Layer::init())
		return false;

	//first sprite in game start page
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(40, screenSize.height / 2));
	sprite->setScale(0.3);
	this->addChild(sprite);
	sprite->setTag(10);


	return true;
}
