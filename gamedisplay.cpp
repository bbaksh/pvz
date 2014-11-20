#include "gamedisplay.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QGraphicsPixmapItem>

GameDisplay::GameDisplay(QWidget *parent) :
    QGraphicsView(parent)
{
    xCoord=0;
    yCoord=0;
    plantType=0;
}


QString GameDisplay::mainScreen()
{
    QString screen(homePath.currentPath()+"/mainscreen3.png");
    return screen;
}

void GameDisplay::setPlant(int i)
{

}

void GameDisplay::setPlantType(int i)
{
    plantType=i;
}

double GameDisplay::getPlantType()
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
        scene->addRect(0,row,90,100,grid,lawnmower);
    }
   switch(i)
   {
   case 1:

       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,100,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,300,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,400,90,100,grid,dirt);
       }
       break;
   case 3:
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,0,90,100,grid,dirt);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,400,90,100,grid,dirt);
       }
       break;
   case 5:
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,0,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,100,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,200,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,300,90,100,grid,grass);
       }
       for(int column=90;column<900;column+=90)
       {
           scene->addRect(column,400,90,100,grid,grass);
       }
       break;
    }
}

void GameDisplay::mousePressEvent(QMouseEvent *click)
{
    //int i=click->pos();
    this->click=click->pos();
    //qDebug() << this->click;
    xCoord=click->x();
    yCoord=click->y();
    //scene->addEllipse(0,10,10,10);
    //std::cout<<click->x()<<","<<click->y()<<std::endl;
}
