#include "gameplay.h"

GamePlay::GamePlay()
{
    sunPoints=100;
}

void GamePlay::subtractSunPoints(int x)
{
    if(sunPoints>=x)
    sunPoints=sunPoints-x;

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

void GamePlay::setCurrentLevel()
{
    sunPoints=100;
    userLevel[getIndex()]=QString::number(userLevel[getIndex()].toInt()+1);
    setCurrentUser();
}

void GamePlay::setLevelForEndGame()
{
    sunPoints=100;
    if(userLevel[getIndex()].toInt()==9)
    {
          userLevel[getIndex()]=QString::number(1);
    }
    setCurrentUser();
}

