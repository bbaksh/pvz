#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QGraphicsPixmapItem>

class Zombies : public QGraphicsPixmapItem
{
private:
    int type;
    int life;
    int equipment;
    int attack;
    double rate;
    double speed;
protected:
public:
    Zombies();
    Zombies(int type, int life, int equipment, int attack, double rate, double speed);
};

#endif // ZOMBIES_H
