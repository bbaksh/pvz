#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include <QPointF>
#include "gameplay.h"
#include <QGraphicsView>
#include <QDir>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <plants.h>
#include <zombies.h>
#include <bullets.h>
#include <lawnmower.h>
#include <vector>
#include <sun.h>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>


class GameDisplay : public QGraphicsView, public GamePlay
{
    Q_OBJECT
private:
    QDir homePath;
    int plantType;
    bool grid[5][10];
    QPointF click;
    double xCoord;
    double yCoord;
    int sunFlowerIndex;
    int zombieIndex;
    int zombieAttackDelay;
    int plantAttackDelay;
    bool zombiesFinished;
    Plants *p;
    Zombies *z;
    Sun *s;
    Bullets *b;
    Lawnmower *l;
    std::vector<Plants *>plantVector;
    std::vector<Zombies *>zombieVector;
    std::vector<Sun *>sunVector;
    std::vector<Bullets *>bulletVector;
    std::vector<Lawnmower *>lawnmowerVector;

public:
    explicit GameDisplay(QWidget *parent = 0);
    QGraphicsScene *scene1;
    QEvent *event;
    QMouseEvent *mouseEvent;
    QString mainScreen();
    void setGridFromLevel();
    void setPlantType(const int i);
    int getPlantType();
    int getRows(int i);
    int zombiesInfrontOfPlants(Plants *plant);
    void setLevel(int i);
    bool cellEmpty(int x, int y);
    QTimer *sunflowerTimer;
    void advance(int phase);


signals:
    void mouse();
    void sunFlowerPlanted();
    void zombieAttack(Zombies *zombie,Plants *plant);
    void plantAttack(Zombies *zombie,Plants *plant);
    void lawnmowerAttack(Zombies *zombie);
public slots:
    void mousePressEvent(QMouseEvent *click);
    void dropSun();
    void sunFlowerSun();
    void spawnZombies();
    void moveZombiesAndPlants();
    void moveLawnmower(Zombies *zombie);
    void zombieHitPlant(Zombies *zombie,Plants *plant);
    void plantShootZombie(Zombies *zombie,Plants *plant);


};

#endif // GAMEDISPLAY_H
