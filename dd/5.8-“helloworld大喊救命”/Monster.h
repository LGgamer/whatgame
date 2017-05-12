#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "cocos2d.h"
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
	int getMoveSpeed();
	int getGold();
	int getDamage();
	std::vector<std::string> getItemList();
public:
	bool isFindEnemy;
	int lv;
	int health;
	int scoutRange;
	int attackRange;
	int moveSpeed;
	int gold;
	int damage;
	int damage_coefficient, speed_coefficient, health_coefficient, gold_coefficient;
	std::string description;
	std::vector<std::string> itemList;

public:
	static bool isInRange(Vec2 player,Vec2 monster, int range);
//	virtual void patrol();
	void move(Node* sprite, float delta);
//	virtual void attack();
};

class fly_monster :public Monster
{
public:
	fly_monster(int lv = 1);
	~fly_monster();

};

class walk_monster :public Monster
{
public:
	walk_monster(int lv = 1);
	~walk_monster();
};

#include <iostream>
#include <list>

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
