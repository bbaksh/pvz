#include "sun.h"

Sun::Sun()
{

}

Sun::Sun(int x, int y,QString path,int type)
{
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
    if(yPos!=randomY)
    {
    yPos++;
    }
}

void Sun::advance(int phase)
{
    std::cout<<"hi"<<std::endl;
}

bool Sun::areaX(int x)
{
    for(int i=0;i<50;i++)
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
    for(int i=0;i<50;i++)
    {
        if(y==yPos+i)
        {
            return true;
        }
    }
   return false;
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
   // painter->setPen(QPen(Qt::black));
    //painter->setBrush(QBrush(sunPicture));
    painter->drawPixmap(xPos,yPos,50,50,sunPicture);
    //painter->boundingRect(xPos,yPos,50,50);

}
