#include "gamedisplay.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsPixmapItem>

GameDisplay::GameDisplay(QWidget *parent) :
    QGraphicsView(parent)
{
    scene1=0;
    xCoord=0;
    yCoord=0;
    plantType=0;
    event=0;
    mouseEvent=0;
    sunFlowerIndex=0;
    zombieIndex=0;
    zombiesFinished=true;
    zombieAttackDelay=0;
    plantAttackDelay=20;
    sunflowerTimer = new QTimer(this);
    sunflowerTimer->start(100);
    this->connect(this->sunflowerTimer,SIGNAL(timeout()),this,SLOT(sunFlowerSun()));
    connect(this,SIGNAL(zombieAttack(Zombies*,Plants*)),this,SLOT(zombieHitPlant(Zombies*,Plants*)));
    connect(this,SIGNAL(plantAttack(Zombies*,Plants*)),this,SLOT(plantShootZombie(Zombies*,Plants*)));
    connect(this,SIGNAL(lawnmowerAttack(Zombies*)),this,SLOT(moveLawnmower(Zombies*)));
//    moveLawnmower = new QTimer(this);
//    connect(moveLawnmower,SIGNAL(timeout()),scene1,SLOT(advance()));
}



QString GameDisplay::mainScreen()
{
    QString screen(homePath.currentPath()+"/mainscreen3.png");
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
        std::cout<<plantType<<std::endl;
}

int GameDisplay::getPlantType()
{
    return plantType;
}

int GameDisplay::getRows(int i)
{
    if(i==0)
        i++;
    for(int n=0;n<userLevel.size();n++)
    {
        if(i==levelLevel[n].toInt())
            return levelRows[n].toInt();
    }
    return 0;
}

int GameDisplay::zombiesInfrontOfPlants(Plants *plant)
{
    int counter=0;
    for(int i=0;i<zombieVector.size();i++)
    {
        if(zombieVector[i]->getX()>=plant->getX()&&zombieVector[i]->getY()==plant->getY())
            counter++;
    }
    return counter;
}

void GameDisplay::setLevel(int i)
{
    QPen grid=QPen(Qt::black);
    QBrush dirt(QColor(102,51,0));
    QBrush grass(QColor(0,153,0));
    QBrush lawnmower(QColor(160,160,160));
    for(int row=0;row<500;row+=100)
    {
        scene1->addRect(0,row,90,100,grid,lawnmower);

    }
   switch(i)
   {
   case 1:
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,100,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,200,90,100,grid,grass);
       }

       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,300,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,400,90,100,grid,dirt);
       }
       l = new Lawnmower(0,200);
       lawnmowerVector.push_back(l);
       scene()->addItem(l);
       break;
   case 3:
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,400,90,100,grid,dirt);
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
           scene1->addRect(column,0,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene1->addRect(column,400,90,100,grid,grass);
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

bool GameDisplay::cellEmpty(int x, int y)
{
    return grid[y/100][x/90];
}

void GameDisplay::advance(int phase)
{

}

void GameDisplay::zombieHitPlant(Zombies *zombie, Plants *plant)
{
    if(zombieAttackDelay%5==0)
    {
        if(plant->getLife()!=0)
            plant->loseHealth(zombie->getAttack());
        else
        {
            grid[plant->getY()/100][plant->getX()/90]=true;
            plant->setPosition(-1,-1);
            plant->setStatus(true);
            scene()->removeItem(plant);
            zombie->setMovement(true);
        }
    }
    zombieAttackDelay++;
}

void GameDisplay::plantShootZombie(Zombies *zombie, Plants *plant)
{
    if(plant->getLife()>0)
    {
    if(plantAttackDelay%(35/**zombiesInfrontOfPlants(plant)*/)==0)
    {
        b = new Bullets(plant->getType(),plant->getX(),plant->getY());
        bulletVector.push_back(b);
        scene()->addItem(b);
    }
    plantAttackDelay++;
    for(int i=0;i<bulletVector.size();i++)
    {
        bulletVector[i]->slideBullet();
        if(zombie->inArea(bulletVector[i]->getX(),bulletVector[i]->getY())&&zombie->getLife()>0)
        {

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
}


void GameDisplay::mousePressEvent(QMouseEvent *click)
{
    std::cout<<plantType<<std::endl;
    emit mouse();
    qDebug() << click->pos();
    if(cellEmpty(click->x(),click->y()))
    {
        switch(plantType)
        {
        case 1:
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(1,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(2,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(3,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(4,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(5,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                {
                        p = new Plants(6,x,y);
                        plantVector.push_back(p);
                        plantType=0;
                        subtractSunPoints(p->getCost());
                        scene()->addItem(p);
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
                    if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                    {
                            p = new Plants(7,x,y);
                            plantVector.push_back(p);
                            plantType=0;
                            subtractSunPoints(p->getCost());
                            scene()->addItem(p);
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
                    if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100))
                    {
                            p = new Plants(8,x,y);
                            plantVector.push_back(p);
                            plantType=0;
                            subtractSunPoints(p->getCost());
                            scene()->addItem(p);
                            break;
                    }

                }
            }
            grid[click->y()/100][click->x()/90]=false;
            break;
        }
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
    for(int i=0;i<lawnmowerVector.size();i++)
    {
        if(lawnmowerVector[i]->getX()==800)
        {
            lawnmowerVector[i]->setPosition(-1,-1);
            scene()->removeItem(lawnmowerVector[i]);
        }
    }
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
    for(int i=0;i<zombieVector.size();i++)
    {
        if(zombieVector[i]->getX()<0&&zombieVector[i]->getY()!=-1)
        {
            std::cout<<"hi"<<std::endl;
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
                    //zombieHitPlant(zombieVector[i],plantVector[n]);

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
                    scene()->removeItem(plantVector[n]);
                    scene()->removeItem(zombieVector[i]);
                }
  //cherry bomb activates based on zombie            // if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY()&&plantVector[n]->getType()==3)
                if(plantVector[n]->getType()==3)
                {
                    for(int m=0;m<zombieVector.size();m++)
                    {
                        if((zombieVector[m]->getX()>=plantVector[n]->getX()-90)&&(zombieVector[m]->getX()<plantVector[n]->getX()+180)&&(zombieVector[m]->getY()>=plantVector[n]->getY()-100)&&(zombieVector[m]->getY()<plantVector[n]->getY()+200))
                        {
                            zombieVector[m]->setPosition(-1,-1);
                            scene()->removeItem(zombieVector[m]);
                        }
                    }
                    grid[plantVector[n]->getY()/100][plantVector[n]->getX()/90]=true;
                    plantVector[n]->setPosition(-1,-1);
                    scene()->removeItem(plantVector[n]);
                }                

            }

        }
        zombieVector[i]->slideZombie();
        scene()->update();

    }
//MOVING THE LAWNMOWERS
//    for(int i=0;i<zombieVector.size();i++)
//    {
//        for(int n=0;n<lawnmowerVector.size();n++)
//        {
//            if(zombieVector[i]->getX()==lawnmowerVector[n]->getX()&&zombieVector[i]->getY()==lawnmowerVector[n]->getY())
//            {
//                while(lawnmowerVector[n]->getX()!=800)
//                {
//                    moveLawnmower->start(500);
//                    scene()->update();
//                }
//            }
//        }
//    }
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
                    zombieVector[n]->setPosition(-1,-1);
                    scene()->removeItem(zombieVector[n]);

                }
            }
            return;
        }

    }
    scene()->addPixmap(homePath.currentPath()+"/icons/youlose.png");
}
