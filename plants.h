#ifndef PLANTS_H
#define PLANTS_H

#include <QGraphicsPixmapItem>

class Plants : public QGraphicsPixmapItem
{
private:


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
public:
    Plants();
    Plants(int type, int cost, int life, int range, int damage, double rate, int splash, int slow, int bomb, double seeding, int sun, int need);
    int getCost() const;
    void setPosition(int x, int y);
    int getX();
    int getY();
    int getType();



};

#endif // PLANTS_H
