#ifndef WEAPON_H
#define WEAPON_H
#include "main.h"

class Weapon //Класс оружия
{
public:
    Weapon();
    //Weapon(int min_damage, int max_damage, double accuracy, int time_r, int max_condition);
    ~Weapon();

    void    SetParam(Sprite* _sprite_bullet, Sound* _sound, int min_damage, int max_damage, double accuracy, int time_r, int max_condition, int tlb, double speed, int _expense);
    bool    is_exist;
    bool    is_reload;
    double  accuracy;
    int     time_reload;
    int     damage[2];
    int     condition[2];
    int     time_life_bullet;
    Clock   clock_reload;
    double  speed_bullet;
    int     expense;
    Sprite* sprite_bullet;
    Sound*  sound;
    Color   bullet_color;

};

class WeaponTemp
{
public:
    WeaponTemp();
    ~WeaponTemp();
    void    SetParam(Sprite* _sprite_bullet, Sound* _sound, Color _bullet_color, int min_damage, int max_damage, double accuracy, int time_r, int max_condition, int tlb, double speed, int _expense);
    void    SetWeapon(Weapon* weapon);
    double  accuracy;
    int     time_reload;
    int     damage[2];
    int     condition;
    int     time_life_bullet;
    //Clock   clock_reload;
    double  speed_bullet;
    int     expense;
    Sprite* sprite_bullet;
    Sound*  sound;
    Color bullet_color;
};

#endif // WEAPON_H
