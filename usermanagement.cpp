#include "usermanagement.h"

UserManagement::UserManagement()
{
}

void UserManagement::readUserData(QString fileName)
{
    QFile players(fileName);
    if (players.open(QIODevice::ReadOnly))
    {
        QTextStream reader(&players);
        QString data=reader.readLine();
        QStringList values;
        while(!data.isNull())
        {
            values=data.split(":");
            userTimestamp.append(values[0]);
            if(nameValidation(values[1]))
            {
                userPlayer.append(values[1]);
            }
            else userPlayer.append("");
            if(levelValidation(values[2]))
            {
                userLevel.append(values[2]);
            }
            else userLevel.append("");
            data = reader.readLine();
        }
        players.close();
    }
}

void UserManagement::readLevelData(QString fileName)
{
    int time=QDateTime::currentDateTime().toTime_t();
    QFile levels(fileName);
    if (levels.open(QIODevice::ReadOnly))
    {
        QTextStream reader(&levels);
        QString data=reader.readLine();
        QStringList values;
        while(!data.isNull())
        {
            values=data.split(":");
            levelLevel.append(values[0]);
            QStringList sequenceValues;
            sequenceValues=values[1].split(",");
            for(int i=0;i<sequenceValues.size();i++)
            {
                levelSequence.append(sequenceValues[i]);
            }
            levelRows.append(values[2]);
            levelStart.append(values[3]);
            levelInterval.append(values[4]);
            levelDecrement.append(values[5]);
            data = reader.readLine();
        }
        levels.close();
    }
}

void UserManagement::createUser(QString name)
{
    QString time=QString::number(QDateTime::currentDateTime().toTime_t());
    userTimestamp.append(time);
    if(nameValidation(name))
    {
        userPlayer.append(name);
    }
    else userPlayer.append("");;
    userLevel.append("0");

}

void UserManagement::saveUsers(QString fileName)
{
    QFile players(fileName);
    if (players.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream write(&players);
        for(int i=0; i<userPlayer.size();i++)
        {
            write<<userTimestamp[i]<<":"<<userPlayer[i]<<":"<<userLevel[i]<<"\r\n";
        }
        players.close();
    }
}

bool UserManagement::nameValidation(QString name)
{
    name=name.toLower();
    bool valid=false;
    if(name.size()<=10)
    {
        for(int i=0;i<name.size();i++)
        {
            if(name[i].isLetterOrNumber())
                valid=true;
            else
            {
                valid=false;
                break;
            }
        }
    }

    if(valid==true)
        return true;
    else
        return false;
}

bool UserManagement::levelValidation(QString level)
{
    bool valid=false;
    for(int i=0;i<level.size();i++)
    {
        if(level[i].isDigit()&&level.toInt()>=0&&level.toInt()<=100)
            valid=true;
    }

    return valid;

}
