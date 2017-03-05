#include <iostream>
#include <string>

class Player{
public :

    //Buff
    int get_Hp(int number);
    int get_Attack(int number);
    int get_Defence(int number);
    int get_Strength(int number);
    int get_Agility(int number);
    int get_Experience(int number);
    int get_coins(int number);
    int Level_up();
    int get_Speed(int number);

    //Debuff
    int Lose_Hp(int number);
    int injure(int number);
    int Lose_Attack(int number);
    int Lose_Defence(int number);
    int Lose_Strength(int number);
    int Lose_Agility(int number);
    int Lose_Speed(int number);
    int Lose_coins(int number);

    //Movement
    int move_to_left(int measure);
    int move_to_right(int measure);
    int attack();
    int roll();
    int useItem();


private:

    int Hp =50;
    int Attack = Strength*0.7 + 5;
    int Defence=Strength*0.5 + 5;
    int Strength=5;
    int Agility=5;
    int Experience=0;
    int coins=0;
    int Level=1;
    int Speed = Strength*(0.4) + Agility*(0.6);
    int x,y;
    string texture_path;



};

//Increasing

int Player::get_Hp(int number){
    Hp = Hp + number;
    return Hp;
}

int Player::get_Attack(int number){
    Attack = Attack + number;
    return Attack;
}

int Player::get_Defence(int number){
    Defence = Defence + number;
    return Defence;
}

int Player::get_Agility(int number) {
    Agility = Agility + number;
    return Agility;
}

int Player::get_Strength(int number) {
    Strength = Strength + number;
    return Strength;
}

int Player::get_Experience(int number) {
    Experience = Experience + number;
    return Experience;
}

int Player::get_coins(int measure){
    coins = coins + number;
    return coins;
}

int Player::Level_up() {
    Level = Level + 1;
    return Level;
}

int Player::get_Speed(int number){
    Speed = Speed + number;
    return Speed;
}

int Player::Lose_Hp(int number) {
    Hp = Hp - number;
    return Hp;
}



//Decreasing

int Player::Lose_Attack(int measure) {
    Attack = Attack - measure;
    return Attack;
}

int Player::Lose_Defence(int measure) {
    Defence = Defence - measure;
    return Defence;
}

int Player::Lose_Strength(int measure) {
    Strength = Strength - measure;
    return Strength;
}

int Player::Lose_Agility(int measure) {
    Agility = Agility - measure;
    return Agility;
}

int Player::Lose_Speed(int measure) {
    Speed = Speed - measure;
    return Speed;
}

int Player::Lose_coins(int measure) {
    coins = coins - measure;
    return coins;
}


//Movement
int move_to_left(int measure){

}

int move_to_right(int measure){

}

int attack(){

}

int roll(){

}

int useItem(){

}

int injure(int number){
    Hp = Hp - (number * (Defence * 0.3);
    return Hp;
}

