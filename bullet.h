#ifndef BULLET_H
#define BULLET_H

#include "main.h"
#include "vector.h"
#include "player.h"
#include "enemy.h"

#define DEFAULT_BULLET_RADIUS 15.0

class Bullet
{
public:
    Bullet();
    ~Bullet();
    bool        is_exist;
    void        SetPosition(Vector<double>*);
    void        SetPosition(int, int);
    void        SetView(Vector<double>*);
    void        SetView(Vector2i);
    void        SetView(int, int);

    void        Move();

    Vector2f    GetPosition();
    Vector2f    GetView();
    double      GetRotation();
    double      GetSpeed();
    Vector2f    GetInertia(double);

    void        SetActive(Player*);
    void        SetActive(Enemy*);
    void        SetDeactive();


    int         max_time_life;
    Clock       time_life;

    int         damage;
    bool        in_shield;
    Sprite      sprite;
private:
    Vector<double>  position;
    Vector<double>  view;
    Vector<double>  inertia;

};

#endif // BULLET_H
