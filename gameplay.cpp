#include "gameplay.h"

GamePlay::GamePlay()
{
    sunPoints=100;
}

void GamePlay::subtractSunPoints(int x)
{
    sunPoints=sunPoints-x;
    if(sunPoints<0)
        sunPoints=0;
}

void GamePlay::addSunPoints(int x)
{
    sunPoints=sunPoints+x;
}

int GamePlay::getSunPoints() const
{
    return sunPoints;
}

void GamePlay::setCurrentUser()
{
    if(userTimestamp.size()>0)
    {
        double i=getIndex();
//        currentUser.append(userTimestamp[i]);
//        currentUser.append(userPlayer[i]);
//        currentUser.append(userLevel[i]);
        currentUser[1]=userPlayer[i];
        currentUser[2]=userLevel[i];
        updateTimestamp(currentUser[1]);
        currentUser[0]=userTimestamp[i];
    }
}

void GamePlay::updateCurrentUser(QString name)
{
    if(userTimestamp.size()>0)
    {
        double i=getNameIndex(name);
//        currentUser.append(userTimestamp[i]);
//        currentUser.append(userPlayer[i]);
//        currentUser.append(userLevel[i]);
        currentUser[1]=userPlayer[i];
        currentUser[2]=userLevel[i];
        updateTimestamp(currentUser[1]);
        currentUser[0]=userTimestamp[i];
    }
}

int GamePlay::getCurrentLevel()
{
    return currentUser[2].toInt();
}


GamePlay::PeaShooter::PeaShooter()
{
      cost=100;
      life=4;
      range=9999;
      damage=1;
      rate=1.5;
      splash=0;
      slow=0;
      bomb=0;
      seeding=7.5;
      sun=0;
      need=0;
}


GamePlay::SunFlower::SunFlower()
{
    cost=50;
    life=4;
    range=0;
    damage=0;
    rate=24;
    splash=0;
    slow=0;
    bomb=0;
    seeding=7.5;
    sun=1;
    need=0;
}


GamePlay::CherryBomb::CherryBomb()
{
    cost=150;
    life=9999;
    range=1;
    damage=90;
    rate=1;
    splash=3;
    slow=0;
    bomb=1;
    seeding=50;
    sun=0;
    need=0;
}


GamePlay::WallNut::WallNut()
{
    cost=50;
    life=72;
    range=0;
    damage=0;
    rate=0;
    splash=0;
    slow=0;
    bomb=0;
    seeding=30;
    sun=0;
    need=0;
}


GamePlay::PatatoMine::PatatoMine()
{
    cost=25;
    life=4;
    range=1;
    damage=90;
    rate=15;
    splash=0;
    slow=0;
    bomb=1;
    seeding=30;
    sun=0;
    need=0;
}


GamePlay::SnowPea::SnowPea()
{
    cost=175;
    life=4;
    range=9999;
    damage=1;
    rate=1.5;
    splash=0;
    slow=1;
    bomb=0;
    seeding=7.5;
    sun=0;
    need=0;
}


GamePlay::Chomper::Chomper()
{
    cost=150;
    life=4;
    range=1;
    damage=150;
    rate=42;
    splash=0;
    slow=0;
    bomb=0;
    seeding=7.5;
    sun=0;
    need=0;
}


GamePlay::Repeater::Repeater()
{
    cost=200;
    life=4;
    range=9999;
    damage=2;
    rate=1.5;
    splash=0;
    slow=0;
    bomb=0;
    seeding=7.5;
    sun=0;
    need=1;
}


GamePlay::Regular::Regular()
{
    life=10;
    equipment=0;
    attack=1;
    rate=0.5;
    speed=5;

}


GamePlay::Flag::Flag()
{
    life=10;
    equipment=0;
    attack=1;
    rate=0.5;
    speed=3.75;
}


GamePlay::Conehead::Conehead()
{
    life=10;
    equipment=18;
    attack=1;
    rate=0.5;
    speed=5;
}


GamePlay::Buckethead::Buckethead()
{
    life=10;
    equipment=55;
    attack=1;
    rate=0.5;
    speed=5;
}


GamePlay::Newspaper::Newspaper()
{
    life=8;
    equipment=8;
    attack=1;
    rate=0.5;
    speed=5;
}
