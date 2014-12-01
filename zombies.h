#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QTime>


class Zombies : public QGraphicsPixmapItem
{
private:
    int alteredSpeed;//this is going to be used as speed, since the provided speed is overpowered
    int type;
    int life;
    int equipment;
    int attack;
    double rate;
    double speed;
    int xPos;
    int yPos;
    bool keepMoving;//handles if a zombie is not moving because its eating a plant
    QDir file;
    QPixmap zombiePicture;
    QTime attackRate;  //how fast a zombie attacks a plant
protected:
public:
    Zombies();
    Zombies(int type,int xPos,int yPos);
    int getX() const;
    int getY() const;
    int getLife();
    int getAttack() const;//used to get a zombies attack
    void loseHealth(int damage);//decreases a zombies life when hit
    void setMovement(bool x);//used to change if a zombie is able to move or not based on a plants status (dead or alive)
    bool getMovement();//gets the status of movement
    void slideZombie();//moves zombie
    void loseSpeed();//reduces speed when hit by snow pea
    int timeElapsed();//checks the time elapsed since last attack
    void resetAttackRate();//resets the time for next attack
    void setPosition(int xPos, int yPos);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool inArea(int x, int y);//used to track if a bullet is in the zombies area
};

#endif // ZOMBIES_H
