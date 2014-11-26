#ifndef SUN_H
#define SUN_H
#include <iostream>
#include <QPainter>
#include <QPicture>

#include <QGraphicsItem>

class Sun : public QGraphicsItem
{
private:
    int xPos;
    int yPos;
    int randomY;
    QPixmap sunPicture;
    int type;
    int index;
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
    QPixmap getPicture();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SUN_H
