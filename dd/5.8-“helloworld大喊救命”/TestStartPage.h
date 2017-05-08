#ifndef _TESTSTARTPAGE_H_
#define _TESTSTARTPAGE_H_

#include "cocos2d.h"
#include "CollisionList.h"
#include "character.h"
#include "Monster.h"
//#include "SceneManager.h"

class GameStartPage : public cocos2d::Layer
{
public:
	int monsterNum;

	CollisonList cl;
	cocos2d::Point screenO;
	character maincharacter;
	//auto bg;
//	Sprite* sprite;
public:

	//初始化怪兽
	void initMonster();
	//初始化怪兽状态
	void initMstatus(Monster* & m);

	//update 中更新怪兽状态
	void updateMonster(float delta);
	//每一个场景关卡都会有一个碰撞列表
	void initCL();
	
	//更新怪物碰撞列表
	void updateCL();
	//检查玩家和CL中的碰撞
	PandS cheakCL(float x1, float y1, int w1, int h1);
	//移动地图元素
	void GameStartPage::moveCL(float dx, float dy);

	static cocos2d::Scene* createNewScene();

	virtual bool init() override;
	void menuItemCallback(Ref * pSender);

	//here is keyboard scene code from game from scratch.com
	virtual void update(float delta) override;

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);


	void keyEvent(float delta);

	void fire(float dt);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;

	CREATE_FUNC(GameStartPage);
};
#endif // __GAMESTARTPAGE_H__
