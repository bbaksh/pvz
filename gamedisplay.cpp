#include "gamedisplay.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsPixmapItem>

int GameDisplay::getCooldown(int i)
{
    return cooldowns[i].elapsed();
}

GameDisplay::GameDisplay(QWidget *parent) :
    QGraphicsView(parent)
{
    scene1=0;
    xCoord=0;
    yCoord=0;
    plantType=0;
    event=0;
    mouseEvent=0;
    zombieIndex=0;
    zombiesFinished=true;
    levelComplete=false;
    restartLevel=false;
    sunflowerTimer = new QTimer(this);
    sunflowerTimer->start(100);
    this->connect(this->sunflowerTimer,SIGNAL(timeout()),this,SLOT(sunFlowerSun()));
    connect(this,SIGNAL(zombieAttack(Zombies*,Plants*)),this,SLOT(zombieHitPlant(Zombies*,Plants*)));
    connect(this,SIGNAL(plantAttack(Zombies*,Plants*)),this,SLOT(plantShootZombie(Zombies*,Plants*)));
    connect(this,SIGNAL(lawnmowerAttack(Zombies*)),this,SLOT(moveLawnmower(Zombies*)));
    for(int i=0;i<8;i++)
    {
        cooldowns[i].start();
    }
}



QString GameDisplay::mainScreen()
{
    QString screen(homePath.currentPath()+"/mainscreen.png");
    return screen;
}

void GameDisplay::setGridFromLevel()
{
    for(int i=0;i<5;i++)
    {
        for(int n=0;n<10;n++)
        {
            grid[i][n]=false;
        }
    }
    if(getCurrentLevel()==1)
    {
        for(int i=1;i<10;i++)
        {
            grid[2][i]=true;
        }
    }
    if(getCurrentLevel()==2)
    {
        for(int i=1;i<4;i++)
        {
            for(int n=1;n<10;n++)
            {
                grid[i][n]=true;
            }
        }
    }
    if(getCurrentLevel()>2)
    {
        for(int i=0;i<5;i++)
        {
            for(int n=1;n<10;n++)
            {
                grid[i][n]=true;
            }
        }
    }
}


void GameDisplay::setPlantType(const int i)
{
    plantType=i;
}

int GameDisplay::getRows(int i)
{
    if(i==0)
        i++;
    for(int n=0;n<levelLevel.size();n++)
    {
        if(i==levelLevel[n].toInt())
            return levelRows[n].toInt();
    }
    return 0;
}

void GameDisplay::setLevel(int i)
{
    QPen grid=QPen(Qt::black);
    QBrush dirt(QColor(102,51,0));
    QBrush grass(QColor(0,153,0));
    QBrush lawnmower(QColor(160,160,160));
    for(int row=0;row<500;row+=100)
    {
        scene()->addRect(0,row,90,100,grid,lawnmower);

    }
   switch(i)
   {
   case 1:
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,100,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,200,90,100,grid,grass);
       }

       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,300,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,400,90,100,grid,dirt);
       }
       l = new Lawnmower(0,200);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       break;
   case 3:
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,400,90,100,grid,dirt);
       }
       l = new Lawnmower(0,100);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,200);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,300);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       break;
   case 5:
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,0,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene()->addRect(column,400,90,100,grid,grass);
       }
       l = new Lawnmower(0,0);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,100);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,200);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,300);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       l = new Lawnmower(0,400);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       break;
   }
   setGridFromLevel();
}

void GameDisplay::levelRestart()
{
    zombieIndex=0;
    zombiesFinished=true;
    levelComplete=false;
    zombieVector.clear();
    plantVector.clear();
    bulletVector.clear();
    sunVector.clear();
    lawnmowerVector.clear();
}

bool GameDisplay::cellEmpty(int x, int y)
{
    return grid[y/100][x/90];
}

void GameDisplay::advance()
{

}

void GameDisplay::zombieHitPlant(Zombies *zombie, Plants *plant)
{
    if(plant->getLife()<=0)
    {
        grid[plant->getY()/100][plant->getX()/90]=true;
        plant->setPosition(-1,-1);
        plant->setStatus(true);
        scene()->removeItem(plant);
        zombie->setMovement(true);
    }
    if(zombie->timeElapsed()>=500)
    {
        zombie->resetAttackRate();
        if(plant->getLife()!=0)
            plant->loseHealth(zombie->getAttack());
    }

}

