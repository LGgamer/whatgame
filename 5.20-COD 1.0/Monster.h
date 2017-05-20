#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "cocos2d.h"
#include "CollisionList.h"
USING_NS_CC;

void debug();

class Monster : public cocos2d::Sprite
{
public:
	static Monster* create(const std::string& filename);
	Monster();
	~Monster();
	int getLv();
	int getHealth();
	int getScoutRange();
	int getAttackRange();
	int getAttackSpeed();
	int getMoveSpeed();
	int getGold();
	int getDamage();
	int getScore();
	std::vector<std::string> getItemList();
public:
	bool isFindEnemy;
	bool isAttack;
	int BulletNumber;


	int lv;
	int health;
	int scoutRange;
	int attackRange;
	int attackSpeed;
	int moveSpeed;
	int gold;
	int damage;
	int score;
	int damage_coefficient, speed_coefficient, health_coefficient, gold_coefficient, attackSpeed_coefficient;
	std::string description;
	std::vector<std::string> itemList;

public:
	static bool isInRange(Vec2 player,Vec2 monster, int range);
	static bool isDropItem(float prob);

	void patrol(Node* player , Vec2 screenO);
	virtual void move(Node* sprite, float delta);
	virtual void attack(Node* sprite, float delta);
	virtual void behavior(Node* sprite, float delta,PandS hitted);
	
};

class Fly_monster :public Monster
{
public:
	Fly_monster();
	~Fly_monster();
	static Fly_monster* create(const std::string& filename);

	void move(Node* sprite, float delta) override;
	virtual void attack(Node* sprite, float delta) override;
	void behavior(Node* sprite, float delta, PandS hitted) override;
};

class Boss_monster :public Monster
{
public:
	Boss_monster();
	~Boss_monster();
	static Boss_monster* create(const std::string& filename);

	//void move(Node* sprite, float delta) override;
	virtual void attack(Node* sprite, float delta) override;
	void behavior(Node* sprite, float delta, PandS hitted) override;
};

#endif // !__MONSTER_H_
