#ifndef _monster_h
#define _monster_h

#include<string>

void debug();

class monster{

public:
    monster();
    ~monster();
    int get_health();
    int get_defense();
    int get_attack();
    int get_speed();
    int get_gold();
    int level, health, attack, defense, speed;
    //int shape_size;
    //virtual void move_way();
    std::string description;
    std::string texture_path;
    double attack_coefficient, defense_coefficient, speed_coefficient, health_coefficient, gold_coefficient;

private:
    int basic_health;
    int basic_gold;
    int basic_attack, basic_defense, basic_speed;
};

class fly_monster:public monster{
public:
    fly_monster(int lv = 1);
    ~fly_monster();

};

class walk_monster:public monster{
public:
    walk_monster(int lv = 1);
    ~walk_monster();
};

#endif // _monster_h
