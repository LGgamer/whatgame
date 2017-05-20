#ifndef _TESTSTARTPAGE_H_
#define _TESTSTARTPAGE_H_

#include "cocos2d.h"
#include "CollisionList.h"
#include "character.h"
#include "Monster.h"
#include "HUDLayer.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

//#include "SceneManager.h"

class GameStartPage : public cocos2d::Layer
{
public:
	//global variable for knowing wheter the user turned off the music
	bool isEffect = UserDefault::getInstance()->getBoolForKey("isEffect");
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
	int soulNumberInMap;
	//number of bullet
	int BulletNumber;
	//numver of box
	int boxNumber;

	CollisonList cl;
	cocos2d::Point screenO;
	//character maincharacter;
	HUDLayer* hud;

	character* sprite;
	int MAXhealth;
	//auto bg;
//	Sprite* sprite;
public:

	//add score
	void updateScore();
	int getScore(int number);

	//initialize walls
	void initWall();
	//initialize treasure boxes 
	void initBox();
	//initialize monsters
	virtual void initMonster();

	//update monster status
	void updateMonster(float delta);
	//basically every scene has a collision list
	void initCL();
	
	//delay
	void delay(float dt);

	//update the collision list
	void updateCL();
	//check player collide with the staff in the collision list
	PandS checkCL(float x1, float y1, int w1, int h1);
	//check the monster collision status by overriding cheackCL
	PandS checkCL(float x1, float y1, int w1, int h1, std::string monsterName);
	//check the collision between the monsters and walls
	PandS checkWall(float x1, float y1, int w1, int h1);

	//patrol path of monsters
	void monsterPatrol(float dt);
	//attack of monsters
	void monsterAttack(float delta);


	//move the elements on the map
	void moveCL(float dx, float dy);

	//update the HUD
	void updateHUD();
	//update health points
	void updateHP();

	//check bullets
	virtual void checkBullet();

	//judge wheter this scene reaches an end
	virtual void checkEnd();
	//next round
	void nextLevel(float dt);
	//a new stage of game
	virtual void nextScene(float dt);

	//create a portal for next stage
	void createPortal(float dt);

	//record the score and the soul number
	void write();
	int readScore();
	int readSoul();

	//the soul dropping and taking
	void dropSoul(Vec2 position);

	//the dropping of buffs
	void dropBuff(Vec2 pos);

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
