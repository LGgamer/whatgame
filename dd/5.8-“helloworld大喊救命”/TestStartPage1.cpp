#include "TestStartPage.h"
#include "SimpleAudioEngine.h"
#include "character.h"
#include "CollisionTest.h"
#include "PlayerLayer.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();

	//auto bg = GameStartPage::create();

	auto layer = GameStartPage::create();

	//scene->addChild(bg,0);
	scene->addChild(layer, 1);

	return scene;
}

bool GameStartPage::init()
{
	if (!Layer::init())
		return false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	auto screenSize = Director::getInstance()->getVisibleSize();


}
