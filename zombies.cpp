#include "zombies.h"

Zombies::Zombies()
{
    type=0;
    life=0;
    equipment=0;
    attack=0;
    rate=0;
    speed=0;
    file=0;
    keepMoving=true;
}

Zombies::Zombies(int type,int xPos,int yPos)
{
    this->type=type;
    this->xPos=xPos;
    this->yPos=yPos;
    keepMoving=true;
    if(this->type==1)
    {
        life=10;
        equipment=0;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie1.png";
    }
    if(this->type==2)
    {
        life=10;
        equipment=0;
        attack=1;
        rate=0.5;
        speed=3.75;
        zombiePicture=file.currentPath()+"/icons/zombie2.png";
    }
    if(this->type==3)
    {
        life=10;
        equipment=18;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie3.png";
    }
    if(this->type==4)
    {
        life=10;
        equipment=55;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie4.png";
    }
    if(this->type==5)
    {
        life=8;
        equipment=8;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie5.png";
    }

}

int Zombies::getX() const
{
    return xPos;
}

int Zombies::getY() const
{
    return yPos;
}

int Zombies::getLife()
{
    return life;
}

int Zombies::getAttack() const
{
    return attack;
}

void Zombies::loseHealth(int damage)
{
    life=life-damage;
}

void Zombies::setMovement(bool x)
{
    keepMoving=x;
}


void Zombies::slideZombie()
{
    if(keepMoving)
    {
    xPos-=2;
    }
}

void Zombies::setPosition(int xPos, int yPos)
{
    this->xPos=xPos;
    this->yPos=yPos;
}

void Zombies::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos,yPos,90,100,zombiePicture);
}

void Zombies::advance(int phase)
{
    setPos(xPos,yPos);
}

bool Zombies::inArea(int x, int y)
{
    for(int i=0;i<30;i++)
    {
        if(x==i&&y==yPos)
            return true;
    }
    return false;
}
