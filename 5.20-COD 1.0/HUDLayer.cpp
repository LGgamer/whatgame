#include "HUDLayer.h"
USING_NS_CC;

/*
	Tag:
		4: not moving items
		5: moving times
*/
bool HUDLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto screenSize = Director::getInstance()->getVisibleSize();
	//the health point bar
	auto HpBackground = Sprite::create("hpbar.png");
	HpBackground->setPosition(Vec2(200, screenSize.height - 100));
	HpBackground->setTag(4);
	this->addChild(HpBackground);
	//small map
	auto miniMap = Sprite::create("miniMap.png");
	miniMap->setScale(2);
	miniMap->setAnchorPoint(Vec2(1, 1));
	miniMap->setPosition(Vec2(screenSize.width-20, screenSize.height - 20));
	miniMap->setName("miniMap");
	miniMap->setTag(4);
	this->addChild(miniMap);

	return true;
}

void HUDLayer::addToMiniMap(Node* sprite, Vec2 screenO,std::string fileName)
{
	auto screenP = sprite->getPosition();
	//sprite in map
	auto mapP = screenO + screenP;
	//map size
	auto mapS = this->getParent()->getChildByName("Map")->getContentSize();
	
	float x = mapP.x/mapS.width;
	float y = mapP.y / mapS.height;
	auto miniMapS = this->getChildByName("miniMap")->getContentSize();

	auto spot = Sprite::create(fileName);
	spot->setScale(0.1);
	spot->setTag(5);
	spot->setPosition(Vec2(miniMapS.width*x, miniMapS.height*y));
	this->getChildByName("miniMap")->addChild(spot);
}

void HUDLayer::clearMiniMap()
{
	for (Node* i : this->getChildByName("miniMap")->getChildren())
	{
		if (i->getTag() == 5)
		{
			auto remove = RemoveSelf::create();
			i->runAction(remove);
		}
	}
}