void GameDisplay::plantShootZombie(Zombies *zombie, Plants *plant)
{
    if(plant->getLife()>0)
    {
    if(plant->timeElapsed()>=1500)
    {
        b = new Bullets(plant->getType(),plant->getX(),plant->getY());
        bulletVector.push_back(b);
        scene()->addItem(b);
        plant->restartAttackRate();

    }
    for(int i=0;i<bulletVector.size();i++)
    {
        bulletVector[i]->slideBullet();
        if(zombie->inArea(bulletVector[i]->getX(),bulletVector[i]->getY())&&zombie->getLife()>0)
        {
            if(bulletVector[i]->getType()==6)
            {
                zombie->loseSpeed();
            }
            zombie->loseHealth(bulletVector[i]->getDamage());
            scene()->removeItem(bulletVector[i]);
            bulletVector[i]->setPosition(-1,-1);
        }
        if(zombie->getLife()<=0)
        {
            scene()->removeItem(zombie);
            zombie->setPosition(-1,-1);
            for(int n=0;n<bulletVector.size();n++)
            {
                if(bulletVector[n]->getX()!=-1&&bulletVector[n]->getY()!=-1)
                {
                    scene()->removeItem(bulletVector[n]);
                    bulletVector[n]->setPosition(-1,-1);
                }
            }
        }
    }
    }

    scene()->update();

}

void GameDisplay::timerTracking()
{
    //SUN DISAPPEARING TIMERS
    for(int i=0;i<sunVector.size();i++)
    {
        if(sunVector[i]->timeEllapsed()>7500&&sunVector[i]->getX()!=-1)
        {
            scene()->removeItem(sunVector[i]);
            sunVector[i]->setClicked();
        }
    }

    if(zombieVector.size()==levelSequenceNumber[getCurrentLevel()-1].size())
    {
        for(int i=0;i<zombieVector.size();i++)
        {
            if(zombieVector[i]->getLife()<=0)
            {
                levelComplete=true;
            }
            else
            {
                levelComplete=false;
                break;
            }
         }
    }
    if(levelComplete)
    {
        zombieIndex=0;
        zombiesFinished=true;
        levelComplete=false;
        zombieVector.clear();
        plantVector.clear();
        bulletVector.clear();
        sunVector.clear();
        lawnmowerVector.clear();
        emit startNextLevel();
    }
}


