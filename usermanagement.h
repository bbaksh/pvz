#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>


class UserManagement
{
private:
protected:
    QString userName;
    QString levelName;
    QStringList userTimestamp;
    QStringList userPlayer;
    QStringList userLevel;
    QStringList levelLevel;
    QStringList levelSequence;
    QStringList levelRows;
    QStringList levelStart;
    QStringList levelInterval;
    QStringList levelDecrement;


public:
    UserManagement();
    void readUserData();
    void readLevelData();
};

#endif // USERMANAGEMENT_H
