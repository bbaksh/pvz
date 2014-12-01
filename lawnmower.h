#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QTime>

class Lawnmower: public QGraphicsPixmapItem
{
private:
    QDir file;//used to track homepath
    QPixmap lawnmowerPicture;//holds the image
    int xPos;
    int yPos;
    QTime disappear;//used to track when a lawnmower has been activated and when it should disappear from the scene
public:
    Lawnmower();
    Lawnmower(int xPos, int yPos);
    int getX();
    int getY();
    int timeElapsed();//returns the time elapsed since a lawnmower is triggered
    void setPosition(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void slideLawnmower();//changes the lawnmowers position when activated
};

#endif // LAWNMOWER_H
