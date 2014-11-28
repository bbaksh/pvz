#ifndef PLANTS_H
#define PLANTS_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>
#include <QTimer>
#include <QGraphicsObject>

class Plants : public QGraphicsPixmapItem
{
private:
    QDir file;
    QPixmap plantPicture;

protected:
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
    int sunTimer;
    int fireTimer;
    bool dead;
    bool plantSun;
    bool shootZombie;
public:
    Plants();
    Plants(int type, int xPos, int yPos);
    int getCost() const;
    int getLife() const;
    void setPosition(int x, int y);
    void loseHealth(int attack);
    int getX();
    int getY();
    int getType() const;
    bool okayToShoot();
    void setOkayToShoot(bool x);
    bool getStatus();
    bool okayToPlant();
    void setStatus(bool status);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);



};

#endif // PLANTS_H
