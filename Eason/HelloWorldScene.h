class GameStartPage : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createNewScene();

	virtual bool init() override;
	void menuItemCallback(Ref * pSender);

	//here is keyboard scene code from game from scratch.com
	virtual void update(float delta) override;

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	int keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

	void fire(float dt);

	cocos2d::ui::LoadingBar* HpBar;


private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;

	CREATE_FUNC(GameStartPage);
};
#endif // __HELLOWORLD_SCENE_H__
