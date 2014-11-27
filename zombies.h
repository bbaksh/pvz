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
    bool keepMoving;
    QDir file;
    QPixmap zombiePicture;
protected:
public:
    Zombies();
    Zombies(int type,int xPos,int yPos);
    int getX() const;
    int getY() const;
    int getLife();
    int getAttack() const;
    void loseHealth(int damage);
    void setMovement(bool x);
    void slideZombie();
    void setPosition(int xPos, int yPos);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool inArea(int x, int y);
};

#endif // ZOMBIES_H
