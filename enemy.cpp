#include "enemy.h"

Box::Box()
{
    is_active = false;
    position.Set(0, 0);
    energy = 0;
}

void Box::Spawn(Vector<double> pos, int _energy)
{
    is_active = true;
    position.Set(pos.x, pos.y);
    energy = _energy;
}

void Box::Delete()
{
    is_active = false;
}

Vector2f Box::GetPosition()
{
    return Vector2f(position.x, position.y);
}

Enemy::Enemy()
{
    is_alive = false;
    health[MAX] = 0;
    health[CURRENT] = 0;
    shield[MAX] = 0;
    shield[CURRENT] = 0;
    position.x = 0.0;
    position.y = 0.0;
    view.x = 0.0;
    view.y = 0.0;
    accuracy = 0;
    reaction = 0;
    size = 0;
}

void Enemy::SetPosition(const Vector<double>* vector)
{
    position = *vector;
}
void Enemy::SetPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Enemy::SetView(const Vector<double>* vector)
{
    view = *vector;
}
void Enemy::SetView(int x , int y)
{
    view.x = x;
    view.y = y;
}
void Enemy::SetView(const Vector2i vector)
{
    view.x = vector.x;
    view.y = vector.y;
}

void Enemy::SetView(const Vector2f vector)
{
    view.x = vector.x;
    view.y = vector.y;
}

Vector2f Enemy::GetPosition()
{
    return Vector2f(position.x, position.y);
}

Vector2f Enemy::GetView()
{
    return Vector2f(view.x, view.y);
}

double Enemy::GetRotation()
{
    return atan2(view.y - position.y ,view.x - position.x) / M_PI * 180 + 90;
}

double Enemy::GetSpeed()
{
    return sqrt(pow(inertia.x, 2.0) + pow(inertia.y, 2.0));
}

/*void Enemy::Spawn(WeaponTemp* _weapon)
{
    is_alive = true;
    health[MAX] = ENEMY_DEFAULT_HEALTH;
    health[CURRENT] = health[MAX];
    this->SetPosition(random(SPAWN_ENEMY_MIN_COORD, DEFAULT_SCREEN_W - SPAWN_ENEMY_MIN_COORD), random(SPAWN_ENEMY_MIN_COORD, DEFAULT_SCREEN_H - SPAWN_ENEMY_MIN_COORD));
    _weapon->SetWeapon(&weapon);
}*/

void Enemy::Spawn(EnemyPrototype* _enemy_prot, Vector<int> pos)
{
    is_alive = true;
    health[MAX] = _enemy_prot->health;
    health[CURRENT] = health[MAX];
    shield[MAX] = _enemy_prot->shield;
    shield[CURRENT] = shield[MAX];
    size = _enemy_prot->size;
    reward = _enemy_prot->reward;
    loot = _enemy_prot->loot;

    _enemy_prot->weapon->SetWeapon(&weapon);
    weapon.is_reload = true;
    sprite = *_enemy_prot->sprite;
    sprite.setOrigin(Vector2f((double)size / 2.0, (double)size / 2.0));
    this->SetPosition(pos.x, pos.y);
}
void Enemy::Destruct()
{
    is_alive = false;
    health[MAX] = 0;
    health[CURRENT] = 0;
    shield[MAX] = 0;
    shield[CURRENT] = 0;
    position.x = 0.0;
    position.y = 0.0;
    view.x = 0.0;
    view.y = 0.0;
    accuracy = 0;
    reaction = 0;
}


EnemyPrototype::EnemyPrototype()
{
    weapon = NULL;
    health = 0;
    shield = 0;
    accuracy = 0.0;
    reaction = 0;
    size = 0;
    sprite = NULL;
}

void EnemyPrototype::SetParam(int max_health, int max_shield, WeaponTemp *_weapon, Sprite *_sprite, int _size, int _reward, bool _loot)
{
    health = max_health;
    shield = max_shield;
    weapon = _weapon;
    sprite = _sprite;
    size = _size;
    reward = _reward;
    loot = _loot;
}

