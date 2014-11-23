#include "zombies.h"

Zombies::Zombies()
{
    type=0;
    life=0;
    attack=0;
    rate=0;
    speed=0;
}

Zombies::Zombies(int type, int life, int equipment, int attack, double rate, double speed)
{
    this->type=type;
    this->life=life;
    this->attack=attack;
    this->rate=rate;
    this->speed=speed;
}
