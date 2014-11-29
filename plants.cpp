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

Plants::Plants(int type, int xPos, int yPos)
{
    fireTimer=1;
    sunTimer=1;
    plantSun=false;
    shootZombie=false;
    dead=false;
    if(type==1)
    {
        plantPicture=file.currentPath()+"/icons/peashooter1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=100;
        life=4;
        range=9999;
        damage=1;
        rate=1.5;
        splash=0;
        slow=0;
        bomb=0;
        seeding=7.5;
        sun=0;
        need=0;
        shootZombie=true;
    }
    if(type==2)
    {
        plantPicture=file.currentPath()+"/icons/sunflower1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=50;
        life=4;
        range=0;
        damage=0;
        rate=24;
        splash=0;
        slow=0;
        bomb=0;
        seeding=7.5;
        sun=1;
        need=0;
        plantSun=true;
        sunSpawn.start();
    }
    if(type==3)
    {
        plantPicture=file.currentPath()+"/icons/cherrybomb1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=150;
        life=9999;
        range=1;
        damage=90;
        rate=1;
        splash=3;
        slow=0;
        bomb=1;
        seeding=50;
        sun=0;
        need=0;
    }
    if(type==4)
    {
        plantPicture=file.currentPath()+"/icons/wallnut1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=50;
        life=72;
        range=0;
        damage=0;
        rate=0;
        splash=0;
        slow=0;
        bomb=0;
        seeding=30;
        sun=0;
        need=0;
    }
    if(type==5)
    {
        plantPicture=file.currentPath()+"/icons/potatomine1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=25;
        life=4;
        range=1;
        damage=90;
        rate=15;
        splash=0;
        slow=0;
        bomb=1;
        seeding=30;
        sun=0;
        need=0;
    }
    if(type==6)
    {
        plantPicture=file.currentPath()+"/icons/snowpea1.png";
        this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=175;
        life=4;
        range=9999;
        damage=1;
        rate=1.5;
        splash=0;
        slow=1;
        bomb=0;
        seeding=7.5;
        sun=0;
        need=0;
        shootZombie=true;
    }
    if(type==7)
    {
        plantPicture=file.currentPath()+"/icons/chomper1.png";this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=150;
        life=4;
        range=1;
        damage=150;
        rate=42;
        splash=0;
        slow=0;
        bomb=0;
        seeding=7.5;
        sun=0;
        need=0;
    }
    if(type==8)
    {
        plantPicture=file.currentPath()+"/icons/repeater1.png";this->type=type;
        this->xPos=xPos;
        this->yPos=yPos;
        cost=200;
        life=4;
        range=9999;
        damage=2;
        rate=1.5;
        splash=0;
        slow=0;
        bomb=0;
        seeding=7.5;
        sun=0;
        need=1;
        shootZombie=true;
    }
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

int Plants::getType() const
{
    return type;
}

bool Plants::okayToShoot()
{
    return shootZombie;
}

void Plants::setOkayToShoot(bool x)
{
    shootZombie=x;
}

bool Plants::getStatus()
{
    return dead;
}

bool Plants::okayToPlant()
{
//    if(sunTimer%75==0)
//        plantSun=true;
//    else
//        plantSun=false;
//    sunTimer++;
//    return plantSun;
    if(sunSpawn.elapsed()>24000)
    {
        sunSpawn.restart();
        plantSun=true;
    }
    else
        plantSun=false;
    return plantSun;
}

void Plants::setStatus(bool status)
{
    dead=status;
}

void Plants::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->drawPixmap(xPos,yPos,90,100,plantPicture);
}

void Plants::advance(int phase)
{
    setPosition(xPos,yPos);
}
