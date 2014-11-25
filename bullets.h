#ifndef BULLETS_H
#define BULLETS_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class Bullets: public QGraphicsItem
{
public:
    Bullets();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    void advance(int);
private:
    int damage;
    int xPos;
    int yPos;
};

#endif // BULLETS_H
