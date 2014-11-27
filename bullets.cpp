#include "bullets.h"

Bullets::Bullets()
{
}

Bullets::Bullets(int type, int xPos, int yPos)
{
    damage=5;
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
    //when function is called, the bullet object that is created will translate along the
    //x axis. When there is a collision with a zombie, it will get deleted.
}

void Bullets::slideBullet()
{
    xPos+=5;
}
