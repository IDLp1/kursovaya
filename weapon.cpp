#include "main.h"
#include "weapon.h"

Weapon::Weapon()
{
    is_exist = false;
    damage[MIN] = 0;
    damage[MAX] = 0;
    accuracy = 0.0;
    time_reload = 0;
    condition[MAX] = 0;
    condition[CURRENT] = condition[MAX];
    is_reload = false;
    //clock_reload.restart();
    speed_bullet = 0.0;
}

Weapon::~Weapon()
{

}

WeaponTemp::WeaponTemp()
{
    accuracy = 0.0;
    time_reload = 0;
    damage[MIN] = 0;
    damage[MAX] = 0;
    condition = 0;
    time_life_bullet = 0;
    speed_bullet = 0.0;
}
void WeaponTemp::SetParam(Sprite* _sprite_bullet, Sound* _sound, Color _bullet_color, int set_min_damage, int set_max_damage,
                          double set_accuracy, int set_tr, int set_max_condition, int tlb, double speed, int _expense)
{
    damage[MIN] = set_min_damage;
    damage[MAX] = set_max_damage;
    accuracy = set_accuracy;
    time_reload = set_tr;
    condition = set_max_condition;

    time_life_bullet = tlb;

    speed_bullet = speed;
    sprite_bullet = _sprite_bullet;
    sound = _sound;
    expense = _expense;

    bullet_color.r = _bullet_color.r;
    bullet_color.g = _bullet_color.g;
    bullet_color.b = _bullet_color.b;
    bullet_color.a = _bullet_color.a;

}


void WeaponTemp::SetWeapon(Weapon *weapon)
{
    weapon->is_exist = true;
    weapon->accuracy = this->accuracy;

    weapon->condition[MAX] = this->condition;
    weapon->condition[CURRENT] = weapon->condition[MAX];
    weapon->damage[MAX] = this->damage[MAX];
    weapon->damage[MIN] = this->damage[MIN];
    weapon->speed_bullet = this->speed_bullet;
    weapon->time_life_bullet = this->time_life_bullet;
    weapon->time_reload = this->time_reload;
    weapon->clock_reload.restart();
    weapon->sprite_bullet = this->sprite_bullet;
    weapon->sound = this->sound;
    weapon->expense = this->expense;
    weapon->bullet_color.a = bullet_color.a;
    weapon->bullet_color.r = bullet_color.r;
    weapon->bullet_color.g = bullet_color.g;
    weapon->bullet_color.b = bullet_color.b;
}

WeaponTemp::~WeaponTemp()
{

}
