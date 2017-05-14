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
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto SettingPrompt = Sprite::create("setting.png");
	SettingPrompt->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200));
	SettingPrompt->setScale(0.1);
	this->addChild(SettingPrompt);
	
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(60);
	auto item2 = MenuItemFont::create("ok", CC_CALLBACK_1(SettingPage::goToStartPage, this));

	auto soundOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	auto soundOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingPage::menuSoundToggleCallback, this), soundOnMenuItem,soundOffMenuItem, NULL);
	//soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 220)));
	soundToggleMenuItem->setScale(0.1);
	auto menu = Menu::create(soundToggleMenuItem,item2, NULL);

	//menu->setPosition(Vec2::ZERO);
	menu->alignItemsVerticallyWithPadding(50);
	this->addChild(menu);
	return true;
}

void SettingPage::goToStartPage(Ref* pSender) {

	Director::getInstance()->popScene();
}
void SettingPage::menuSoundToggleCallback(Ref* pSender) {
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	if (soundToggleMenuItem->getSelectedIndex() == 1) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/background.mp3");
	}
	else {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3");
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


