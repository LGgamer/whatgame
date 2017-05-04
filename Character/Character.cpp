#include "character.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

character::character(){

    basic_health = 10;
    level = 1;
    gold = 0;
    basic_attack = 10;
    basic_defence = 5;
    basic_speed = 100;
    attack_coefficient = defence_coefficient = speed_coefficient = health_coefficient = gold_coefficient = 1.0;
}

character::~character() {
    
}

int character::get_health(){
    return level * health_coefficient * basic_health;
}

int character::get_attack(){
    return level * attack_coefficient * basic_attack;
    // related with strength
}

int character::get_defence(){
    return level * defence_coefficient * basic_defence;
}

int character::get_strength(){
    return level * strength_coefficient * basic_strength;
}

int character::get_agility() {
    return level * agility_coefficient * basic_agility;
}

 int character::get_speed(){
    return level * speed_coefficient * basic_speed;
}

int character::get_experience(){
    return experience;
}

int character::get_gold(){
    return gold;
}
