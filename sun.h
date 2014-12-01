#ifndef SUN_H
#define SUN_H
#include <iostream>
#include <QPainter>
#include <QPicture>
#include <QTime>
#include <QGraphicsItem>

class Sun : public QGraphicsItem
{
private:
    int xPos;
    int yPos;
    int randomY;//obtain a random y coordinate for the sun to stop falling at
    int type;
    QPixmap sunPicture;//holds the picture
    QTime disappear;//tracks when a sun should disapear automatically
public:
    Sun();
    Sun(int x, int y,QString path,int type);
    int getX();
    int getY();
    int getType();//used to see if its a random sun or a sunflower sun
    void setClicked();//changes the position if clicked on for sunpoints
    void slideSun();//moves the sun downwards
    void advance(int phase);
    bool areaX(int x);//checks mouse click in x area
    bool areaY(int y);//checks mouse click in y area
    int timeEllapsed();//returns how much time since the plant has stopped falling
    QPixmap getPicture();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SUN_H
