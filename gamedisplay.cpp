#include "gamedisplay.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>


GameDisplay::GameDisplay(QWidget *parent) :
    QGraphicsView(parent)
{
}


QString GameDisplay::mainScreen()
{
    QString screen(homePath.currentPath()+"/mainscreen3.png");
    return screen;
}

void GameDisplay::setLevel(int i)
{
    QPen grid=QPen(Qt::black);
    QBrush dirt(QColor(102,51,0));
    QBrush grass(QColor(0,153,0));
    QBrush lawnmower(QColor(160,160,160));
    if(i==0)
        i++;
    if(i>2)
        i=3;
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
   case 2:
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
   case 3:
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
    qDebug() << this->click;
    //std::cout<<click->x()<<","<<click->y()<<std::endl;
}
