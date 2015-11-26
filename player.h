#ifndef PLAYER_H
#define PLAYER_H



#define DEFAULT_MAX_HEALTH  100 // макс. здоровье
#define DEFAULT_MAX_SHEILD  50 // щит
#define DEFAULT_MAX_ENERGY  1000 // макс. энергия
#define DEFAULT_SHIELD_PROT 30 // защита щита от урона
#define DEFAULT_GIVE_SCORE  10
#define BONUS_TIME          1750

#define PLAYER_DIM  64.0 // "габариты" игрока
#define SHIELD_R    40.0 // радиус щита

#include "main.h"
#include "vector.h"
#include "weapon.h"


using namespace sf;

//константы игровой физики
const double deceleration = 0.25; // торможение
const double inertia_bp = 0.25; //минимальная инерция, после которого тело игрока останавливаеться полностью
const double max_inertion = 10.0; //максимальная допустимая инерция


class Engine
{
public:
    Engine();
    void SetParam(double _power, int _expense, int _max_condition, int _condition);
    double power;
    int expense;
    int condition[2];
    bool enabled;
};


class Player //Класс игрока
{
public:
    Player();

    void        SetPosition(const Vector<double>*);
    void        SetPosition(int, int);
    void        SetView(const Vector<double>*);
    void        SetView(const Vector2i);
    void        SetView(int, int);

    Vector2f    GetPosition();
    Vector2f    GetView();
    double      GetRotation();
    double      GetSpeed();
    Vector2f    GetInertia(double);

    void        SetMove(Vector<double>, bool);
    void        Move();
    void        SetInertia(double _x, double _y);
    void        Alive();
    void        Death();
    Vector<double>      GetInertia();
    bool            in_move; //??

    ////////////
    ///
    bool        ReadyToFire(int);
    void        Attack(int weapon);
    //void        SetWeapon(Weapon* weapon, int slot);
    void        SetEngine(Engine* _engine);
    ////////////Игровые параметры

    int         health[2];

    int         shield[2];
    int         shield_prot;
    bool        is_shield;
    int         energy[2];
    int         weapon_selected;
    Weapon      weapon[4];
    Engine      engine;
    unsigned long int score;


    Sprite      sprite;
    ////////////

    double frame;
    bool    is_alive;
    bool    is_empty;
    int     bonus;

private:
    Vector<double>  position;
    Vector<double>  view;
    Vector<double>  inertia;
    double          friction;

};

#endif // PLAYER_H
