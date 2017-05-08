#include "Monster.h"
#include "CollisionTest.h"
USING_NS_CC;

Monster::Monster() : Sprite()
{
	//debug();
	isFindEnemy = false;
	health = 100;
	lv = 1;
	gold = 10;
	damage = 10;
	moveSpeed = 100;
	description = std::string("A father monster");
	//texture_path = std::string("HelloMonster.png");
	damage_coefficient = speed_coefficient = health_coefficient = gold_coefficient = 1;
}

Monster* Monster::create(const std::string& filename)
{
	Monster *sprite = new (std::nothrow) Monster();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Monster::~Monster() {
}

int Monster::getHealth() {
	return health * lv * health_coefficient;
}

int Monster::getDamage() {
	return damage * lv * damage_coefficient;
}

int Monster::getMoveSpeed() {
	return moveSpeed * lv * speed_coefficient;
}

int Monster::getGold() {
	srand((unsigned)time(NULL));
	return (rand() % gold + gold / 2) * gold_coefficient;
}

bool Monster::isInRange(Vec2 player, Vec2 monster, int range)
{
	//this->gold = 2;
	Vec2 delta = player - monster;
	float distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	if (distance <= range)
		return true;
	else
		return false;
}

void Monster::move(Node* sprite,float delta)
{

	//this->runAction(MoveTo::create(5,player));
	auto playerP = sprite->getPosition();
	auto playerS = sprite->getContentSize();
	int pwith = sprite->getScale()*playerS.width;
	int pheig = playerS.height*sprite->getScale();

	auto cp = this->getPosition();
	Vec2 dp = playerP - cp;
	float cos = dp.x / sqrt(pow(dp.x, 2) + pow(dp.y, 2));
	float sin = dp.y / sqrt(pow(dp.x, 2) + pow(dp.y, 2));
	if (CollisionTest::isCollision(playerP.x, playerP.y, pwith, pheig, cp.x, cp.y, this->getContentSize().width * this->getScale(), this->getContentSize().height * this->getScale()))
		;
	else
		this->setPosition(cp.x + delta* moveSpeed*cos, cp.y + delta* moveSpeed*sin);

}