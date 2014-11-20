#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include <QPointF>
#include "gameplay.h"
#include <QGraphicsView>
#include <QDir>
#include <QGraphicsItem>

class GameDisplay : public QGraphicsView, public GamePlay
{
    Q_OBJECT
private:
    QDir homePath;
protected:
    QPointF click;
    double xCoord;
    double yCoord;
    double plantType;

public:
    explicit GameDisplay(QWidget *parent = 0);
    QGraphicsScene *scene;
    QString mainScreen();
    void setPlant(int i);
    void setPlantType(int i);
    double getPlantType();
    int getRows(int i);
    void setLevel(int i);



signals:

public slots:
    void mousePressEvent(QMouseEvent *click);

};

#endif // GAMEDISPLAY_H
