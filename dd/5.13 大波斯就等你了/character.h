#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include "cocos2d.h"

class character : public cocos2d::Sprite
{
public:
	static character* create(const std::string& filename);
	character();
	~character();
	int get_current_health();
	int get_max_health();
	int get_attack();
	int get_defence();
	int get_strength();
	int get_agility();
	int get_experience();
	int get_gold();
	//int level_up();
	void attack_up(int points);
	void speed_up(int points);

	int get_speed();
	void HpDown(int point);
	void setHp(int point);
	bool stillalive();
	bool godlike = false;
	time_t injureTime = 0;
	double attack_coefficient, defence_coefficient, strength_coefficient, agility_coefficient;
	double experience_coefficient, coins_coefficient, speed_coefficient;
	double health_coefficient, gold_coefficient;

private:
	int basic_health;
	int basic_attack;
	int basic_defence;
	int basic_strength;
	int basic_agility;
	int experience;
	int gold;
	int level;
	int basic_speed;
	bool live;
};

#endif
