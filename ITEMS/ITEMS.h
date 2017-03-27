//
//  ITEMS.h
//  itemstest
//
//  Created by Feiyang Wu on 05/03/2017.
//  Copyright © 2017 Feiyang Wu. All rights reserved.
//

#ifndef ITEMS_h
#define ITEMS_h

#include <stdio.h>
#include <string>

void debug();

class Items {
public:
    Items();
    ~Items();
    std::string getItemTag();
private:
    std::string item_tag;  //showing the figure has "buff", "debuff" or "weapon"
};

//buff
class buffItem : public Items {
public:
    buffItem(int degree=1);
    ~buffItem();
    int degree;
    int getDegree();
    std::string get_buffTag();
private:
    int basic_buffDegree;
};

//heals
class healingMedicine: buffItem{
public:
    healingMedicine(int deg=1);
    ~healingMedicine();
    void addHP();
    int get_precentage();
private:
    int basic_healingPercentage;
};

//move faster
class movingFast:buffItem{
public:
    movingFast(int deg=1);
    ~movingFast();
    void addMovingSpeed();
    int get_SpeedPercentage();
    int currentSpeed;
private:
    int basic_speedUpPoints;
};

//attack up!
class attackUp:buffItem{
public:
    attackUp(int deg=1);
    ~attackUp();
    void addAttackPoints();
    int get_ExtraAttack();
private:
    int basic_extraAttackPoints;
};

// shields up!
class shieldUp:buffItem{
public:
    shieldUp(int deg=1);
    ~shieldUp();
    void addShieldPoints();
    int get_ExtraShield();
private:
    int basic_extraShieldPoints;
};

//weapons
class weapons:Items{
public:
    weapons();
    ~weapons();
    std::string getWeaponName();
    int getAttackPoints();
    int getAttackSpeed();
    int getAttackArrange();
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
private:
    std::string weaponName;
    int basic_attackPoints;
    int basic_attackSpeed;
    int basic_attackArrange;
};

class blade:weapons {
public:
    blade();
    ~blade();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};

class arrow:weapons {
public:
    arrow();
    ~arrow();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};

class handgun:weapons{
public:
    handgun();
    ~handgun();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};

class axes:weapons{
public:
    axes();
    ~axes();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};

class laserBeam:weapons{
public:
    laserBeam();
    ~laserBeam();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};

class rocket:weapons{
public:
    rocket();
    ~rocket();
private:
    int extra_AttackPoints;
    int extra_AttackSpeed;
    int extra_AttackArrange;
};





#endif /* ITEMS_h */
