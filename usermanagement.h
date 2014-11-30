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

public slots:


    QStringList userSort();


};

#endif // USERMANAGEMENT_H
