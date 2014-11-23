#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtAlgorithms>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QList>
#include <QGraphicsItem>



class UserManagement
{
private:
protected:
    QStringList userTimestamp;
    QStringList userPlayer;
    QStringList userLevel;
    QStringList levelLevel;
    QStringList levelSequence;
    QList<QStringList> levelSequenceNumber;
    QStringList levelRows;
    QStringList levelStart;
    QStringList levelInterval;
    QStringList levelDecrement;
    bool close;

public:
    UserManagement();
    void readUserData(QString fileName);
    void readLevelData(QString fileName);
    void createUser(QString name);
    void deleteUser(int index);
    void saveUsers(QString fileName);
    void updateTimestamp(QString name);
    bool nameValidation(QString name);
    bool levelValidation(QString level);
    bool closeProgram();
    double getIndex();
    double getNameIndex(QString name);


    QStringList userSort();


};

#endif // USERMANAGEMENT_H

/*
 Stuff I dont need:
 //if(name[i]=="0"||name[i]=="1"||name[i]=="2"||name[i]=="3"||name[i]=="4"||name[i]=="5"||name[i]=="6"||name[i]=="7"||name[i]=="8"||name[i]=="9"||name[i]=="a"||name[i]=="b"||name[i]=="c"||name[i]=="d"||name[i]=="e"||name[i]=="f"||name[i]=="g"||name[i]=="h"||name[i]=="i"||name[i]=="j"||name[i]=="k"||name[i]=="l"||name[i]=="m"||name[i]=="n"||name[i]=="o"||name[i]=="p"||name[i]=="q"||name[i]=="r"||name[i]=="s"||name[i]=="t"||name[i]=="u"||name[i]=="v"||name[i]=="w"||name[i]=="x"||name[i]=="y"||name[i]=="z")
    //pvz.createUser("bob");
    //pvz.createUser("Brandon");
    //pvz.saveUsers(playersPath.currentPath()+"/pvz_players.csv");

    GRID: TOP LEFT (-50,-13) BOTTOM RIGHT(847,485)


//    struct PeaShooter{
//    public:
//      PeaShooter();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//      QString path;
//    };
//    struct SunFlower{
//      SunFlower();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct CherryBomb{
//      CherryBomb();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct WallNut{
//      WallNut();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct PatatoMine{
//      PatatoMine();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct SnowPea{
//      SnowPea();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct Chomper{
//      Chomper();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct Repeater{
//      Repeater();
//      int cost;
//      int life;
//      int range;
//      int damage;
//      double rate;
//      int splash;
//      int slow;
//      int bomb;
//      double seeding;
//      int sun;
//      int need;
//    };
//    struct Regular{
//        Regular();
//        int life;
//        int equipment;
//        int attack;
//        double rate;
//        double speed;
//    };
//    struct Flag{
//        Flag();
//        int life;
//        int equipment;
//        int attack;
//        double rate;
//        double speed;
//    };
//    struct Conehead{
//        Conehead();
//        int life;
//        int equipment;
//        int attack;
//        double rate;
//        double speed;
//    };
//    struct Buckethead{
//        Buckethead();
//        int life;
//        int equipment;
//        int attack;
//        double rate;
//        double speed;
//    };
//    struct Newspaper{
//        Newspaper();
//        int life;
//        int equipment;
//        int attack;
//        double rate;
//        double speed;
//    };
//GamePlay::PeaShooter::PeaShooter()
//{
//      cost=100;
//      life=4;
//      range=9999;
//      damage=1;
//      rate=1.5;
//      splash=0;
//      slow=0;
//      bomb=0;
//      seeding=7.5;
//      sun=0;
//      need=0;
//      path="C://Qt/Qt5.3.1/Tools/QtCreator/bin/build-pvz_bbaksh-Desktop_Qt_5_3_MinGW_32bit-Debug/icons/peashooter.png";
//}


//GamePlay::SunFlower::SunFlower()
//{
//    cost=50;
//    life=4;
//    range=0;
//    damage=0;
//    rate=24;
//    splash=0;
//    slow=0;
//    bomb=0;
//    seeding=7.5;
//    sun=1;
//    need=0;
//}


//GamePlay::CherryBomb::CherryBomb()
//{
//    cost=150;
//    life=9999;
//    range=1;
//    damage=90;
//    rate=1;
//    splash=3;
//    slow=0;
//    bomb=1;
//    seeding=50;
//    sun=0;
//    need=0;
//}


//GamePlay::WallNut::WallNut()
//{
//    cost=50;
//    life=72;
//    range=0;
//    damage=0;
//    rate=0;
//    splash=0;
//    slow=0;
//    bomb=0;
//    seeding=30;
//    sun=0;
//    need=0;
//}


//GamePlay::PatatoMine::PatatoMine()
//{
//    cost=25;
//    life=4;
//    range=1;
//    damage=90;
//    rate=15;
//    splash=0;
//    slow=0;
//    bomb=1;
//    seeding=30;
//    sun=0;
//    need=0;
//}


//GamePlay::SnowPea::SnowPea()
//{
//    cost=175;
//    life=4;
//    range=9999;
//    damage=1;
//    rate=1.5;
//    splash=0;
//    slow=1;
//    bomb=0;
//    seeding=7.5;
//    sun=0;
//    need=0;
//}


//GamePlay::Chomper::Chomper()
//{
//    cost=150;
//    life=4;
//    range=1;
//    damage=150;
//    rate=42;
//    splash=0;
//    slow=0;
//    bomb=0;
//    seeding=7.5;
//    sun=0;
//    need=0;
//}


//GamePlay::Repeater::Repeater()
//{
//    cost=200;
//    life=4;
//    range=9999;
//    damage=2;
//    rate=1.5;
//    splash=0;
//    slow=0;
//    bomb=0;
//    seeding=7.5;
//    sun=0;
//    need=1;
//}


//GamePlay::Regular::Regular()
//{
//    life=10;
//    equipment=0;
//    attack=1;
//    rate=0.5;
//    speed=5;

//}


//GamePlay::Flag::Flag()
//{
//    life=10;
//    equipment=0;
//    attack=1;
//    rate=0.5;
//    speed=3.75;
//}


//GamePlay::Conehead::Conehead()
//{
//    life=10;
//    equipment=18;
//    attack=1;
//    rate=0.5;
//    speed=5;
//}


//GamePlay::Buckethead::Buckethead()
//{
//    life=10;
//    equipment=55;
//    attack=1;
//    rate=0.5;
//    speed=5;
//}


//GamePlay::Newspaper::Newspaper()
//{
//    life=8;
//    equipment=8;
//    attack=1;
//    rate=0.5;
//    speed=5;
}
*/
