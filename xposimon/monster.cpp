#include "monster.h"
#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>


monster::monster(){
    debug();
    basic_health = 100;
    level = 1;
    basic_gold = 10;
    basic_attack = 10;
    basic_defense = 5;
    basic_speed = 100;
    description = std::string("A father monster");
    texture_path = std::string("HelloMonster.png");
    attack_coefficient = defense_coefficient = speed_coefficient = health_coefficient = gold_coefficient = 1.0;
}

monster::~monster(){
}

int monster::get_health(){
    return level * health_coefficient * basic_health;
}

int monster::get_attack(){
    return level * attack_coefficient * basic_attack;
}

int monster::get_defense(){
    return level * defense_coefficient * basic_defense;
}

int monster::get_speed(){
    return level * speed_coefficient * basic_speed;
}

int monster::get_gold(){
    srand((unsigned)time(NULL));
    return (rand()% basic_gold + basic_gold/2) * gold_coefficient;
}

fly_monster::fly_monster(int lv){
    level = lv;
    attack_coefficient = 0.3;
    speed_coefficient = 4.0;
    defense_coefficient = 0.5;
    health_coefficient = 0.7;
    description = string("A kind of fly monsters.")
    health = get_health();
    attack = get_attack();
    defense = get_defense();
    speed = get_speed();
}

fly_monster::~fly_monster(){
}

walk_monster::walk_monster(int lv){
    level = lv;
    attack_coefficient = 2.0;
    speed_coefficient = 0.7;
    defense_coefficient = 1.3;
    health_coefficient = 1.5;
    description = string("A kind of walk monster.")
    health = get_health();
    attack = get_attack();
    defense = get_defense();
    speed = get_speed();
}

walk_monster::~walk_monster(){
}

int main(){
    fly_monster a(2);
    std::cout<<a.level<<" "<<a.health<<" "<<a.attack<<" "<<a.defense<<" "<<a.speed;
}