void GameDisplay::mousePressEvent(QMouseEvent *click)
{
        switch(plantType)
        {
        case 1:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(1,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[0].restart();
                        emit disableButton(1);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 2:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(2,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[1].restart();
                        emit disableButton(2);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 3:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(3,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[2].restart();
                        emit disableButton(3);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 4:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(4,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[3].restart();
                        emit disableButton(4);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 5:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(5,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[4].restart();
                        emit disableButton(5);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 6:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                {
                        p = new Plants(6,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
                        cooldowns[5].restart();
                        emit disableButton(6);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 7:
        {
            for(int x=0;x<900;x+=90)
            {
                for(int y=0;y<500;y+=100)
                {
                    if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))
                    {
                            p = new Plants(7,x,y);
                            plantVector.push_back(p);
                            plantType=0;
                            subtractSunPoints(p->getCost());
                            scene()->addItem(p);
                            cooldowns[6].restart();
                            emit disableButton(7);
                            break;
                    }

                }
            }
            grid[click->y()/100][click->x()/90]=false;
            break;
        }
        case 8:
        {
            for(int x=0;x<900;x+=90)
            {
                for(int y=0;y<500;y+=100)
                {
                    for(int i=0;i<plantVector.size();i++)
                    {
                        if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&plantVector[i]->getType()==1&&plantVector[i]->getX()==x&&plantVector[i]->getY()==y)
                        {
                            plantVector[i]->setPosition(-1,-1);
                            scene()->removeItem(plantVector[i]);

                            p = new Plants(8,x,y);
                            plantVector.push_back(p);
                            plantType=0;
                            subtractSunPoints(p->getCost());
                            scene()->addItem(p);
                            cooldowns[7].restart();
                            emit disableButton(8);
                            break;
                        }
                    }

                }
            }
            grid[click->y()/100][click->x()/90]=false;
            break;
        }
    }
    for(int i=0;i<sunVector.size();i++)
    {
        if(sunVector[i]->areaX(click->x())&&sunVector[i]->areaY(click->y()))
        {
            sunVector[i]->setClicked();
            scene()->removeItem(sunVector[i]);
            addSunPoints(25);
        }
    }
}

void GameDisplay::dropSun()
{

    xCoord=rand()%900;
    yCoord=rand()%500;
    while(!(xCoord>100&&xCoord<835&&yCoord>30&&yCoord<430))
    {
        xCoord=rand()%900;
        yCoord=rand()%500;
    }
    s = new Sun(xCoord,yCoord,homePath.currentPath()+"/icons/sun.png",1);
    sunVector.push_back(s);
    scene()->addItem(s);

}

void GameDisplay::sunFlowerSun()
{
    for(int i=0;i<plantVector.size();i++)
    {
        if(plantVector[i]->getType()==2&&plantVector[i]->getLife()>0&&plantVector[i]->okayToPlant())
        {

            s = new Sun(plantVector[i]->getX(),plantVector[i]->getY(),homePath.currentPath()+"/icons/sun.png",2);
            sunVector.push_back(s);
            scene()->addItem(s);
        }
    }
}

void GameDisplay::spawnZombies()
{
    if(zombiesFinished)
    {
        if(getCurrentLevel()==1)
        {
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,200);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
        if(getCurrentLevel()==2)
        {
                int randomRow;
                randomRow=rand()%3+1;
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,100*randomRow);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
        if(getCurrentLevel()>2)
        {
                int randomRow;
                randomRow=rand()%5;
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,100*randomRow);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
    }
    if(zombieIndex!=levelSequenceNumber[getCurrentLevel()-1].size()-1)
    {
        zombieIndex++;
    }
    else
        zombiesFinished=false;
}

void GameDisplay::moveZombiesAndPlants()
{

    for(int i=0;i<lawnmowerVector.size();i++)
    {
        if(lawnmowerVector[i]->getX()==800&&lawnmowerVector[i]->timeElapsed()>=1500)
        {
            lawnmowerVector[i]->setPosition(-1,-1);
            scene()->removeItem(lawnmowerVector[i]);
        }
    }
    for(int i=0;i<zombieVector.size();i++)
    {
        if(zombieVector[i]->getX()<0&&zombieVector[i]->getY()!=-1)
        {
            emit lawnmowerAttack(zombieVector[i]);
        }
        for(int n=0;n<plantVector.size();n++)
        {
            if(zombieVector[i]->getX()!=-1&&plantVector[n]->getX()!=-1)
            {
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY())
                {
                    zombieVector[i]->setMovement(false);
                    emit zombieAttack(zombieVector[i],plantVector[n]);
                }
                else
                {
                    if(plantVector[n]->getStatus())
                        zombieVector[i]->setMovement(true);
                }
                if(zombieVector[i]->getX()>=plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY())
                {
                    if((plantVector[n]->getType()==1||plantVector[n]->getType()==6||plantVector[n]->getType()==8))
                    {
                        emit plantAttack(zombieVector[i],plantVector[n]);
                    }
                }
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY()&&plantVector[n]->getType()==5)
                {
                    grid[plantVector[n]->getY()/100][plantVector[n]->getX()/90]=true;
                    plantVector[n]->setPosition(-1,-1);
                    zombieVector[i]->setPosition(-1,-1);
                    zombieVector[i]->loseHealth(plantVector[n]->getDamage());
                    scene()->removeItem(plantVector[n]);
                    scene()->removeItem(zombieVector[i]);
                }
                if(plantVector[n]->getType()==3&&plantVector[n]->timeElapsed()>=1000)
                {
                    for(int m=0;m<zombieVector.size();m++)
                    {
                        if((zombieVector[m]->getX()>=plantVector[n]->getX()-90)&&(zombieVector[m]->getX()<plantVector[n]->getX()+180)&&(zombieVector[m]->getY()>=plantVector[n]->getY()-100)&&(zombieVector[m]->getY()<plantVector[n]->getY()+200))
                        {
                            zombieVector[m]->loseHealth(plantVector[n]->getDamage());
                            zombieVector[m]->setPosition(-1,-1);
                            scene()->removeItem(zombieVector[m]);
                        }
                    }
                    grid[plantVector[n]->getY()/100][plantVector[n]->getX()/90]=true;
                    plantVector[n]->setPosition(-1,-1);
                    scene()->removeItem(plantVector[n]);
                }
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY()&&plantVector[n]->getType()==7)
                {
                    if(plantVector[n]->okayToChomp())
                    {
                        zombieVector[i]->loseHealth(plantVector[n]->getDamage());
                        if(zombieVector[i]->getLife()<=0)
                        {
                            zombieVector[i]->setPosition(-1,-1);
                            scene()->removeItem(zombieVector[i]);
                        }

                    }
                }
            }

        }
        zombieVector[i]->slideZombie();
        scene()->update();
    }
    for(int i=0;i<sunVector.size();i++)
    {
        if(sunVector[i]->getType()==1)
        {
            sunVector[i]->slideSun();
            scene()->update();
        }
    }

}

void GameDisplay::moveLawnmower(Zombies *zombie)
{
    for(int i=0;i<lawnmowerVector.size();i++)
    {
        if(lawnmowerVector[i]->getX()>zombie->getX()&&lawnmowerVector[i]->getY()==zombie->getY())
        {
            lawnmowerVector[i]->slideLawnmower();
            for(int n=0;n<zombieVector.size();n++)
            {
                if(zombieVector[n]->getY()==lawnmowerVector[i]->getY())
                {
                    zombieVector[n]->loseHealth(zombieVector[n]->getLife());
                    zombieVector[n]->setPosition(-1,-1);
                    scene()->removeItem(zombieVector[n]);

                }
            }
            return;
        }

    }
    scene()->addPixmap(homePath.currentPath()+"/icons/youlose.png");
    if(!restartLevel)
    {
        timeToRestart.start();
        restartLevel=true;
    }
    if(restartLevel&&timeToRestart.elapsed()>1000)
    {
        restartLevel=false;
        levelRestart();
        sunPoints=100;
        emit startThisLevel();
    }
}
