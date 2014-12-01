#include "sun.h"

Sun::Sun()
{

}

Sun::Sun(int x, int y,QString path,int type)
{
    disappear.start();
    if(type==1)
    {
    xPos=x;
    yPos=0;
    randomY=y;
    sunPicture=path;
    this->type=type;

    }
    else
    {  
        xPos=x;
        yPos=y;
        randomY=0;
        sunPicture=path;
        this->type=type;
    }
}

int Sun::getX()
{
    return xPos;
}

int Sun::getY()
{
    return yPos;
}

int Sun::getType()
{
    return type;
}

void Sun::setClicked()
{
    xPos=-1;
    yPos=-1;
}

void Sun::slideSun()
{
    if(yPos<=randomY)
    {
    yPos+=2;
    disappear.restart();
    }

}

void Sun::advance(int phase)
{
}

bool Sun::areaX(int x)
{
    for(int i=0;i<50;i++)//CHECKS IF MOUSE CLICK IS WITHIN THE 50X50 AREA
    {
        if(x==xPos+i)
        {
            return true;
        }
    }
    return false;
}

bool Sun::areaY(int y)
{
    for(int i=0;i<50;i++)//CHECKS IF MOUSE CLICK IS WITHIN THE 50X50 AREA
    {
        if(y==yPos+i)
        {
            return true;
        }
    }
    return false;
}


int Sun::timeEllapsed()
{
    return (disappear.elapsed());

}

QPixmap Sun::getPicture()
{
    return sunPicture;
}

QRectF Sun::boundingRect() const
{
    return QRectF(0,0,62,62);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(xPos,yPos,50,50,sunPicture);

}
