#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "UserManagement.h"

class GamePlay: public UserManagement
{
protected:
    int sunPoints;
    QString currentUser[3];//an array of siz 3. holds the name, level and timestamp of current user

public:
    GamePlay();
    void subtractSunPoints(int x);
    void addSunPoints(int x);
    int getSunPoints() const;
    void setCurrentUser();
    void updateCurrentUser(QString name);//used to update a user when they succesfully complete a level or is selected
    int getCurrentLevel();
    void setCurrentLevel();
    void setLevelForEndGame();//used to reset the level back to 1 when the user beats level 8
};

#endif // GAMEPLAY_H
