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
}

Zombies::Zombies(int type,int xPos,int yPos)
{
    this->type=type;
    this->xPos=xPos;
    this->yPos=yPos;
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
        zombiePicture=file.currentPath()+"/icons/zombie1.png";
    }
    if(this->type==5)
    {
        life=8;
        equipment=8;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie1.png";
    }

}

int Zombies::moveZombie()
{
    xPos-=5;
    return xPos;
}

void Zombies::slideZombie()
{
    xPos--;
}

void Zombies::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos,yPos,100,90,zombiePicture);
}

void Zombies::advance(int phase)
{
    setPos(xPos,yPos);
}
