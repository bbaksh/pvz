#include "bullets.h"

Bullets::Bullets()
{
}

QRectF Bullets::boundingRect() const
{
    return QRectF(0,0,5,5);
}

void Bullets::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    painter->setPen(pen);
    QBrush b(Qt::green);
    painter->setBrush(b);
    painter->drawEllipse(boundingRect());
}

void Bullets::advance(int)
{
    //when function is called, the bullet object that is created will translate along the
    //x axis. When there is a collision with a zombie, it will get deleted.
}
