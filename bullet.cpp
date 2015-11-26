#include "vector.h"
#include "bullet.h"



Bullet::Bullet()
{
    is_exist = false;
    position.Set(0.0, 0.0);
    view.Set(0.0, 0.0);
    inertia.Set(0.0, 0.0);
    damage = 0;
    max_time_life = 0;
    in_shield = false;
}
Vector2f Bullet::GetPosition()
{
    return Vector2f(position.x, position.y);
}

void Bullet::SetActive(Player* player)
{
    position.x = player->GetPosition().x;
    position.y = player->GetPosition().y;

    view.x = player->GetView().x;
    view.y = player->GetView().y;


    inertia = view - position;

    damage = random(player->weapon[player->weapon_selected].damage[MIN],
            player->weapon[player->weapon_selected].damage[MAX]);

    max_time_life = player->weapon[player->weapon_selected].time_life_bullet;
    time_life.restart();
    inertia.SetNormal();

    // разброс





    //
    position = position + inertia * PLAYER_DIM; // защита от самопопадания
    inertia = inertia * player->weapon[player->weapon_selected].speed_bullet;
    is_exist = true;
    in_shield = false;
    sprite = *player->weapon[player->weapon_selected].sprite_bullet;
}

void Bullet::SetActive(Enemy* player)
{

    position.x = player->GetPosition().x;
    position.y = player->GetPosition().y;

    view.x = player->GetView().x;
    view.y = player->GetView().y;
    //разброс
    /*double random_angle = 1.0;
    view.SetNormal();
    view.x = view.x * cos(random_angle) - view.y * sin(random_angle);
    view.y = view.x * sin(random_angle) + view.y * cos(random_angle);*/



    inertia = view - position;

    damage = random(player->weapon.damage[MIN],
            player->weapon.damage[MAX]);

    max_time_life = player->weapon.time_life_bullet;
    time_life.restart();
    inertia.SetNormal();

    //inertia.SetNormal();
    position = position + inertia * PLAYER_DIM; // защита от самопопадания



    inertia = inertia * player->weapon.speed_bullet;
    is_exist = true;
    in_shield = false;

    sprite = *player->weapon.sprite_bullet;
    sprite.setColor(player->weapon.bullet_color);
}

void Bullet::SetDeactive()
{
    is_exist = false;
    in_shield = false;
    position.Set(0.0, 0.0);
    view.Set(0.0, 0.0);
    inertia.Set(0.0, 0.0);
    damage = 0;
}

void Bullet::Move()
{
    position = position + inertia;
}

double Bullet::GetRotation()
{
    return atan2(view.y - position.y ,view.x - position.x) / M_PI * 180 + 90;
}

Bullet::~Bullet()
{

}

