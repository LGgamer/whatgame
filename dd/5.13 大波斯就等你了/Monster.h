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
	int damage_coefficient, speed_coefficient, health_coefficient, gold_coefficient, attackSpeed_coefficient;
	std::string description;
	std::vector<std::string> itemList;

public:
	static bool isInRange(Vec2 player,Vec2 monster, int range);
	void patrol(Node* player);
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
};

//#include <iostream>
//#include <list>

/*

Root
|
|
Selector (only one of these children need to succeed)
/             \
/               \
/                 \
Door is open?      Sequence (all of these children need to succeed)
(if door is                /           \
already open,             /             \
we are done)             /               \
Approach door      Open the door
(if this fails
then the door
cannot be opened)
*/
#if 0
class BNode
{  // This class represents each node in the behaviour tree.
public:
	virtual bool run() = 0;
};

class CompositeNode : public BNode
{  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
private:
	std::list<BNode*> children;
public:
	const std::list<BNode*>& getChildren() const { return children; }
	void addChild(BNode* child) { children.emplace_back(child); }
};

class Selector : public CompositeNode
{
public:
	virtual bool run() override
	{
		for (BNode* child : getChildren())
		{  // The generic Selector implementation
			if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
				return true;
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};

class Sequence : public CompositeNode
{
public:
	virtual bool run() override
	{
		for (BNode* child : getChildren())
		{  // The generic Sequence implementation.
			if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
				return false;
		}
		return true;  // All children suceeded, so the entire run() operation succeeds.
	}
};
#endif

#endif // !__MONSTER_H_
