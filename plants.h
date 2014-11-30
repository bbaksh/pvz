#ifndef PLANTS_H
#define PLANTS_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>
#include <QTimer>
#include <QGraphicsObject>
#include <QTime>

class Plants : public QGraphicsPixmapItem
{
private:
    QDir file;
    QPixmap plantPicture;
    QTime sunSpawn;
    QTime attackRate;
    int type;
    int cost;
    int life;
    int range;
    int damage;
    double rate;
    int splash;
    int slow;
    int bomb;
    double seeding;
    int sun;
    int need;
    int xPos;
    int yPos;
    bool dead;
    bool plantSun;
    bool shootZombie;
    bool chompZombie;
public:
    Plants();
    Plants(int type, int xPos, int yPos);
    int getCost() const;
    int getLife() const;
    void setPosition(int x, int y);
    void loseHealth(int attack);
    int getX();
    int getY();
    int getDamage();
    int getType() const;
    bool okayToShoot();
    void setOkayToShoot(bool x);
    bool getStatus();
    bool okayToChomp();
    bool okayToPlant();
    int timeElapsed();
    void restartAttackRate();
    void setStatus(bool status);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



};

#endif // PLANTS_H
