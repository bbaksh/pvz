#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "gameplay.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPixmap>

class GameBoard: public GamePlay
{
private:
    QPixmap *currentScreen;
public:
    GameBoard();
    QString setMainScreen();


};

#endif // GAMEBOARD_H
