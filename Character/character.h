#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>

void debug();

class player{

public:
    player();
    ~player();
    int get_health();
    int get_attack();
    int get_defence();
    int get_strength();
    int get_agility();
    int get_experience();
    int get_coins();
    int level_up();
    int get_speed();

    int health;
    int attack, defence;
    int strength, agility;
    int experience,coins, level;
    int speed;
    //int shape_size;
    //virtual void move_way();
    std::string texture_path;
    double attack_coefficient, defence_coefficient, strength_coefficient, agility_coefficient;
    double experience_coefficient, coins_coefficient;

private:
    int basic_health;
    int basic_attack;
    int basic_defence;
    int basic strength;
    int basic_agility;
    int basic_experience;
    int basic_gold;
    int basic_experience;
    int basic_level;
    int basic_speed;

};


#endif // CHARACTER_H
