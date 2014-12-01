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
    QDir file;//current path
    QPixmap plantPicture;//holds picture
    QTime sunSpawn;//handles sunflower sun spawn times
    QTime attackRate;//hands when plants should attack
    //all of this is information to classify a plant
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

    bool dead;//checks if a plant is dead
    bool plantSun;//checks a sunflower can plant a new sun
    bool shootZombie;//checks if a zombie can be shot
    bool chompZombie;//checks if a zombie can be chomped by chomper
public:
    Plants();
    Plants(int type, int xPos, int yPos);
    int getCost() const;
    int getLife() const;
    void setPosition(int x, int y);
    void loseHealth(int attack);//used to reduce a plants health when attacked
    int getX();
    int getY();
    int getDamage();
    int getType() const;
    bool okayToShoot();//returns shooting status
    void setOkayToShoot(bool x);//sets shooting status
    bool getStatus();//returns if a plant is dead or not
    bool okayToChomp();//returns if a plant can be chompd
    bool okayToPlant();//returns if its okay to play a seed here
    int timeElapsed();//returns the time elapsed for an event
    void restartAttackRate();//restarts the attack timer
    void setStatus(bool status);//manual set if a plant is dead
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



};

#endif // PLANTS_H
