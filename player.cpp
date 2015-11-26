#include "player.h"

Engine::Engine()
{
    power = 0.0;
    condition[MAX] = 0;
    condition[CURRENT] = condition[MAX];
    expense = 0;
    enabled = false;
}

void Engine::SetParam(double _power, int _expense, int _max_condition, int _condition)
{
    power = _power;
    expense = _expense;
    condition[MAX] = _max_condition;
    condition[CURRENT] = _condition;
}

Player::Player()
{
    position.Set(0, 0);
    view.Set(0, 0);
    inertia.Set(0.0, 0.0);
    friction = 1.0;
    in_move = false;

    ///////////Игровые
    health[MAX] = 0;
    health[CURRENT] = health[MAX];
    shield[MAX] = 0;
    shield[CURRENT] =  shield[MAX];
    shield_prot = 0;
    is_shield = false;
    energy[MAX] = 0;
    energy[CURRENT] = energy[MAX];
    weapon_selected = 0;
    for(int i(0); i < (sizeof(weapon) / sizeof(weapon[0])); i++)
    {
        weapon[i].is_exist = false;
    }

    frame = 0;
    is_alive = false;
    is_empty = false;
    score = 0;
    bonus = 0;
}

void Player::SetPosition(const Vector<double>* vector)
{
    position = *vector;
}
void Player::SetPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Player::SetView(const Vector<double>* vector)
{
    view = *vector;
}
void Player::SetView(int x , int y)
{
    view.x = x;
    view.y = y;
}
void Player::SetView(const Vector2i vector)
{
    view.x = vector.x;
    view.y = vector.y;
}

Vector2f Player::GetPosition()
{
    return Vector2f(position.x, position.y);
}

Vector2f Player::GetView()
{
    return Vector2f(view.x, view.y);
}

double Player::GetRotation()
{
    return atan2(view.y - position.y ,view.x - position.x) / M_PI * 180 + 90;
}

double Player::GetSpeed()
{
    return sqrt(pow(inertia.x, 2.0) + pow(inertia.y, 2.0));
}

Vector2f Player::GetInertia(double scale)
{
    return Vector2f(inertia.x * scale, inertia.y * scale);
}

void Player::SetMove(Vector<double> vector, bool walk)
{
        inertia = inertia + vector;
       // inertia.SetNormal();
        in_move = true;
}
void Player::SetInertia(double _x, double _y)
{
    inertia.x = _x;
    inertia.y = _y;
}
Vector<double> Player::GetInertia()
{
    return Vector<double>(inertia.x, inertia.y);
}

void Player::Move()
{
    position = position + inertia;
    //std::cout << "V(x) =  " << inertia.x << " | V(y) = " << inertia.y << std::endl;
    // Торможение
    if(!in_move)
    {
        if(inertia.x > 0.0)
        {
            if(inertia.x < inertia_bp) inertia.x = 0.0;
            else inertia.x -= deceleration * friction;
        }
        else
        {
            if(inertia.x > -inertia_bp) inertia.x = 0.0;
            else inertia.x += deceleration * friction;
        }

        if(inertia.y > 0.0)
        {
            if(inertia.y < inertia_bp) inertia.y = 0.0;
            else inertia.y -= deceleration * friction;
        }
        else
        {
            if(inertia.y > -inertia_bp) inertia.y = 0.0;
            else inertia.y += deceleration * friction;
        }
    }
}

void Player::SetEngine(Engine *_engine)
{
    engine.condition[MAX] = _engine->condition[MAX];
    engine.condition[CURRENT] = _engine->condition[CURRENT];
    engine.expense = _engine->expense;
    engine.power = _engine->power;
    engine.enabled = true;
}

void Player::Death()
{
    health[CURRENT] = 0;
    is_alive = false;
    inertia.x = 0;
    inertia.y = 0;
}

void Player::Alive()
{
    is_alive = true;
    position.Set(200, 300);
    health[MAX] = DEFAULT_MAX_HEALTH;
    health[CURRENT] = health[MAX];
    shield[MAX] = DEFAULT_MAX_SHEILD;
    shield[CURRENT] = shield[MAX];
    shield_prot = DEFAULT_SHIELD_PROT;
    energy[MAX] = DEFAULT_MAX_ENERGY;
    energy[CURRENT] = energy[MAX];
    weapon_selected = 0;
    for(int i(0); i < (sizeof(weapon) / sizeof(weapon[0])); i++)
    {
        weapon[i].is_exist = false;
    }

    frame = 0;
    is_empty = false;
    score = 0;
    bonus = 0;
    sprite.setColor(Color(255, 255, 255, 255));
}

/*bool Player::ReadyToFire(int weapon_id)
{
    if(weapon[weapon_id] != NULL)
    {
        if(!(weapon[weapon_id]->is_reload))
        {
            return true;
        }
    }
    return false;
}*/


void Player::Attack(int weapon)
{

}
