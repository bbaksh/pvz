#include "plants.h"

Plants::Plants()
{
    cost=0;
    life=0;
    range=0;
    damage=0;
    rate=0;
    splash=0;
    slow=0;
    bomb=0;
    seeding=0;
    sun=0;
    need=0;
    type=0;
    xPos=0;
    yPos=0;
    dead=false;
}

Plants::Plants(int type, int cost, int life, int range, int damage, double rate, int splash, int slow, int bomb, double seeding, int sun, int need)
{
    dead=false;
    this->type=type;
    this->cost=cost;
    this->life=life;
    this->range=range;
    this->damage=damage;
    this->rate=rate;
    this->splash=splash;
    this->slow=slow;
    this->bomb=bomb;
    this->seeding=seeding;
    this->sun=sun;
    this->need=need;

}

int Plants::getCost() const
{
    return cost;
}

int Plants::getLife() const
{
    return life;
}

void Plants::setPosition(int x, int y)
{
    xPos=x;
    yPos=y;
}

void Plants::loseHealth(int attack)
{
    life=life-attack;
}

int Plants::getX()
{
    return xPos;
}

int Plants::getY()
{
    return yPos;
}

int Plants::getType()
{
    return type;
}

bool Plants::getStatus()
{
    return dead;
}

void Plants::setStatus(bool status)
{
    dead=status;
}
