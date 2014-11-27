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
    connect(this,SIGNAL(zombieAttack(Zombies*,Plants*)),this,SLOT(zombieHitPlant(Zombies*,Plants*)));

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

void GameDisplay::setPlant(int i)
{
    scene1->addRect(100,90,100,100);
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
}

void GameDisplay::setLevel(int i)
{
    QPen grid=QPen(Qt::black);
    QBrush dirt(QColor(102,51,0));
    QBrush grass(QColor(0,153,0));
    QBrush lawnmower(QColor(160,160,160));
//    if(i==0)
//        i++;
//    if(i>2)
//        i=3;
    for(int row=0;row<500;row+=100)
    {
        scene1->addRect(0,row,90,100,grid,lawnmower);

    }
   switch(i)
   {
   case 1:
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,200);
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
       break;
   case 3:
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,100);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,200);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,300);
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
       break;
   case 5:
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,0);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,100);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,200);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,300);
       scene()->addPixmap(QPixmap(homePath.currentPath()+"/icons/lawnmower.png"))->setPos(0,400);
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
       break;
   }
   setGridFromLevel();
}

bool GameDisplay::cellEmpty(int x, int y)
{
    return grid[y/100][x/90];
}

void GameDisplay::zombieHitPlant(Zombies *zombie, Plants *plant)
{
    if(zombieAttackDelay%5==0)
    {
        if(plant->getLife()!=0)
            plant->loseHealth(zombie->getAttack());
        else
        {
            plant->setPosition(-1,-1);
            plant->setStatus(true);
        }
    }
    zombieAttackDelay++;
}

void GameDisplay::mousePressEvent(QMouseEvent *click)
{
    std::cout<<plantType<<std::endl;
   // mouseEvent=click;
//    if(mouseEvent!=0)
        emit mouse();
    qDebug() << click->pos();
    if(cellEmpty(click->x(),click->y()))
    {
        switch(plantType)
        {
        case 1:
    {
        p = new Plants(1,100,4,9999,1,1.5,0,0,0,7.5,0,0);
        plantVector.push_back(p);
        plantType=0;
        subtractSunPoints(p->getCost());
        QGraphicsPixmapItem peashooter1(QPixmap(homePath.currentPath()+"/icons/peashooter1.png"));
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/peashooter1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        ;
        break;
    }
        case 2:
    {
        p = new Plants(2,50,4,0,0,24,0,0,0,7.5,1,0);
        plantVector.push_back(p);
        plantType=0;
        p->setPosition(click->x(),click->y());
        subtractSunPoints(p->getCost());
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/sunflower1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        sunflowerTimer = new QTimer(this);
        sunflowerTimer->start(7500);
        this->connect(this->sunflowerTimer,SIGNAL(timeout()),this,SLOT(sunFlowerSun()));
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 3:
    {
        p = new Plants(3,150,9999,1,90,1,3,0,1,50,0,0);
        plantVector.push_back(p);
        plantType=0;
        subtractSunPoints(p->getCost());
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/cherrybomb1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 4:
    {
        p = new Plants(4,50,72,0,0,0,0,0,0,30,0,0);
        plantVector.push_back(p);
        plantType=0;
        subtractSunPoints(p->getCost());
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/wallnut1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 5:
    {
        p = new Plants(5,25,4,1,90,15,0,0,1,7.5,0,0);
        plantVector.push_back(p);
        plantType=0;
        subtractSunPoints(p->getCost());
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/potatomine1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 6:
    {
        p = new Plants(6,175,4,9999,1,1.5,0,1,0,7.5,0,0);
        plantVector.push_back(p);
        plantType=0;
        subtractSunPoints(p->getCost());
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                {
                        scene()->addPixmap(homePath.currentPath()+"/icons/snowpea1.png")->setPos(x,y);
                        p->setPosition(x,y);
                        break;
                }

            }
        }
        grid[click->y()/100][click->x()/90]=false;
        break;
    }
        case 7:
        {
            p = new Plants(7,150,4,1,150,42,0,0,0,7.5,0,0);
            plantVector.push_back(p);
            plantType=0;
            subtractSunPoints(p->getCost());
            for(int x=0;x<900;x+=90)
            {
                for(int y=0;y<500;y+=100)
                {
                    if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                    {
                            scene()->addPixmap(homePath.currentPath()+"/icons/chomper1.png")->setPos(x,y);
                            p->setPosition(x,y);
                            break;
                    }

                }
            }
            grid[click->y()/100][click->x()/90]=false;
            break;
        }
        case 8:
        {
            p = new Plants(8,200,4,9999,2,1.5,0,0,0,7.5,0,1);
            plantVector.push_back(p);
            plantType=0;
            subtractSunPoints(p->getCost());
            for(int x=0;x<900;x+=90)
            {
                for(int y=0;y<500;y+=100)
                {
                    if(click->x()>=x&&click->x()<=(x+90)&&click->y()>=y&&click->y()<=(y+100))
                    {
                            scene()->addPixmap(homePath.currentPath()+"/icons/repeater1.png")->setPos(x,y);
                            p->setPosition(x,y);
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
        //if(sunVector[i]->getX()+n==click->x()&&sunVector[i]->getY()+n==click->y())
        if(sunVector[i]->areaX(click->x())&&sunVector[i]->areaY(click->y()))
        {
            sunVector[i]->setClicked();
            scene()->removeItem(sunVector[i]);
            addSunPoints(25);
           // break;
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
   // scene()->addPixmap(s->getPicture())->setPos(xCoord,yCoord);
   // scene()->addRect(s->boundingRect(),QPen(Qt::black),QBrush(s->getPicture()))->setPos(xCoord,yCoord);
    scene()->addItem(s);
}

void GameDisplay::sunFlowerSun()
{
    for(int i=0;i<plantVector.size();i++)
    {
        if(plantVector[i]->getType()==2)
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
    //        for(int i=0;i<levelSequenceNumber[getCurrentLevel()].size();i++)
    //        {
                int randomRow;
                randomRow=rand()%5;
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,100*randomRow);
                zombieVector.push_back(z);
                scene()->addItem(z);
    //        }
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
        for(int n=0;n<plantVector.size();n++)
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
//void GameDisplay::handlemouse(QEvent *mouse)
//{
//    if(mouse!=0)
//    {
//        mouseEvent=static_cast<QMouseEvent *>(mouse);
//    }
//    std::cout<<"gamedisplay event   "<<mouseEvent->pos().x()<<"       "<<mouseEvent->pos().y()<<std::endl;
//    xCoord=mouseEvent->x();
//    yCoord=mouseEvent->y();
//    if(plantType==1)
//    {
//        scene1->addEllipse(xCoord,yCoord,20,20,QPen(Qt::black),QBrush(Qt::red));
//        //plantType=0;
//    }

//    mouseEvent=0;
//}
