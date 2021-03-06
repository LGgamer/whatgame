#include "Monster.h"
#include "CollisionTest.h"
#include "RandomList.h"
#include "CollisionList.h"
USING_NS_CC;

Monster::Monster() : Sprite()
{
	//debug();
	isFindEnemy = false;
	isAttack = false;
	BulletNumber = 0;

	attackSpeed = 800;
	scoutRange = 500;
	attackRange = 200;

	health = 100;
	lv = 1;
	gold = 10;
	damage = 10;
	moveSpeed = 100;
	description = std::string("A father monster");
	//texture_path = std::string("HelloMonster.png");
	damage_coefficient = speed_coefficient = attackSpeed_coefficient= health_coefficient = gold_coefficient = 1;
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




int Monster::getAttackRange()
{
	return attackRange;
}

int Monster::getAttackSpeed()
{
	return attackSpeed* attackSpeed_coefficient;
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

void Monster::patrol(Node* player)
{
	if(Monster::isInRange(player->getPosition(), this->getPosition(), this->scoutRange))
	{
		this->isFindEnemy = true;
	}
	else
	{
		const int patrolRange = 50;
		auto cp = this->getPosition();

		int x = random(-1, 1);
		int y = random(-1, 1);
		Vec2 dir = Vec2(x, y);
		this->runAction(MoveTo::create(3, cp + dir * 50));
	}

}

void Monster::attack(Node* sprite, float delta)
{
	auto playerP = sprite->getPosition();

	auto bullet = Sprite::create("Bullet.png");
	bullet->setScale(0.2);
	BulletNumber++;
	log("%d", BulletNumber);
	bullet->setTag(6);
	auto damage = std::to_string(this->getDamage());
	auto str1 = std::to_string(BulletNumber);
	auto str2 = std::string("-bullet");
	auto str = damage + str2 + str1;
	bullet->setName(str);
	//auto sprite = this->getParent()->getChildByTag(1);

	auto startPos = this->getPosition();// - Point(0, this->getContentSize().height / 10);
	auto endPos = startPos + Point(0, -500);

	auto duration = (startPos.y - endPos.y) / this->getAttackSpeed();

	bullet->setPosition(startPos);

	this->getParent()->addChild(bullet);

	auto fire = MoveTo::create(duration, playerP);
	auto remove = RemoveSelf::create();
	bullet->runAction(Sequence::create(fire, remove, NULL));
}

void Monster::behavior(Node* sprite, float delta,PandS hitted)
{
	auto player = sprite;
	//If monster dose not find player
   // If player is in the range of monster's scout range
	if (Monster::isInRange(player->getPosition(), this->getPosition(), this->scoutRange))
	{
		this->isFindEnemy = true;
	}
	if (Monster::isInRange(player->getPosition(), this->getPosition(), this->scoutRange) || this->isFindEnemy)
	{
		// If monster hits the wall they will stop and patrol
		if (hitted.width > 0 && hitted.height > 0)
		{
			if (hitted.name.find("Wall") != std::string::npos)
				this->isFindEnemy = false;


			Vec2 d = this->getPosition() - Vec2(hitted.x, hitted.y);
			this->setPosition(Vec2(this->getPosition().x + d.x / this->moveSpeed, this->getPosition().y + d.y /this->moveSpeed));
		}

		if (Monster::isInRange(player->getPosition(), this->getPosition(), this->attackRange) && this->isFindEnemy)
		{
			this->isAttack = true;
		}
		// If player is in the monster's attack range
		else
		{
			this->isAttack = false;
			// if the monster hits other monsters, they will not move
			/*hitted = checkCL(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width*monster->getScale(), monster->getContentSize().height*monster->getScale(), monster->getName());*/
			if (hitted.width > 0 && hitted.height > 0)
			{
				Vec2 d = this->getPosition() - Vec2(hitted.x, hitted.y);
				this->setPosition(Vec2(this->getPosition().x + d.x / this->moveSpeed, this->getPosition().y + d.y / this->moveSpeed));
			}
			else
				this->move(player, delta);
		}
	}
}

Fly_monster::Fly_monster() : Monster()
{
	scoutRange = 1000;
	attackRange = 700;
	attackSpeed = 200;
}
Fly_monster::~Fly_monster(){}

Fly_monster* Fly_monster::create(const std::string& filename)
{
	Fly_monster *sprite = new (std::nothrow) Fly_monster();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Fly_monster::move(Node* sprite, float delta)
{
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
	{
		
		this->setPosition(cp.x + delta* moveSpeed*cos, cp.y + delta* moveSpeed*sin);
	}
}



void Fly_monster::attack(Node* sprite, float delta)//the fly monster will attack from four dirction
{

	auto playerP = sprite->getPosition();
	auto dp = playerP - this->getPosition();
	auto cp = this->getPosition();

	for (int i = 0; i < 4; i++)
	{
		auto bullet = Sprite::create("Bullet.png");
		bullet->setScale(0.5);
		BulletNumber++;
		log("%d", BulletNumber);
		bullet->setTag(6);
		auto damage = std::to_string(this->getDamage());
		auto str1 = std::to_string(BulletNumber);
		auto str2 = std::string("-bullet");
		auto str = damage + str2 + str1;
		bullet->setName(str);

		Vec2 startPos;
		Vec2 endPos;
		float duration;
		MoveTo* fire;
		auto remove = RemoveSelf::create();
		if (i == 0)//up
		{
			startPos = this->getPosition() + Vec2(0, 0.5*this->getContentSize().height);

			endPos = startPos + Vec2(0, this->getAttackRange());

			duration = (fabs(startPos.y - endPos.y)) / this->getAttackSpeed();

			bullet->setPosition(startPos);

			this->getParent()->addChild(bullet);

			fire = MoveTo::create(duration, endPos);
				
			bullet->runAction(Sequence::create(fire, remove, NULL));
		}
		else if (i == 1)//down
		{
			startPos = this->getPosition() - Vec2(0, 0.5*this->getContentSize().height);

			endPos = startPos + Vec2(0, -this->getAttackRange());

			duration = fabs((startPos.y - endPos.y)) / this->getAttackSpeed();

			bullet->setPosition(startPos);

			this->getParent()->addChild(bullet);

			fire = MoveTo::create(duration, endPos);

			bullet->runAction(Sequence::create(fire, remove, NULL));
		}
		else if (i == 2)//left
		{
			startPos = this->getPosition() - Vec2(0.5*this->getContentSize().width,0);

			endPos = startPos + Vec2(-this->getAttackRange(), 0);

			duration = fabs((startPos.x - endPos.x)) / this->getAttackSpeed();

			bullet->setPosition(startPos);

			this->getParent()->addChild(bullet);

			fire = MoveTo::create(duration, endPos);

			bullet->runAction(Sequence::create(fire, remove, NULL));
		}
		else if (i == 3)
		{
			startPos = this->getPosition() + Vec2(0.5*this->getContentSize().width,0);

			endPos = startPos + Vec2(this->getAttackRange(), 0);

			duration = fabs((startPos.x - endPos.x)) / this->getAttackSpeed();

			bullet->setPosition(startPos);

			this->getParent()->addChild(bullet);

			fire = MoveTo::create(duration, endPos);

			bullet->runAction(Sequence::create(fire, remove, NULL));
		}
	}
}

void Fly_monster::behavior(Node* sprite, float delta, PandS hitted)
{
	auto player = sprite;
	auto dp = player->getPosition() - this->getPosition();
	auto cp = this->getPosition();
	//If monster dose not find player
	// If player is in the range of monster's scout range
	if (Monster::isInRange(player->getPosition(), this->getPosition(), this->scoutRange))
	{
		this->isFindEnemy = true;
	}
	if (Monster::isInRange(player->getPosition(), this->getPosition(), this->scoutRange) || this->isFindEnemy)
	{
		// If monster hits the wall they will stop and patrol
		if (hitted.width > 0 && hitted.height > 0)
		{
			if (hitted.name.find("Wall") != std::string::npos)
				this->isFindEnemy = false;
			Vec2 d = this->getPosition() - Vec2(hitted.x, hitted.y);
			this->setPosition(Vec2(this->getPosition().x + d.x / this->moveSpeed, this->getPosition().y + d.y / this->moveSpeed));
		}

		if (Monster::isInRange(player->getPosition(), this->getPosition(), this->attackRange) && this->isFindEnemy)
		{
			if (fabs(dp.y) > this->getContentSize().height*0.5 && fabs(dp.y) > this->getContentSize().width*0.5)
			{
				if (fabs(dp.y) > fabs(dp.x))
				{
					int dir = dp.x / fabs(dp.x);
					this->setPosition(cp.x + delta* moveSpeed*dir, cp.y);
				}
				else
				{
					int dir = dp.y / fabs(dp.y);
					this->setPosition(cp.x, cp.y + delta* moveSpeed*dir);
				}
			}
			else
				this->isAttack = true;
		}
		// If player is in the monster's attack range
		else
		{
			this->isAttack = false;
			// if the monster hits other monsters, they will not move
			if (hitted.width > 0 && hitted.height > 0)
			{
				Vec2 d = this->getPosition() - Vec2(hitted.x, hitted.y);
				this->setPosition(Vec2(this->getPosition().x + d.x / this->moveSpeed, this->getPosition().y + d.y / this->moveSpeed));
			}
			else
				this->move(player, delta);
		}
	}
}