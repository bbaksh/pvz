#include "usermanagement.h"

UserManagement::UserManagement()
{
    close=false;
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
            else
            {
                userPlayer.append("");
                players.remove();
                userTimestamp.clear();
                userPlayer.clear();
                userLevel.clear();
                saveUsers(fileName);
                break;
            }
            if(levelValidation(values[2]))
            {
                userLevel.append(values[2]);
            }
            else
            {
                    userPlayer.append("");
                    players.remove();
                    userTimestamp.clear();
                    userPlayer.clear();
                    userLevel.clear();
                    saveUsers(fileName);
                    break;
                }
            data = reader.readLine();
        }
        players.close();
    }


}

void UserManagement::readLevelData(QString fileName)
{
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
    else
        close=true;

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
    userSort();

}

void UserManagement::deleteUser(int index)
{
  userLevel[index]="NULL";
  userPlayer[index]="NULL";
  userTimestamp[index]="NULL";
}

void UserManagement::saveUsers(QString fileName)
{
    QFile players(fileName);
    if (players.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream write(&players);
        for(int i=0; i<userPlayer.size();i++)
        {
            if(userTimestamp[i]!="NULL"&&userPlayer[i]!="NULL")
            write<<userTimestamp[i]<<":"<<userPlayer[i]<<":"<<userLevel[i]<<"\r\n";
        }
        players.close();
    }

}

void UserManagement::updateTimestamp(QString name)
{
    QString time=QString::number(QDateTime::currentDateTime().toTime_t());
    for(int i=0;i<userTimestamp.size();i++)
    {
        if(name==userPlayer[i])
        {
            userTimestamp[i]=time;
        }
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

bool UserManagement::closeProgram()
{
    return close;
}

double UserManagement::getIndex()
{
    if(userTimestamp.size()>0)
    {
        double highest=0;
        for(int i=0;i<userTimestamp.size();i++)
        {
            if(highest<userTimestamp[i].toDouble())
                highest=userTimestamp[i].toDouble();
        }
        for(int i=0;i<userTimestamp.size();i++)
        {
            if(userTimestamp[i].toDouble()==highest)
                return i;
        }
    }
}

double UserManagement::getNameIndex(QString name)
{
    for(int i=0;i<userPlayer.size();i++)
    {
        if(name==userPlayer[i])
            return i;
    }
}

QStringList UserManagement::userSort()
{
    int totalSize=userPlayer.size();
    QStringList sortedTimes=userTimestamp;
    if(userPlayer.size()>0)
    {
        sortedTimes.sort();
        QStringList sortedNames;
        for(int n=totalSize;n>0;n--)
        {
            for(int i=0;i<userPlayer.size();i++)
            {
                if(sortedTimes[n-1]==userTimestamp[i])
                    if(userPlayer[i]!="NULL")
                        sortedNames.append(userPlayer[i]);
            }
        }
        return sortedNames;
    }
}
