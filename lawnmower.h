#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QTime>

class Lawnmower: public QGraphicsPixmapItem
{
private:
    QDir file;
    QPixmap lawnmowerPicture;
    int xPos;
    int yPos;
    QTime disappear;
public:
    Lawnmower();
    Lawnmower(int xPos, int yPos);
    int getX();
    int getY();
    int timeElapsed();
    void setPosition(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void slideLawnmower();
};

#endif // LAWNMOWER_H
