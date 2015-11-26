#ifndef ENEMY_H
#define ENEMY_H

#include "main.h"
#include "weapon.h"
#include "vector.h"

#define ENEMY_DEFAULT_HEALTH 10
#define ENEMY_MAX_HEALTH  1000
#define ENEMY_MIN_HEALTH  100

#define ENEMY_PROT_SOLDIER      0
#define ENEMY_PROT_BIG          1
#define ENEMY_PROT_BOX          2
#define ENEMY_PROT_SMALL        3

#define MAX_ENEMY_PROT          4

#define DEFAULT_SPAWN_ENEMY_LENGHT 450.0

#define SIZE_BOX        24
#define DEFAULT_BOX_ENERGY 300


class Box
{
public:
    Box();
    bool    is_active;
    Vector<double> position;
    int     energy;
    Sprite* sprite;

    void    Spawn(Vector<double> pos, int _energy);
    void    Delete();

    Vector2f GetPosition();
};

class EnemyPrototype
{
public:
    EnemyPrototype();
    void        SetParam(int max_health, int max_shield, WeaponTemp*  _weapon, Sprite* _sprite, int _size, int _reward, bool _loot);
    WeaponTemp*      weapon;
    int         health;
    int         shield;
    int         accuracy;
    int         reaction;
    int         size;
    int         reward;
    bool        loot;
    Sprite*      sprite;
};

class Enemy
{
public:
    Enemy();
    void        SetPosition(const Vector<double>*);
    void        SetPosition(int, int);
    void        SetView(const Vector<double>*);
    void        SetView(const Vector2i);
    void        SetView(const Vector2f);
    void        SetView(int, int);

    Vector2f    GetPosition();
    Vector2f    GetView();
    double      GetRotation();
    double      GetSpeed();
    Vector2f    GetInertia(double);

    //void        Spawn(WeaponTemp* _weapon);
    void        Spawn(EnemyPrototype* _enemy_prot, Vector<int> pos);
    void        Destruct();
    void        SetParam(int max_health, int max_shield);

    void        SetMove(Vector<double>, bool);
    void        Move();

    bool        is_alive;
    Weapon      weapon;
    int         health[2];
    int         shield[2];

    int         accuracy;

    int         reaction;
    Sprite      sprite;

    int         size;
    int         reward;
    bool        loot;
private:
    Vector<double>  position;
    Vector<double>  view;
    Vector<double>  inertia;

};



#endif // ENEMY_H
