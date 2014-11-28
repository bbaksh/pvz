#include "lawnmower.h"

Lawnmower::Lawnmower()
{
}

Lawnmower::Lawnmower(int xPos, int yPos)
{
    this->xPos=xPos;
    this->yPos=yPos;
    lawnmowerPicture=file.currentPath()+"/icons/lawnmower.png";
    slideTimer=0;
}

int Lawnmower::getX()
{
    return xPos;
}

int Lawnmower::getY()
{
    return yPos;
}

void Lawnmower::setPosition(int x, int y)
{
    xPos=x;
    yPos=y;
}

void Lawnmower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos,yPos,90,100,lawnmowerPicture);
}

void Lawnmower::advance(int phase)
{
    //xPos=800;
}

void Lawnmower::slideLawnmower()
{
    //(slideTimer%1000==0)
    xPos=800;
    //slideTimer++;
}
