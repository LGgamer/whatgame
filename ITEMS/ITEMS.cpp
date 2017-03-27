//
//  ITEMS.cpp
//  
//
//  Created by Feiyang Wu on 05/03/2017.
//
//

#include "ITEMS.h"
#include <iostream>
#include <string>
#include <stdio.h>

std::string Items::getItemTag(){
    return item_tag;
}

//buff 
buffItem::buffItem(int degree){
    basic_buffDegree=1;
};

int buffItem::getDegree(){
    return basic_buffDegree*degree;
}

std::string buffItem::get_buffTag(){
    if(degree==1){
        return "small";
    }else if(degree == 2 ){
        return "medium";
    }else if (degree==3){
        return "large";
    }else if (degree==4){
        return "extra large";
    }else{
        return "none";
    }
}

//heals
healingMedicine::healingMedicine(int deg){
    debug();
    degree=deg;
    basic_healingPercentage=25;
}

healingMedicine::~healingMedicine(){
}

int healingMedicine::get_precentage(){
    if (degree<=4){
    return basic_healingPercentage*degree;
    }else {
        return basic_healingPercentage*4;
    }
}


//moving fast
movingFast::movingFast(int deg){
    debug();
    degree=deg;
    basic_speedUpPoints=10;
}

movingFast::~movingFast(){

}

int movingFast::get_SpeedPercentage(){
    if (degree<=4){
        return basic_speedUpPoints*degree;
    }else {
        return basic_speedUpPoints*4;
    }
}


//add attack points
attackUp::attackUp(int deg){
    debug();
    degree=deg;
    basic_extraAttackPoints=50;
}

attackUp::~attackUp(){
    
}

int attackUp::get_ExtraAttack(){
    if (degree<=4) {
        return basic_extraAttackPoints*degree;
    }else{
        return basic_extraAttackPoints;
    }
}

//shields up up !!
shieldUp::shieldUp(int deg){
    debug();
    degree=deg;
    basic_extraShieldPoints=50;
}

shieldUp::~shieldUp(){
    
}

int shieldUp::get_ExtraShield(){
    if (degree<=4) {
        return basic_extraShieldPoints*degree;
    } else {
        return basic_extraShieldPoints;
    }
}

//weapons
weapons::weapons(){
    basic_attackSpeed=10;
    basic_attackPoints=100;
    basic_attackArrange=50;
    extra_AttackPoints=1;
    extra_AttackSpeed=1;
    extra_AttackArrange=1;
    weaponName="unnamed weapon";
}

weapons::~weapons(){
    
}

int weapons::getAttackPoints(){
    return extra_AttackPoints*basic_attackPoints;
}

int weapons::getAttackSpeed(){
    return extra_AttackSpeed*basic_attackSpeed;
}

int weapons::getAttackArrange(){
    return extra_AttackArrange*basic_attackArrange;
}

std:: string weapons::getWeaponName(){
    return weaponName;
}

//blade is a type of weapon with high attack points, medium attack speed, and small attack arrange.
blade::blade(){
    extra_AttackPoints=4;
    extra_AttackSpeed=3;
    extra_AttackArrange=2;
}

blade::~blade(){
    
}



//arrow is a type of weapon with normal attack points, high attack speed, and broad attack arrange.
arrow::arrow(){
    extra_AttackPoints=3;
    extra_AttackSpeed=4;
    extra_AttackArrange=4;
}

arrow::~arrow(){
    
}

//handgun is a type of weapon with high attack points, low attack speed, and highest attack arrange;
handgun::handgun(){
    extra_AttackPoints=4;
    extra_AttackSpeed=2;
    extra_AttackArrange=5;
}

handgun::~handgun(){
    
}

//axes is a type of weapon with highest attack points, low attack speed, and smallest attack arrange.
axes::axes(){
    extra_AttackPoints=5;
    extra_AttackSpeed=2;
    extra_AttackArrange=1;
}

axes::~axes(){
    
}

//laserBeam is a type of weapon with normal attack points, highest attack speed, and high attack arrange.
laserBeam::laserBeam(){
    extra_AttackPoints=3;
    extra_AttackSpeed=5;
    extra_AttackArrange=4;
}

laserBeam::~laserBeam(){
    
}

//rocket is a type of weapon with highest attack points, lowest attack speed, and highest attack arrange.
rocket::rocket(){
    extra_AttackPoints=5;
    extra_AttackSpeed=1;
    extra_AttackSpeed=5;
}

rocket::~rocket(){
    
}





