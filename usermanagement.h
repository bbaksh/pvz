#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtAlgorithms>
#include <QApplication>
#include <QAbstractButton>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <QList>
#include <QGraphicsItem>
#include <QObject>



class UserManagement
{
private:
protected:
    QStringList userTimestamp;
    QStringList userPlayer;
    QStringList userLevel;
    QStringList levelLevel;
    QStringList levelSequence;
    QList<QStringList> levelSequenceNumber;//holds a lists of lists (ie a list of zombiesequences, and each zombiesequence is a list of zombie types)
    QStringList levelRows;
    QStringList levelStart;//when a level starts
    QStringList levelInterval;//how fast zombies appear after it starts
    QStringList levelDecrement;//decrease how fast the zombies appear
    bool close;//close the program due to an error

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

public slots:
    QStringList userSort();//sort users by timestamp


};

#endif // USERMANAGEMENT_H
