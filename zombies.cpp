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
    alteredSpeed=2;
    attackRate.start();
    this->type=type;
    this->xPos=xPos;
    this->yPos=yPos;
    keepMoving=true;
    if(this->type==1)//creates a zombie with characteristics based on type
    {
        life=10;
        equipment=0;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie1.png";
    }
    if(this->type==2)//creates a zombie with characteristics based on type
    {
        alteredSpeed=1;
        life=10;
        equipment=0;
        attack=1;
        rate=0.5;
        speed=3.75;
        zombiePicture=file.currentPath()+"/icons/zombie2.png";
    }
    if(this->type==3)//creates a zombie with characteristics based on type
    {
        life=28;
        equipment=18;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie3.png";
    }
    if(this->type==4)//creates a zombie with characteristics based on type
    {
        life=65;
        equipment=55;
        attack=1;
        rate=0.5;
        speed=5;
        zombiePicture=file.currentPath()+"/icons/zombie4.png";
    }
    if(this->type==5)//creates a zombie with characteristics based on type
    {
        life=16;
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

void Zombies::loseHealth(int damage)//zombie loses health
{
    life=life-damage;
    if(life<=8&&type==5)
        alteredSpeed=1;
}

void Zombies::setMovement(bool x)
{
    keepMoving=x;
}

bool Zombies::getMovement()
{
    return keepMoving;
}


void Zombies::slideZombie()
{
    if(keepMoving)
    {
    xPos-=alteredSpeed;//move zombie by the speed
    }
}

void Zombies::loseSpeed()
{
    alteredSpeed=1;//if a zombie is hit by snow pea, the speed becomes 1
}

int Zombies::timeElapsed()
{
    return attackRate.elapsed();//returns time since last attack
}

void Zombies::resetAttackRate()
{
    attackRate.restart();//restarts the time when an attack is performed
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

bool Zombies::inArea(int x, int y)//checks if a bullet is in the area of the zombie
{
    for(int i=0;i<15;i++)
    {
        if(x==xPos+i&&y==yPos)
            return true;
    }
    return false;
}
