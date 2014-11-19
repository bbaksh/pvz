#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "UserManagement.h"

class GamePlay: public UserManagement
{
protected:
    int sunPoints;
    QString currentUser[3];
public:
    GamePlay();
    void subtractSunPoints(int x);
    void addSunPoints(int x);
    int getSunPoints() const;
    void setCurrentUser();
    void updateCurrentUser(QString name);
    int getCurrentLevel();
    struct PeaShooter{
      PeaShooter();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct SunFlower{
      SunFlower();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct CherryBomb{
      CherryBomb();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct WallNut{
      WallNut();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct PatatoMine{
      PatatoMine();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct SnowPea{
      SnowPea();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct Chomper{
      Chomper();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct Repeater{
      Repeater();
      int cost;
      int life;
      int range;
      int damage;
      double rate;
      int splash;
      int slow;
      int bomb;
      double seeding;
      int sun;
      int need;
    };
    struct Regular{
        Regular();
        int life;
        int equipment;
        int attack;
        double rate;
        double speed;
    };
    struct Flag{
        Flag();
        int life;
        int equipment;
        int attack;
        double rate;
        double speed;
    };
    struct Conehead{
        Conehead();
        int life;
        int equipment;
        int attack;
        double rate;
        double speed;
    };
    struct Buckethead{
        Buckethead();
        int life;
        int equipment;
        int attack;
        double rate;
        double speed;
    };
    struct Newspaper{
        Newspaper();
        int life;
        int equipment;
        int attack;
        double rate;
        double speed;
    };
};

#endif // GAMEPLAY_H
