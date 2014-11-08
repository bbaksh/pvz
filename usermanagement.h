#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDateTime>


class UserManagement
{
private:
protected:
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
    void readUserData(QString fileName);
    void readLevelData(QString fileName);
    void createUser(QString name);
    void saveUsers(QString fileName);
    bool nameValidation(QString name);
    bool levelValidation(QString level);

};

#endif // USERMANAGEMENT_H

/*
 Stuff I dont need:
 //if(name[i]=="0"||name[i]=="1"||name[i]=="2"||name[i]=="3"||name[i]=="4"||name[i]=="5"||name[i]=="6"||name[i]=="7"||name[i]=="8"||name[i]=="9"||name[i]=="a"||name[i]=="b"||name[i]=="c"||name[i]=="d"||name[i]=="e"||name[i]=="f"||name[i]=="g"||name[i]=="h"||name[i]=="i"||name[i]=="j"||name[i]=="k"||name[i]=="l"||name[i]=="m"||name[i]=="n"||name[i]=="o"||name[i]=="p"||name[i]=="q"||name[i]=="r"||name[i]=="s"||name[i]=="t"||name[i]=="u"||name[i]=="v"||name[i]=="w"||name[i]=="x"||name[i]=="y"||name[i]=="z")

*/