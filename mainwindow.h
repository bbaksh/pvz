#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "UserManagement.h"
#include "gameplay.h"
#include "gamedisplay.h"
#include <QMainWindow>
#include <QDir>
#include <iostream>
#include <QTimer>
#include <time.h>
#include <QTime>
#include <QSpacerItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    void loadButtons();
    void quitProgram();
    ~MainWindow();
protected:
//    bool event(QEvent *mouse);

private slots:

   void updateSunLabel();

   void setupNextLevel();

   void handleCooldown(int i);

   void on_newButton_clicked();

   void on_deleteButton_clicked();

   void on_quitButton_clicked();

   void on_userButton_activated(const QString &arg1);

   void on_startButton_clicked();

   void on_plant1Button_clicked();

   void on_restartButton_clicked();

   void on_plant2Button_clicked();

   void on_plant3Button_clicked();

   void on_plant4Button_clicked();

   void on_plant5Button_clicked();

   void on_plant6Button_clicked();

   void on_plant7Button_clicked();

   void on_plant8Button_clicked();

private:

    GameDisplay *pvz;//accesser to ui element graphicsview
    QString userPathName;
    QDir playersPath;
    QDir levelsPath;
    QTimer *timer;
    QTimer *updateSuns;
    QTimer *zombieTimer;
    QTimer *animateZombie;
    QGraphicsPixmapItem *picture;
    QTime plantButtons[8];
signals:
    void mouseclick(QEvent *);
    void levelsError();

};


#endif // MAINWINDOW_H
