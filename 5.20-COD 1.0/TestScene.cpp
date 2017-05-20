#include "TestScene.h"
#include "cocos2d.h"
#include "PlayerLayer.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* TestScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = TestScene::create();
	scene->addChild(layer);
	// 'layer' is an autorelease object

	// return the scene
	return scene;
}

bool TestScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = HelloWorld::create();
	auto player = PlayerLayer::create();
	this->addChild(bg,0,"bg");
	this->addChild(player,1,"playerl");

}