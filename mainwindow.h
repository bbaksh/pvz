#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "UserManagement.h"
#include "gameplay.h"
#include "gameboard.h"
#include <QMainWindow>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    QGraphicsScene *scene;
    GameBoard pvz;
};

#endif // MAINWINDOW_H
