#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QDir>


class Zombies : public QGraphicsPixmapItem
{
private:
    int type;
    int life;
    int equipment;
    int attack;
    double rate;
    double speed;
    int xPos;
    int yPos;
    QDir file;
    QPixmap zombiePicture;
protected:
public:
    Zombies();
    Zombies(int type,int xPos,int yPos);
    int moveZombie();
    void slideZombie();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
};

#endif // ZOMBIES_H
