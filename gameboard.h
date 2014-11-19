#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "gameplay.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDir>

class GameBoard: public GamePlay
{
private:
    QDir homePath;
    QPixmap currentScreen;
public:
    GameBoard();
    QString getMainScreen();


};

#endif // GAMEBOARD_H
