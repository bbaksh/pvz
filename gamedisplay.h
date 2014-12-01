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
    QTime timeToRestart;//used to track when to restart the level
    QTimer *sunflowerTimer;//tracks when to spawn suns from sunflowers
    QTime cooldowns[8];//used to track the seeding time of the plants
    int plantType;
    int zombieIndex;//used to track which zombie to spawn from the sequence
    bool zombiesFinished;//used to check that all zombies have been spawned from the sequence
    bool grid[5][10];//keeps track of the grid to see where has a plant and where is dirt
    bool levelComplete;//used to track if the level has been completed
    bool restartLevel;//used to track if the level has to be restarted
    double xCoord;
    double yCoord;
    Plants *p;//this is used to create plant objects dynamically and then store them in a vector
    Zombies *z;//this is used to create zombie objects dynamically and then store them in a vector
    Sun *s;//this is used to create sun objects dynamically and then store them in a vector
    Bullets *b;//this is used to create bullet objects dynamically and then store them in a vector
    Lawnmower *l;//this is used to create lawnmower objects dynamically and then store them in a vector
    std::vector<Plants *>plantVector;//stores all the plants in the level
    std::vector<Zombies *>zombieVector;//stores all the zombies in the level
    std::vector<Sun *>sunVector;//stores all the suns in the level
    std::vector<Bullets *>bulletVector;//stores all the bullets in the level
    std::vector<Lawnmower *>lawnmowerVector;//stores the lawnmowers in the level
public:
    explicit GameDisplay(QWidget *parent = 0);
    QGraphicsScene *scene1;//used to change the scene from mainwindow
    QEvent *event;
    QMouseEvent *mouseEvent;//handles mouse events
    QString mainScreen();//returns the path of the "menu" screen
    int getRows(int i);//gets the amount of dirt and grass rows based on level
    bool cellEmpty(int x, int y);//used to check if the cell on the grid is empty
    void advance();
    void setGridFromLevel();//checks the current level and displays the grid
    void setPlantType(const int i);
    void setLevel(int i);
    void levelRestart();//used to restart the level and its "parameters" to run smooth
    int getCooldown(int i);//gets the cooldown from the plant timers
    ~GameDisplay();


signals:
    void zombieAttack(Zombies *zombie,Plants *plant);//used to track what zombie hits a plant
    void plantAttack(Zombies *zombie,Plants *plant);//used to track what plant hits a zombie
    void lawnmowerAttack(Zombies *zombie);//used to track when a lawnmower destroys a row
    void startNextLevel();
    void startThisLevel();//used to restart the current level
    void disableButton(int i);//used to handle when a plant button should be disabled
public slots:
    void mousePressEvent(QMouseEvent *click);
    void dropSun();//drops a sun randomly
    void sunFlowerSun();//spawns a sun for a sunflower
    void spawnZombies();
    void moveZombiesAndPlants();//moves zombies and plants, but also keeps track of the coordinate system and then calls events based on "encounters"
    void moveLawnmower(Zombies *zombie);
    void zombieHitPlant(Zombies *zombie,Plants *plant);
    void plantShootZombie(Zombies *zombie,Plants *plant);
    void timerTracking();//used to time when suns disappear and when the level is completed.

};

#endif // GAMEDISPLAY_H
