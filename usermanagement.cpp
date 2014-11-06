#include "usermanagement.h"

UserManagement::UserManagement()
{
}

void UserManagement::readUserData()
{
    QFile players(userName);
    if (players.open(QIODevice::ReadOnly))
    {
        QTextStream reader(&players);
        QString data=reader.readLine();
        QStringList values;
        while(!data.isNull())
        {
            values=data.split(":");
            userTimestamp.append(values[0]);
            userPlayer.append(values[1]);
            userLevel.append(values[2]);
            data = reader.readLine();
        }
        players.close();
    }
}

void UserManagement::readLevelData()
{
    QFile levels(levelName);
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
