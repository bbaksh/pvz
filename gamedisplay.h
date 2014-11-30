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
#include <QTime>

class GameDisplay : public QGraphicsView, public GamePlay
{
    Q_OBJECT
private:
    QPointF click;
    QDir homePath;
    QTime timeToRestart;
    QTime cooldowns[8];

    int plantType;
    int zombieIndex;
    bool zombiesFinished;
    bool grid[5][10];
    bool levelComplete;
    bool restartLevel;
    double xCoord;
    double yCoord;
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
    QTimer *sunflowerTimer;
    int getRows(int i);
    bool cellEmpty(int x, int y);
    void advance();
    void setGridFromLevel();
    void setPlantType(const int i);
    void setLevel(int i);
    void levelRestart();
    int getCooldown(int i);


signals:
    void sunFlowerPlanted();
    void zombieAttack(Zombies *zombie,Plants *plant);
    void plantAttack(Zombies *zombie,Plants *plant);
    void lawnmowerAttack(Zombies *zombie);
    void startNextLevel();
    void startThisLevel();
    void disableButton(int i);
public slots:
    void mousePressEvent(QMouseEvent *click);
    void dropSun();
    void sunFlowerSun();
    void spawnZombies();
    void moveZombiesAndPlants();
    void moveLawnmower(Zombies *zombie);
    void zombieHitPlant(Zombies *zombie,Plants *plant);
    void plantShootZombie(Zombies *zombie,Plants *plant);
    void timerTracking();

};

#endif // GAMEDISPLAY_H
