#include "SettingPage.h"
USING_NS_CC;

Scene* SettingPage ::createNewScene() {
	auto scene = Scene::create();
	auto layer = SettingPage::create();
	scene->addChild(layer, 1);
	return scene;
}

bool SettingPage::init() {
	if (!Layer::init())
		return false;

	auto screenSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto bgtest = Sprite::create("bgtest.png");
	bgtest->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	bgtest->setTag(0);
	this->addChild(bgtest, -1);

	auto SettingPrompt = Sprite::create("setting.png");
	SettingPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200));
	SettingPrompt->setScale(0.2);
	this->addChild(SettingPrompt);
	
	Sprite* backSpriteNormal = Sprite::create("menu/backbutton.png");
	backSpriteNormal->setScale(0.3);
	Sprite* backSpriteSelected = Sprite::create("menu/backbutton.png");
	backSpriteSelected->setScale(0.3);
	MenuItemSprite*backMenuItem = MenuItemSprite::create(backSpriteNormal, backSpriteSelected, CC_CALLBACK_1(SettingPage::goToStartPage, this));
	backMenuItem->setPosition(Vec2(screenSize.width/2+170, screenSize.height/2- 110));


	auto soundOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	auto soundOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");
	
	auto soundLable = Label::create("sound", "Time New Roman", 30);
	soundLable->setPosition(Vec2(screenSize.width/2, screenSize.height/2 - 130));
	soundLable->setColor(Color3B(255, 255, 255));
	this->addChild(soundLable);
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingPage::menuSoundToggleCallback, this), soundOnMenuItem,soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Vec2(screenSize.width/2+100,screenSize.height/2 - 130));
	soundToggleMenuItem->setScale(0.05);
	auto menu = Menu::create(soundToggleMenuItem, backMenuItem, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
	return true;
}

void SettingPage::goToStartPage(Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("sound/on.wav");
	Director::getInstance()->popScene();
}

void SettingPage::menuSoundToggleCallback(Ref* pSender) {
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	if (soundToggleMenuItem->getSelectedIndex() == 1) {
		SimpleAudioEngine::getInstance()->playEffect("sound/off.wav");
		if (isEffect == true) {
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		UserDefault::getInstance()->setBoolForKey("isEffect",false);
	}
	else {
		SimpleAudioEngine::getInstance()->playEffect("sound/on.wav");
		if (isEffect == false) {
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
}

void SettingPage::onEnter()
{
	Layer::onEnter();
}

void SettingPage::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void SettingPage::onExit()
{
	Layer::onExit();
}

void SettingPage::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void SettingPage::cleanup()
{
	Layer::cleanup();
}


