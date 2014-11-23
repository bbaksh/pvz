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
#include <vector>
#include <sun.h>
#include <QGraphicsScene>
#include <QTimer>


class GameDisplay : public QGraphicsView, public GamePlay
{
    Q_OBJECT
private:
    QDir homePath;
    int plantType;

    QPointF click;
    double xCoord;
    double yCoord;

    Plants *p;
    Zombies *z;
    Sun *s;
    std::vector<Plants *>plantVector;
    std::vector<Zombies *>zombieVector;
    std::vector<Sun *>sunVector;

public:
    explicit GameDisplay(QWidget *parent = 0);
    QGraphicsScene *scene1;
    QEvent *event;
    QMouseEvent *mouseEvent;
    QString mainScreen();
    void setPlant(int i);
    void setPlantType(const int i);
    int getPlantType();
    int getRows(int i);
    void setLevel(int i);
    bool cellEmpty();
    QTimer *sunflowerTimer;




signals:
    void mouse();
    void sunFlowerPlanted();
public slots:
    void mousePressEvent(QMouseEvent *click);
  //  void handlemouse(QEvent *mouse=0);
    void dropSun();
    void sunFlowerSun();

};

#endif // GAMEDISPLAY_H
