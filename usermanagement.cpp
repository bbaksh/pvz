#include "usermanagement.h"

UserManagement::UserManagement()
{
    close=false;
}

void UserManagement::readUserData(QString fileName)
{
    //READS THE USER.CSV FILE AND PARSES IT ACCORDINGLY
    QFile players(fileName);
    if (players.open(QIODevice::ReadOnly))
    {
        QTextStream reader(&players);
        QString data=reader.readLine();
        QStringList values;
        while(!data.isNull())
        {
            if(data.contains(":"))//checks for garbage that doesnt have :
            {
                values=data.split(":");
                userTimestamp.append(values[0]);
                if(nameValidation(values[1]))//CHECKS FOR NAME VALIDATION
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
                if(levelValidation(values[2]))//CHECKS FOR LEVEL VALIDATION
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
            else
                break;
        }
        players.close();
    }
    else//CHECKS IF FILE ISNT READ (AKA DOESNT EXIST)
    {

        userPlayer.append("");
        userTimestamp.append("");
        userLevel.append("");
    }
    if(userPlayer.size()==0)//CHECKS IF FILE IS EMPTY
    {
        userPlayer.append("");
        userTimestamp.append("");
        userLevel.append("");
        QMessageBox invalidPlayerData;
        invalidPlayerData.setText("Error! “pvz_players” has invalid player data!\nThe program will run with default settings.\nPlease create a new user.");
        invalidPlayerData.setStandardButtons(QMessageBox::Ok);
        invalidPlayerData.exec();
    }
}

void UserManagement::readLevelData(QString fileName)
{

    //READS THE LEVELS INFORMATION AND PARSES IT ACORDDINGLY
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
            QStringList sequenceValues;//used to append in for loop
            sequenceValues=values[1].split(",");
            for(int i=0;i<sequenceValues.size();i++)
            {
                levelSequence.append(sequenceValues[i]);
            }
            levelSequenceNumber.append(levelSequence);//MAKES A LIST OF SEQUENCES
            levelSequence.clear();
            levelRows.append(values[2]);
            levelStart.append(values[3]);
            levelInterval.append(values[4]);
            levelDecrement.append(values[5]);
             data = reader.readLine();
        }
        levels.close();
    }
    else
    {
        close=true;
    }

}

void UserManagement::createUser(QString name)
{
    //CREATES A USER
    QString time=QString::number(QDateTime::currentDateTime().toTime_t());//GETS A CURRENT TIMESTAMP
    userTimestamp.append(time);
    if(nameValidation(name))
    {
        //CUSTOM MESSAGE BOX TO CONFIRM USER CREATION
        QMessageBox invalidName;
        invalidName.setText("Are you sure you want to create this user?");
        QAbstractButton *okayButton =invalidName.addButton(QObject::tr("OKAY"),QMessageBox::ActionRole);
        QAbstractButton *cancelButton =invalidName.addButton(QObject::tr("CANCEL"),QMessageBox::ActionRole);
        invalidName.exec();
        if(invalidName.clickedButton() == okayButton)
        {
            userPlayer.append(name);
            userLevel.append("1");
        }
        if(invalidName.clickedButton()==cancelButton)
        {
            userPlayer.append("");
            userLevel.append("");
        }
    }
    else
        {
        userPlayer.append("");
        userLevel.append("");
        }
        userSort();
}

void UserManagement::deleteUser(int index)//SETS USER INFO TO NULL (THIS WONT GET SAVED IN THE SAVE FUNCTION)
{
  userLevel[index]="NULL";
  userPlayer[index]="NULL";
  userTimestamp[index]="NULL";
}

void UserManagement::saveUsers(QString fileName)
{
    //SAVES THE FILE BY WRITING A NEW ONE WITH THE APPROPRIATE INFORMATION
    QFile players(fileName);
    if (players.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream write(&players);
        for(int i=0; i<userPlayer.size();i++)
        {
            if(userTimestamp[i]!="NULL"&&userPlayer[i]!="NULL")//CHECKS THAT THE USER HASNT BEEN DELETED
            write<<userTimestamp[i]<<":"<<userPlayer[i]<<":"<<userLevel[i]<<"\r\n";
        }
        players.close();
    }

}

void UserManagement::updateTimestamp(QString name)
{
    //UPDATE USER TIMESTAMP BASED ON WHAT WAS SELECTED LAST
    QString time=QString::number(QDateTime::currentDateTime().toTime_t());//GET CURRENT TIMESTAMP
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
//    if(name.size()<10)
//    {
//        for(int i=0;i<name.size();i++)
//        {
//            if(name[i].isLetterOrNumber())                    //OLD VALIDIATION HERE
//                valid=true;
//            else
//            {
//                valid=false;
//                break;
//            }
//        }
//    }
    if(name.size()<10)//NEW VALIDATION BASED ON ALPHANUMERIC CHANGES IN THE PROJECT
        valid=true;
    return valid;
}

bool UserManagement::levelValidation(QString level)
{
    //CHECKS IF A LEVEL IS VALID
    bool valid=false;
    for(int i=0;i<level.size();i++)
    {
        if(level[i].isDigit()&&level.toInt()>=0&&level.toInt()<=100)//MAKES SURE LEVEL IS A NUMBER AND BETWEEN 0-100
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
    //gets the index of the most current user (highest timestamp)
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
    //gets the index of the current player selected
    for(int i=0;i<userPlayer.size();i++)
    {
        if(name==userPlayer[i])
            return i;
    }
}

QStringList UserManagement::userSort()
{
    //sorts the usernames by timestamp
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
                    {
                        sortedNames.append(userPlayer[i]);

                    }
                else
                        break;
            }
        }
        while(sortedNames.size()>5)//only takes the top 5 for the combobox
        {
            sortedNames.pop_back();
        }
        return sortedNames;
    }
}
