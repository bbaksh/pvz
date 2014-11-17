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


   void on_newButton_clicked();

   void on_deleteButton_clicked();

   void on_quitButton_clicked();

private:
    QGraphicsScene *scene;
    GameBoard pvz;
    QString userPathName;
};

#endif // MAINWINDOW_H
