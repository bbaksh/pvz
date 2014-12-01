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

   void updateSunLabel();//gets called repeatedly to update the sunlabel and the plant buttons with there cooldowns and availability

   void setupNextLevel();//sets the parameters to be ready for the next level

   void handleCooldown(int i);//disables buttons based on the plant cooldown and when it was triggered

   void on_newButton_clicked();//make a new user

   void on_deleteButton_clicked();//delete your user

   void on_quitButton_clicked();//rage quit

   void on_userButton_activated(const QString &arg1);//select a user

   void on_startButton_clicked();//used to start the game

  //The plant buttons trigger a plant to be active
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

    GameDisplay *pvz;//accesser to ui element graphicsview and handles everything done in the gamedisplay class and transmit it to mainwindow
    QString userPathName;//gets the path to the player_csv
    QDir playersPath;//gets the path to the player_csv
    QDir levelsPath;//gets the path to the levels_csv
    QTimer *timer;//used to trigger a random sun falling
    QTimer *updateSuns;//used to update sunlabel
    QTimer *zombieTimer;//triggers whena zombie should spawn
    QTimer *animateZombie;//triggers zombies to move and tracks events
signals:
    void levelsError();//used to identify an error and deal with it accordingly

};


#endif // MAINWINDOW_H
