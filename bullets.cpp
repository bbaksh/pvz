#include "bullets.h"

Bullets::Bullets()
{
}

Bullets::Bullets(int type, int xPos, int yPos)
{
    if(type==8)
        damage=2;
    else
        damage=1;
    this->type=type;
    this->xPos=xPos;
    this->yPos=yPos;
    bulletPicture=file.currentPath()+"/icons/bullet1.png";
}

int Bullets::getX()
{
    return xPos;
}

int Bullets::getY()
{
    return yPos;
}

int Bullets::getType()
{
    return type;
}

int Bullets::getDamage()
{
    return damage;
}

void Bullets::setPosition(int x, int y)
{
    xPos=x;
    yPos=y;
}

QRectF Bullets::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Bullets::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos,yPos,100,90,bulletPicture);
}

void Bullets::advance(int)
{
}

void Bullets::slideBullet()
{
    xPos+=5;
}
