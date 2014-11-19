#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include <QPointF>
#include "gameplay.h"
#include <QGraphicsView>
#include <QDir>

class GameDisplay : public QGraphicsView, public GamePlay
{
    Q_OBJECT
private:
    QDir homePath;
protected:
    QPointF click;

public:
    explicit GameDisplay(QWidget *parent = 0);
    QGraphicsScene *scene;
    QString mainScreen();
    void setLevel(int i);



signals:

public slots:
    void mousePressEvent(QMouseEvent *click);

};

#endif // GAMEDISPLAY_H
