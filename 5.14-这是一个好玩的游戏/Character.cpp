#include "Character.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cocos2d.h"

USING_NS_CC;

character::character() {

	live = true;

	basic_health = 100;
	level = 1;
	gold = 0;
	basic_attack = 10;
	basic_defence = 5;
	basic_speed = 100;
	attack_coefficient = defence_coefficient = speed_coefficient = health_coefficient = gold_coefficient = 1.0;

	BulletNumber = 0;
	attackSpeed = 1000;
	attackRange = 500;
	attackM = 1;
}

character* character::create(const std::string& filename)
{
	character *sprite = new (std::nothrow) character();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

character::~character() {

}

int character::get_max_health() {
	return level * health_coefficient * 100;
}

int character::get_current_health() {
	return basic_health;
}

int character::get_attack() {
	return level * attack_coefficient * basic_attack;
	// related with strength
}

int character::get_defence() {
	return level * defence_coefficient * basic_defence;
}

int character::get_strength() {
	return level * strength_coefficient * basic_strength;
}

int character::get_agility() {
	return level * agility_coefficient * basic_agility;
}

int character::get_speed() {
	return level * speed_coefficient * basic_speed;
}

int character::get_experience() {
	return experience;
}

int character::get_gold() {
	return gold;
}

void character::HpDown(int point) {

    if ( basic_health >= point && godlike == false ) {
        injureTime = std::time(nullptr);
        basic_health = basic_health - point;
        auto blink = Blink::create(1.2f, 10);
        this->runAction(blink);
    }else if ( basic_health >= point && godlike == true ) {
        auto current_time = std::time(nullptr);
        if ( current_time - injureTime >= 1.5 ) {
            basic_health = basic_health - point;
        }
    } 
    if ( basic_health <= point ){
        basic_health = 0;
        live = false;
    }
}

bool character::stillalive() {
	if (live == true) {
		return true;
	}
	else {
		return false;
	}
}

void character::attack_up(int points) {
	basic_attack = basic_attack + points;
}

void character::speed_up(int points) {
	basic_speed = basic_speed + points;
}

int character::getAttackRange()
{
	return attackRange;
}

int character::getAttackSpeed()
{
	return attackSpeed;
}

void character::fire1(Vec2 dp)
{
	float cos = dp.x / sqrt(pow(dp.x, 2) + pow(dp.y, 2));
	float sin = dp.y / sqrt(pow(dp.x, 2) + pow(dp.y, 2));

	auto bullet = Sprite::create("playerBullet.png");
	bullet->setScale(0.2);
	BulletNumber++;
	bullet->setTag(5);
	auto str1 = std::to_string(BulletNumber);
	auto str2 = std::string("bullet");
	auto str = str2 + str1;
	bullet->setName(str);

	auto startPos = this->getPosition() + dp;
	auto endPos = startPos + Vec2(this->getAttackRange()*cos, this->getAttackRange()*sin);

	auto intv = startPos - endPos;
	auto d = sqrt(pow(intv.x, 2) + pow(intv.y, 2));

	auto duration = d / this->getAttackSpeed();

	bullet->setPosition(startPos);

	this->getParent()->addChild(bullet);

	auto fire = MoveTo::create(duration, endPos);
	auto remove = RemoveSelf::create();
	bullet->runAction(Sequence::create(fire, remove, NULL));
}

void character::fire2(Vec2 dp)
{
	fire1(dp);
	if (fabs(dp.y) > fabs(dp.x))
	{
		fire1(dp + Vec2(20, 0));
		fire1(dp - Vec2(20, 0));
	}
	else
	{
		fire1(dp + Vec2(0, 20));
		fire1(dp - Vec2(0, 20));
	}
}