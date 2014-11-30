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
    int randomY;
    int type;
    QPixmap sunPicture;
    QTime disappear;
public:
    Sun();
    Sun(int x, int y,QString path,int type);
    int getX();
    int getY();
    int getType();
    void setClicked();
    void slideSun();
    void advance(int phase);
    bool areaX(int x);
    bool areaY(int y);
    bool getDeleted();
    int timeEllapsed();
    QPixmap getPicture();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SUN_H
