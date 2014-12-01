#include "gamedisplay.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsPixmapItem>

int GameDisplay::getCooldown(int i)
{
    return cooldowns[i].elapsed();
}

GameDisplay::~GameDisplay()
{
    //TAKE CARE OF MEMORY LEAKS AND DANGLING POINTERS
    for(int i=0;i<plantVector.size();i++)
    {
        delete plantVector[i];
    }
    delete p;
    p=0;
    for(int i=0;i<zombieVector.size();i++)
    {
        delete zombieVector[i];
    }
    delete z;
    z=0;
    for(int i=0;i<sunVector.size();i++)
    {
        delete sunVector[i];
    }
    for(int i=0;i<lawnmowerVector.size();i++)
    {
        delete lawnmowerVector[i];
    }
    delete l;
    l=0;
    for(int i=0;i<bulletVector.size();i++)
    {
        delete bulletVector[i];
    }
    delete b;
    b=0;
    delete sunflowerTimer;
    sunflowerTimer=0;
    delete scene1;
    scene1=0;
    delete event;
    event=0;
    delete mouseEvent;
    mouseEvent=0;
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

void GameDisplay::setLevel(int i)//sets up the grid based on level
{
    QPen grid=QPen(Qt::black);//
    QBrush dirt(QColor(102,51,0));// handles the colors of the grid
    QBrush grass(QColor(0,153,0));//
    QBrush lawnmower(QColor(160,160,160));//
    for(int row=0;row<500;row+=100)
    {
        scene()->addRect(0,row,90,100,grid,lawnmower);

    }
   switch(i)
   {
   case 1://sets 1 row of grass, rest is dirt
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
   case 3://sets middle 3 rows of grass, rest is dirt
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
   case 5://sets 5 rows of grass
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

void GameDisplay::levelRestart()//sets the game status back to the beginning of the level
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
    if(plant->getLife()<=0)//if plant is dead
    {
        grid[plant->getY()/100][plant->getX()/90]=true;
        plant->setPosition(-1,-1);
        plant->setStatus(true);//sets plant dead
        scene()->removeItem(plant);
        zombie->setOpacity(1);
        zombie->setMovement(true);//lets zombie move again
    }
    if(zombie->timeElapsed()>=500)//checks if the zombie can attack again
    {
        zombie->resetAttackRate();
        if(plant->getLife()!=0)
        {
            zombie->setOpacity(.5);//shows a zombie is attacking
            plant->loseHealth(zombie->getAttack());//zombie damages plant
        }
    }

}

void GameDisplay::plantShootZombie(Zombies *zombie, Plants *plant)
{
    if(plant->getLife()>0)
    {
    if(plant->timeElapsed()>=1500)//makes a new bullet to shoot every 1.5 seconds
    {
        b = new Bullets(plant->getType(),plant->getX(),plant->getY());
        bulletVector.push_back(b);
        scene()->addItem(b);
        plant->restartAttackRate();

    }
    for(int i=0;i<bulletVector.size();i++)
    {
        bulletVector[i]->slideBullet();//shoots bullet
        if(zombie->inArea(bulletVector[i]->getX(),bulletVector[i]->getY())&&zombie->getLife()>0)//checks if a bullet hits a zombie
        {
            if(bulletVector[i]->getType()==6)//if the bullet is from a snow pea reduce zombie speed once
            {
                zombie->loseSpeed();
            }
            zombie->loseHealth(bulletVector[i]->getDamage());//reduce zombie health based on bullet damage
            scene()->removeItem(bulletVector[i]);
            bulletVector[i]->setPosition(-1,-1);
        }
        if(zombie->getLife()<=0)//if a zombie dies
        {
            scene()->removeItem(zombie);
            zombie->setPosition(-1,-1);
            for(int n=0;n<bulletVector.size();n++)
            {
                if(bulletVector[n]->getX()!=-1&&bulletVector[n]->getY()!=-1)//if a bullet has hit, we remove it so it doesnt hit a zombie that has died
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
    //CHECKS IF LEVEL IS COMPLETE
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
    if(levelComplete)//SET THE GAME PARAMETERS FOR NEXT LEVEL
    {
        zombieIndex=0;
        zombiesFinished=true;
        levelComplete=false;
        zombieVector.clear();
        plantVector.clear();
        bulletVector.clear();
        sunVector.clear();
        lawnmowerVector.clear();
        emit startNextLevel();//this signals the next level to start
    }
}


void GameDisplay::mousePressEvent(QMouseEvent *click)
{
        switch(plantType)//switch statement used to place a plant where you click
        {
        case 1://pea shooter
    {
        for(int x=0;x<900;x+=90)
        {
            for(int y=0;y<500;y+=100)
            {
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                    if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&cellEmpty(click->x(),click->y()))//tracks where you click on the grid, then assigns the plant to be placed on a fixed coordinate for that cell
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
                        if(click->x()>x&&click->x()<(x+90)&&click->y()>y&&click->y()<(y+100)&&plantVector[i]->getType()==1&&plantVector[i]->getX()==x&&plantVector[i]->getY()==y)//tracks if a peashooter has been placed on the grid. if you click the same spot, a repeater will be placed and the peashooter gets removed
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
        if(sunVector[i]->areaX(click->x())&&sunVector[i]->areaY(click->y()))//checks if you have clicked on a sun
        {
            sunVector[i]->setClicked();//moves the sun so you cant click on it again (if you dont do this, you wont see the sun but you can still get sun points)
            scene()->removeItem(sunVector[i]);
            addSunPoints(25);
        }
    }
}

void GameDisplay::dropSun()
{

    xCoord=rand()%900;
    yCoord=rand()%500;
    while(!(xCoord>100&&xCoord<835&&yCoord>30&&yCoord<430))//generate a random set of coordinates on the screen
    {
        xCoord=rand()%900;
        yCoord=rand()%500;
    }
    s = new Sun(xCoord,yCoord,homePath.currentPath()+"/icons/sun.png",1);//create a sun based on the coordinates, and identify its a falling sun (type 1)
    sunVector.push_back(s);
    scene()->addItem(s);

}

void GameDisplay::sunFlowerSun()
{
    for(int i=0;i<plantVector.size();i++)
    {
        if(plantVector[i]->getType()==2&&plantVector[i]->getLife()>0&&plantVector[i]->okayToPlant())//checks if a sunflower is ready to plant a sun
        {

            s = new Sun(plantVector[i]->getX(),plantVector[i]->getY(),homePath.currentPath()+"/icons/sun.png",2);//make it a sunflower sun (type 2)
            sunVector.push_back(s);
            scene()->addItem(s);
        }
    }
}

void GameDisplay::spawnZombies()
{
    if(zombiesFinished)//if the sequence isnt finished spawn the next zombie
    {
        if(getCurrentLevel()==1)//spawns it according to grass rows in the level
        {
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,200);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
        if(getCurrentLevel()==2)//spawns it according to grass rows in the level
        {
                int randomRow;
                randomRow=rand()%3+1;
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,100*randomRow);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
        if(getCurrentLevel()>2)//spawns it according to grass rows in the level
        {
                int randomRow;
                randomRow=rand()%5;
                z = new Zombies(levelSequenceNumber[getCurrentLevel()-1].at(zombieIndex).toInt(),900,100*randomRow);
                zombieVector.push_back(z);
                scene()->addItem(z);
        }
    }
    if(zombieIndex!=levelSequenceNumber[getCurrentLevel()-1].size()-1)//checks to see if current zombie is the last
    {
        zombieIndex++;//if not, then move onto the next zombie
    }
    else
        zombiesFinished=false;//if all zombies are spawned, change the status
}

void GameDisplay::moveZombiesAndPlants()
{

    for(int i=0;i<lawnmowerVector.size();i++)
    {
        if(lawnmowerVector[i]->getX()==800&&lawnmowerVector[i]->timeElapsed()>=1500)//removes a lawnmower 1.5 seconds if it was triggered
        {
            lawnmowerVector[i]->setPosition(-1,-1);
            scene()->removeItem(lawnmowerVector[i]);
        }
    }
    for(int i=0;i<zombieVector.size();i++)
    {
        if(zombieVector[i]->getX()<0&&zombieVector[i]->getY()!=-1)//triggers a lawnmower if a zombie steps on it
        {
            emit lawnmowerAttack(zombieVector[i]);
        }
        for(int n=0;n<plantVector.size();n++)
        {
            if(zombieVector[i]->getX()!=-1&&plantVector[n]->getX()!=-1)//only cycles through plants and zombies that are visible to the scene
            {
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY())//checks if a zombie encountered a plant
                {
                    zombieVector[i]->setMovement(false);//stops movement
                    emit zombieAttack(zombieVector[i],plantVector[n]);
                }
                else
                {
                    if(plantVector[n]->getStatus())//checks if the plant died
                        zombieVector[i]->setMovement(true);//allows zombie to move again
                }
                if(zombieVector[i]->getX()>=plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY())//checks if a zombie is infront a plant
                {
                    if((plantVector[n]->getType()==1||plantVector[n]->getType()==6||plantVector[n]->getType()==8))//if the plant is ranged, attack it
                    {
                        emit plantAttack(zombieVector[i],plantVector[n]);
                    }
                }
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY()&&plantVector[n]->getType()==5)//checks if a zombie triggers potato mine
                {
                    grid[plantVector[n]->getY()/100][plantVector[n]->getX()/90]=true;//allow to plant here after mine disappears
                    plantVector[n]->setPosition(-1,-1);
                    zombieVector[i]->setPosition(-1,-1);
                    zombieVector[i]->loseHealth(plantVector[n]->getDamage());
                    scene()->removeItem(plantVector[n]);
                    scene()->removeItem(zombieVector[i]);
                }
                if(plantVector[n]->getType()==3&&plantVector[n]->timeElapsed()>=1000)//if a cherry bomb is placed and 1 second passes, trigger it
                {
                    for(int m=0;m<zombieVector.size();m++)
                    {
                        if((zombieVector[m]->getX()>=plantVector[n]->getX()-90)&&(zombieVector[m]->getX()<plantVector[n]->getX()+180)&&(zombieVector[m]->getY()>=plantVector[n]->getY()-100)&&(zombieVector[m]->getY()<plantVector[n]->getY()+200))//checks for zombies in a 3x3 radius of the cherry bomb
                        {
                            zombieVector[m]->loseHealth(plantVector[n]->getDamage());//kills them acordingly
                            zombieVector[m]->setPosition(-1,-1);
                            scene()->removeItem(zombieVector[m]);
                        }
                    }
                    grid[plantVector[n]->getY()/100][plantVector[n]->getX()/90]=true;//allows to plant on the grid again
                    plantVector[n]->setPosition(-1,-1);
                    scene()->removeItem(plantVector[n]);
                }
                if(zombieVector[i]->getX()==plantVector[n]->getX()&&zombieVector[i]->getY()==plantVector[n]->getY()&&plantVector[n]->getType()==7)//checks if a zombie is on chomper
                {
                    if(plantVector[n]->okayToChomp())//checks if chomper can attack
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
        zombieVector[i]->slideZombie();//move the zombies
        scene()->update();//refresh the scene
    }
    for(int i=0;i<sunVector.size();i++)
    {
        if(sunVector[i]->getType()==1)//see what random suns have spawned (not sunflower suns)
        {
            sunVector[i]->slideSun();//slide random suns
            scene()->update();
        }
    }

}

void GameDisplay::moveLawnmower(Zombies *zombie)
{
    for(int i=0;i<lawnmowerVector.size();i++)
    {
        if(lawnmowerVector[i]->getX()>zombie->getX()&&lawnmowerVector[i]->getY()==zombie->getY())//checks if a zombie triggers a lawnmower
        {
            lawnmowerVector[i]->slideLawnmower();//move lawnmower
            for(int n=0;n<zombieVector.size();n++)
            {
                if(zombieVector[n]->getY()==lawnmowerVector[i]->getY())//checks what zombies are in the row of the lawnmower when activated
                {
                    zombieVector[n]->loseHealth(zombieVector[n]->getLife());//kills the zombies
                    zombieVector[n]->setPosition(-1,-1);
                    scene()->removeItem(zombieVector[n]);

                }
            }
            return;
        }

    }
    scene()->addPixmap(homePath.currentPath()+"/icons/youlose.png");//displays an image when you lose
    if(!restartLevel)//restarts the level 1 second after you see the "you lose" picture
    {
        timeToRestart.start();
        restartLevel=true;
    }
    if(restartLevel&&timeToRestart.elapsed()>1000)//restarts the level 1 second after you see the "you lose" picture
    {
        restartLevel=false;
        levelRestart();
        sunPoints=100;
        emit startThisLevel();
    }
}
