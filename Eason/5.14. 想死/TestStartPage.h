#ifndef _TESTSTARTPAGE_H_
#define _TESTSTARTPAGE_H_

#include "cocos2d.h"
#include "CollisionList.h"
#include "character.h"
#include "Monster.h"
#include "HUDLayer.h"
//#include "SceneManager.h"

class GameStartPage : public cocos2d::Layer
{
public:
	//monster number for each type
	int monsterNum;
	//current monster number for all types
	int currentMonsterNum;
	//total round number
	int totalRound;
	//current round number;
	int cround;

	//判断游戏结束
	bool done;

	//分数
	int score;
	//number of soul
	int soulNumber;
	//number of bullet
	int BulletNumber;

	CollisonList cl;
	cocos2d::Point screenO;
	//character maincharacter;
	HUDLayer* hud;
	//auto bg;
//	Sprite* sprite;
public:

	//分数增加
	void updateScore();
	int getScore(int number);

	//初始化墙
	void initWall();

	//初始化怪兽
	virtual void initMonster();
	//初始化怪兽状态
	void initMstatus(Monster* & m);

	//update 中更新怪兽状态
	void updateMonster(float delta);
	//每一个场景关卡都会有一个碰撞列表
	void initCL();
	
	//更新怪物碰撞列表
	void updateCL();
	//检查玩家和CL中的碰撞
	PandS checkCL(float x1, float y1, int w1, int h1);
	//检查怪和怪的碰撞，这里重载了cheackCL
	PandS checkCL(float x1, float y1, int w1, int h1, std::string monsterName);
	//检查怪和墙的碰撞
	PandS checkWall(float x1, float y1, int w1, int h1);

	//怪物巡逻
	void monsterPatrol(float dt);
	//怪物攻击
	void monsterAttack(float delta);
	/*void monsterPatrol2(float dt);
	void monsterPatrol3(float dt);
	void monsterPatrol4(float dt);*/

	//移动地图元素
	void moveCL(float dx, float dy);

	//更新HUD
	void updateHUD();
	//更新血条
	void updateHP();

	//检查子弹
	void checkBullet();

	//判断关卡结束
	void checkEnd();
	//下一轮
	void nextLevel(float dt);
	//下一关
	virtual void nextScene(float dt);

	//创建传送门
	void createPortal(float dt);
	bool ending = false;

	//写入分数和魂数目
	void write();
	int readScore();
	int readSoulForThisTurn();
	int readSoulForAll();
	void useSoulForAll(int number);

	//魂掉落与获取
	void dropSoul(Vec2 position);
	void getSoul();

	static cocos2d::Scene* createNewScene();

	virtual bool init() override;
	void menuItemCallback(Ref * pSender);

	//here is keyboard scene code from game from scratch.com
	virtual void update(float delta) override;

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);


	void keyEvent(float delta);

	void fire(float dt);

	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;

	CREATE_FUNC(GameStartPage);
};
#endif // __GAMESTARTPAGE_H__
