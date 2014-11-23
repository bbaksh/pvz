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
};

#endif // GAMEPLAY_H
