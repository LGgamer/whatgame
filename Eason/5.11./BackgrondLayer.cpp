#include "BackgroundLayer.h"
USING_NS_CC;

bool BackgroundLayer::init()
{
	if (!Layer::init())
		return false;

	auto bg = Sprite::create("Map.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(-0.5*bg->getContentSize().width + Director::getInstance()->getVisibleSize().width*0.5, -0.5*bg->getContentSize().height + Director::getInstance()->getVisibleSize().height*0.5));
	bg->setTag(1);
	bg->setName("Map");
	this->addChild(bg, -1);

	return true;
}